#include <catch.hpp>

#include <cstdint>
#include <iostream>

#include <fmt/format.h>

#include <pat/pat.hpp>

using namespace pat;

TEST_CASE( "Leafy majority graphs", "[examples]" )
{
  auto func = []( uint32_t n ) {
    uint32_t secondary_items = ( n * ( n - 1 ) ) / 2;

    default_solver solver( n, secondary_items );

    auto offset = n;
    for ( auto i = 1u; i <= n; ++i )
    {
      /* only primary inputs */
      solver.add_option( std::vector<uint32_t>{i} );

      for ( auto j = 1u; j < i; ++j )
      {
        /* two primary inputs */
        solver.add_option( std::vector<uint32_t>{i, offset + j} );

        for ( auto k = j + 1; k < i; ++k )
        {
          /* one primary input */
          solver.add_option( std::vector<uint32_t>{i, offset + j, offset + k} );
        }
      }

      offset += i - 1;
    }

    return solver.solve();
  };

  CHECK( func( 4 ) == 56 );
  CHECK( func( 5 ) == 616 );
  CHECK( func( 6 ) == 9856 );
  CHECK( func( 7 ) == 216832 );
}
