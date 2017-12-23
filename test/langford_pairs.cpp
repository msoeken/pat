#include <catch.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <pat/pat.hpp>

using namespace pat;

inline auto langford_pairs( unsigned n )
{
  default_solver solver( 3 * n );

  for ( auto i = 1u; i <= n; ++i )
  {
    for ( auto j = 1u; j <= 2u * n - 1u - i; ++j )
    {
      auto k = i + j + 1u;

      assert( k <= 2u * n );

      solver.add_option( std::vector<uint32_t>{2 * n + i, j, k} );
    }
  }

  return solver.solve();
}

TEST_CASE( "Langford pairs example", "[examples]" )
{
  CHECK( langford_pairs( 3 ) == 2 );
  CHECK( langford_pairs( 4 ) == 2 );
  CHECK( langford_pairs( 5 ) == 0 );
  CHECK( langford_pairs( 8 ) == 300 );
  CHECK( langford_pairs( 11 ) == 35584 );
}
