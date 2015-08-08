#include <cstdlib>
#include <iostream>
#include "Weighted_graph.h"

/*******************************************************************
 *
 * Currently, the instructor's output for the following executions
 * on the machine ecelinux9 is as follows:
 *
 *    $ g++ -O2 speed.cpp
 *
 *    $ time ./a.out 100
 *    14023.2, 2537074
 *    0.099u ...
 *    $ time ./a.out 200
 *    59470.3, 23730391
 *    0.817u ...
 *    $ time ./a.out 300
 *    136289, 83171291
 *    3.043u ...
 *    $ time ./a.out 400
 *    246579, 210765898
 *    8.644u ...
 *    $ time ./a.out 500
 *    392473, 418489876
 *    18.418u ...
 *    $ time ./a.out 600
 *    568650, 743708665
 *    34.319u ...
 *    $ time ./a.out 700
 *    776082, 1195813916
 *    57.496u ...
 *
 * The argument to ./a.out is the number of nodes in the graph.
 *
 * The next two numbers are the sum of the minimum spanning trees
 * and the sum of the number of edges checked.
 *
 * Finally, the time in question is the first number followed by
 * a 'u'.  This will indicate how fast your algorithm is.
 *******************************************************************/

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        return 0;
    }
    
    int N = std::atoi( argv[1] );
    
    // The random number seed will change
    srand48( 10 );
    
    double total = 0.0;
    int count = 0;
    
    Weighted_graph g( N );
    
    for ( int i = 0; i < N*N; ++i ) {
        for ( int j = 0; j < 10; ++j ) {
            int x = lrand48() % N;
            int y = lrand48() % N;
            double d = drand48();
            g.insert_edge( x, y, d );
        }
        
        std::pair<double, int> result = g.minimum_spanning_tree();
        total += result.first;
        count += result.second;
    }
    
    std::cout << total << ", " << count << std::endl;
    
    return 0;
}