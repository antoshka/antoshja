
#include <string>
#include <vector>
#include <unordered_set>
#include <cassert>

using graph_t       = std::vector< std::vector< int > >;
using graph_map_t   = std::vector< std::unordered_set< int > >;

class Solution {
public:
    static bool
    dfs( graph_map_t&           graph,
        std::vector< bool >&   visited,
        int                    index,
        int                    parent )
    {
        if( visited[index] )
            return true;

        visited[index] = true;

        for ( auto e: graph[index] ) {
            if ( e != parent and dfs( graph, visited, e, index ) ) 
            return true;
        }

        return false;
    }

    static std::vector< int >
    findRedundantConnection( const graph_t& edges ) {

        const size_t    len         { edges.size()      };
        graph_map_t     graph       { len + 1           };

        for ( const auto &v: edges ) {
            graph[v[0]].insert( v[1] );
            graph[v[1]].insert( v[0] );
        }

        for ( int i = len - 1; i >= 0; i-- ) {

            std::vector< int >      ed      { edges[i]          };
            std::vector< bool >     vis1    ( len + 1, false    );
            std::vector< bool >     vis2    ( len + 1, false    );

            graph[ ed[ 0 ] ].erase( ed[ 1 ] );
            graph[ ed[ 1 ] ].erase( ed[ 0 ] );

            if ( not dfs( graph, vis1, ed[0], 0 )
                and not dfs( graph, vis2, ed[1], 0 ) )
            {
                return ed;
            }

            graph[ ed[ 0 ] ].insert( ed[1] );
            graph[ ed[ 1 ] ].insert( ed[0] );
        }

        return {};
    }
};

int main() {

    // leetcode.com/problems/redundant-connection
    //  ┌───┐    ┌───┐    ┌───┐
    //  │ 1 ├───►│ 2 ├───►│ 3 │
    //  └┬─┬┘    └───┘    └─┬─┘
    //   │ │                │
    //   │ └─────────┐      │
    //   ▼           │      ▼
    //  ┌───┐        │    ┌───┐
    //  │ 5 │        └───►│ 4 │
    //  └───┘             └───┘

    graph_t graph {
        { 1, 2 },
        { 2, 3 },
        { 3, 4 },
        { 1, 4 },
        { 1, 5 }
    };

    assert( Solution::findRedundantConnection( graph ) == std::vector< int >( { 1, 4 } ) );

    puts("done!");
}
