/* pat: C++ dancing links solver
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
  \brief Callback functions to access solutions

  \author Mathias Soeken
*/

#pragma once

#include <cstdint>
#include <vector>

namespace pat
{
/*! \brief Iterator type to access solutions

  To avoid copying, a solution is passed to the solution callback in terms of an
  iterator pair.
*/
using solution_iterator = std::vector<uint32_t>::const_iterator;

/*! \brief Do nothing, just count all solutions

  This solution callback does not perform any code, but will return true such
  that all solutions are going to be visited.  This is the default solution
  callback that is passed to ``pat::solver::solve``.
*/
inline bool just_count( solution_iterator begin, solution_iterator end )
{
  (void)begin;
  (void)end;
  return true;
}

/*! \brief Do nothing, but stop after first solution

  This solution callback can be used if one is iterested in finding whether
  there is a solution or not, but the actual solution is not important.
*/
inline bool stop_after_first( solution_iterator begin, solution_iterator end )
{
  (void)begin;
  (void)end;
  return false;
}

/*! \brief Do nothing, in a meta solution callback

  In a meta solution callback, such as ``pat::stop_after``, this callback can be
  used to indicate that no action is performed on the solution.  Callbacks in
  meta solution callbacks do not return a truth value, since the meta callback
  decides whether to continue finding solutions or not.
*/
inline void do_nothing( solution_iterator begin, solution_iterator end )
{
  (void)begin;
  (void)end;
}

/*! \cond PRIVATE */
namespace detail
{
template<typename Fn>
struct stop_after_impl
{
  stop_after_impl( uint32_t max_solutions, Fn&& fn )
      : max_solutions( max_solutions ),
        fn( std::move( fn ) ) {}

  bool operator()( solution_iterator begin, solution_iterator end )
  {
    fn( begin, end );
    return ++counter != max_solutions;
  }

private:
  uint32_t counter{0u};
  uint32_t max_solutions;

  Fn&& fn;
};
}
/*! \endcond PRIVATE */

/*! \brief Stop after given number of solutions

  This is a meta solution callback, which can receive as second argument another
  callback which handles the actual solution.  By default, no action is
  performed on the solution.
*/
template<typename Fn = decltype( do_nothing )>
inline auto stop_after( uint32_t max_solutions, Fn&& fn = do_nothing )
{
  return detail::stop_after_impl<Fn>( max_solutions, std::move( fn ) );
}
}
