#include <catch.hpp>

#include <cstdint>
#include <iostream>

#include <fmt/format.h>

#include <pat/pat.hpp>

using namespace pat;

inline auto n_queens_primary( uint8_t n )
{
  const uint32_t num_items = 6 * n - 2;
  const uint32_t column_offset = n;
  const uint32_t a_offset = 2 * n - 1;
  const uint32_t b_offset = 5 * n - 1;

  default_solver solver( num_items );

  for ( uint32_t i = 1u; i <= n; ++i )
  {
    for ( uint32_t j = 1u; j <= n; ++j )
    {
      const auto row = i;
      const auto col = column_offset + j;
      const auto a = a_offset + i + j;
      const auto b = b_offset + i - j;

      solver.add_option( std::vector<uint32_t>{row, col, a, b} );
    }
  }

  for ( uint32_t i = 2 * n + 1; i <= num_items; ++i )
  {
    solver.add_option( std::vector<uint32_t>{i} );
  }

  return solver.solve();
}

TEST_CASE( "n Queens (primary)", "[examples]" )
{
  CHECK( n_queens_primary( 4 ) == 2 );
  CHECK( n_queens_primary( 8 ) == 92 );
  CHECK( n_queens_primary( 10 ) == 724 );
}
