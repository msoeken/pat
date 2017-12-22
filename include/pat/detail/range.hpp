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
  \file range.hpp
  \brief Range utilities

  \author Mathias Soeken
*/

#pragma once

#include <cstdint>
#include <string>

#include <range/v3/all.hpp>

namespace pat
{
namespace detail
{
struct identity
{
  template<typename U>
  constexpr auto operator()( U&& v ) const noexcept -> decltype( std::forward<U>( v ) )
  {
    return std::forward<U>( v );
  }
};

template<typename Fn = identity>
inline auto pad( Fn&& fn = Fn(), uint8_t width = 5 )
{
  return ranges::view::transform( [width, &fn]( auto i ) { return fmt::format( "{:>{}}", fn( i ), width ); } );
}

inline auto split_and_prefix( uint8_t n, const std::string& prefix, const std::string& suffix = "\n" )
{
  return ranges::view::chunk( n ) |
         ranges::view::transform( [&prefix, &suffix]( const auto& c ) { return fmt::format( "{}{}{}", prefix, ranges::action::join( c ), suffix ); } );
}
}
}