#include <iostream>
#include <vector>

#include <pat/pat.hpp>

int main( int argc, char** argv )
{
  std::cout << "hello world" << std::endl;

  pat::solver solver( 7 );
  solver.add_option( std::vector<uint32_t>{3, 5} );
  solver.add_option( std::vector<uint32_t>{1, 4, 7} );
  solver.add_option( std::vector<uint32_t>{2, 3, 6} );
  solver.add_option( std::vector<uint32_t>{1, 4, 6} );
  solver.add_option( std::vector<uint32_t>{2, 7} );
  solver.add_option( std::vector<uint32_t>{4, 5, 7} );

  //solver.print_contents();

  solver.solve( []( const auto& solution ) {
    std::cout << "[i] solution:";
    for ( auto option : solution )
    {
      std::cout << " " << option;
    }
    std::cout << std::endl;
  } );

  return 0;
}
