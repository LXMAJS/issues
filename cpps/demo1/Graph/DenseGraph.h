//
// Created by 黎进 on 2018/8/31.
//

#ifndef DEMO1_DENSEGRAPH_H
#define DEMO1_DENSEGRAPH_H

#include <iostream>
#include <vector>

using namespace std;

namespace DenseGraph{
    /*
     * advince vector
     */
    class DenseGraph{
    private:
        int n; // count of vectrix
        int m; // count of edge
        bool directed; // if directed
        vector<vector<bool>> g; // graph

    public:
        /// construction
        /// \param n
        /// \param directed
        DenseGraph(int n, bool directed){
            this->n = n;
            this->m = 0;
            this->directed = directed;

            for (int i = 0; i < n; i++) {
                g.push_back( vector<bool>(n, false) ); //TODO: can't understand now
            }
        }

        ~DenseGraph(){
            // Do nothing
        }

        int V(){ return n; }
        int E(){ return m; }

        /// confirm two v has e
        /// \param v
        /// \param w
        /// \return
        bool hasEdge(int v, int w){
            assert(v >= 0 && v <= n);
            assert(w >= 0 && w <= n);

            return g[v][w];
        }

        ///  add edge
        /// \param v
        /// \param w
        void addEdge(int v, int w) {
            assert(v >= 0 && v <= n);
            assert(w >= 0 && w <= n);

            // 去掉了平行边的概念
            if (hasEdge(v, w)) {
                return;
            }

            g[v][w] = true;
            if(!directed){
                g[w][v] = true;
            }
            m++;
            return;
        }
    };
}

#endif //DEMO1_DENSEGRAPH_H