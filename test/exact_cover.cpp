#include <catch.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <pat/pat.hpp>

using namespace pat;

TEST_CASE( "Knuth simple exact cover example", "[examples]" )
{
  default_solver solver( 7 );
  solver.add_option( std::vector<uint32_t>{3, 5} );
  solver.add_option( std::vector<uint32_t>{1, 4, 7} );
  solver.add_option( std::vector<uint32_t>{2, 3, 6} );
  solver.add_option( std::vector<uint32_t>{1, 4, 6} );
  solver.add_option( std::vector<uint32_t>{2, 7} );
  solver.add_option( std::vector<uint32_t>{4, 5, 7} );

  std::string solution;
  const auto num_solutions = solver.solve( [&solver, &solution]( const auto& begin, const auto& end ) {
    for ( auto it = begin; it != end; ++it )
    {
      solution += std::to_string( solver.option_index( *it ) );
    }
    return true;
  } );

  CHECK( num_solutions == 1 );
  CHECK( solution == "340" );
}
