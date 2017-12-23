#include <iostream>
#include <vector>

#include <pat/pat.hpp>

void langford_pairs( unsigned n )
{
  pat::solver solver( 3 * n );

  for ( auto i = 1u; i <= n; ++i )
  {
    for ( auto j = 1u; j <= 2u * n - 1u - i; ++j )
    {
      auto k = i + j + 1u;

      assert( k <= 2u * n );

      solver.add_option( std::vector<uint32_t>{2 * n + i, j, k} );
    }
  }

  std::cout << "found " << solver.solve( pat::stop_after( 10u, [n]( auto begin, auto end ) { assert( std::distance( begin, end ) == n ); } ) ) << " solutions" << std::endl;
}

int main( int argc, char** argv )
{
  pat::solver solver( 7 );
  solver.add_option( std::vector<uint32_t>{3, 5} );
  solver.add_option( std::vector<uint32_t>{1, 4, 7} );
  solver.add_option( std::vector<uint32_t>{2, 3, 6} );
  solver.add_option( std::vector<uint32_t>{1, 4, 6} );
  solver.add_option( std::vector<uint32_t>{2, 7} );
  solver.add_option( std::vector<uint32_t>{4, 5, 7} );

  solver.solve( [&solver]( const auto& begin, const auto& end ) {
    std::cout << "[i] solution:";
    for ( auto it = begin; it != end; ++it )
    {
      std::cout << " " << solver.option_index( *it );
    }
    std::cout << std::endl;
    return true;
  } );

  langford_pairs( 8u );

  return 0;
}
