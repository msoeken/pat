/* kitty: C++ dancing links solver
 * Copyright (C) 2017  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
  \file solver.hpp
  \brief Solver interface

  \author Mathias Soeken
*/

#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include <fmt/format.h>
#include <range/v3/all.hpp>

#include "detail/range.hpp"

namespace pat
{

class solver
{
private:
  struct item
  {
    uint32_t index{};
    uint32_t llink{};
    uint32_t rlink{};
  };

  struct node
  {
    union {
      int32_t len{};
      int32_t top;
    };
    uint32_t ulink{};
    uint32_t dlink{};
  };

public:
  explicit solver( uint32_t num_items )
      : items( num_items + 1 ),
        nodes( num_items + 2 ),
        num_items( num_items )
  {
    initialize_items();
  }

  template<class Items>
  void add_option( const Items& opt_items )
  {
    /* store current last item */
    const auto p = nodes.size() - 1;
    auto k = 0u;

    for ( auto j : opt_items )
    {
      if ( j < 1 || j > items.size() )
      {
        assert( false );
      }
      nodes[j].len++;
      const auto q = nodes[j].ulink;
      nodes[j].ulink = nodes[q].dlink = nodes.size();

      node next_node;
      next_node.ulink = q;
      next_node.dlink = j;
      next_node.top = j;

      nodes.push_back( next_node );
      ++k;
    }

    ++m;
    nodes[p].dlink = p + k;

    /* next spacer */
    node spacer;
    spacer.top = -m;
    spacer.ulink = p + 1;
    nodes.push_back( spacer );
  }

  void solve()
  {
    auto l = 0;
  }

  /* debug */
public:
  void print_contents( std::ostream& os = std::cout )
  {
    /* seperation rule */
    std::string rule( 5 * items.size() + 9, '-' );

    /* items */
    os << rule << std::endl
       << "       i:" << ( ranges::view::ints( size_t( 0 ), items.size() ) | detail::pad() | ranges::action::join ) << std::endl
       << "llink(i):" << ( items | detail::pad( []( auto i ) { return i.llink; } ) | ranges::action::join ) << std::endl
       << "rlink(i):" << ( items | detail::pad( []( auto i ) { return i.rlink; } ) | ranges::action::join ) << std::endl
       << rule << std::endl;

    /* nodes */
    const auto indexes = ranges::view::ints( size_t( 0 ), nodes.size() ) |
                         detail::pad() |
                         detail::split_and_prefix( items.size(), "       x:" );

    const auto tops = nodes |
                      detail::pad( []( auto n ) { return n.top; } ) |
                      detail::split_and_prefix( items.size(), "  top(x):" );

    const auto ulinks = nodes |
                        detail::pad( []( auto n ) { return n.ulink; } ) |
                        detail::split_and_prefix( items.size(), "ulink(x):" );

    const auto dlinks = nodes |
                        detail::pad( []( auto n ) { return n.dlink; } ) |
                        detail::split_and_prefix( items.size(), "dlink(x):" );

    os << ( ranges::view::zip_with( [&rule]( const auto& l1, const auto& l2, const auto& l3, const auto& l4 ) { return l1 + l2 + l3 + l4 + rule + "\n"; },
                                    indexes, tops, ulinks, dlinks ) |
            ranges::action::join )
       << std::endl;
  }

private:
  void initialize_items()
  {
    /* initialize linked list of top items */
    for ( auto i = 1; i <= num_items; ++i )
    {
      items[i].index = i;
      items[i].llink = i - 1;
      items[i - 1].rlink = i;

      nodes[i].len = 0;
      nodes[i].ulink = nodes[i].dlink = i;
    }

    items[0].llink = num_items;
    items[num_items].rlink = 0;

    /* spacer */
    nodes[num_items + 1].top = 0;
  }

private:
  std::vector<item> items;
  std::vector<node> nodes;

  uint32_t num_items;
  int32_t m = 0;
};
}
