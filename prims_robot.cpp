//Markus Buchholz

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits>
#include <algorithm>

int INF = std::numeric_limits<int>::max();

class Graph
{

private:
    int N;

public:
    std::vector<std::vector<int>> transitions;

    std::vector<std::pair<int, int>> connections;

    std::vector<int> connectNodes(int, int, std::vector<std::pair<int, int>>);

    Graph(int n) : N(n)
    {

        std::cout << "init graph" << std::endl;
        std::vector<int> trans_i(n, INF);
        std::vector<std::vector<int>> trans(n, trans_i);
        this->transitions = trans;
        std::vector<int> v_i(n, 0);
    }
    void addEdge(int vStart, int vEnd, int cost);
    std::vector<std::pair<int, int>> runPrims(int start);
};

//-------------------------------------------------------------------------------

void Graph::addEdge(int vStart, int vEnd, int cost)
{

    std::vector<int> trans_i;
    this->transitions[vStart][vEnd] = cost;
}

//-------------------------------------------------------------------------------
std::vector<int> Graph::connectNodes(int start, int goal, std::vector<std::pair<int, int>> prims)
{

    std::vector<int> way;

    std::vector<int> hash[N];

    for (auto &ii : prims)
    {
        hash[ii.first].push_back(ii.second);
    }

    int waypoint = goal;
    way.push_back(waypoint);
    while (waypoint != start)
    {
        for (int ii = 0; ii < N; ii++)
        {

            for (int jj = 0; jj < hash[ii].size(); jj++)
            {

                if (hash[ii][jj] == waypoint)
                {

                    waypoint = ii;
                    way.push_back(waypoint);
                }
            }
        }
    }

    return way;
}

//-------------------------------------------------------------------------------

std::vector<std::pair<int, int>> Graph::runPrims(int start)
{
    std::vector<std::pair<int, int>> prims;

    std::vector<int> visited(N, 0);

    visited[start] = 1;
    std::vector<int> active(N, 0);
    active[start] = 1;

    while (std::count(visited.begin(), visited.end(), 1) != visited.size())
    {

        int min_edge = INF;
        int iX = INF;
        int jX = INF;

        for (int ii = 0; ii < transitions.size(); ii++)
        {

            if (active[ii] == 1)
            {
                for (int jj = 0; jj < transitions[0].size(); jj++)
                {
                    if (visited[jj] == 0)
                    {
                        if (transitions[ii][jj] < min_edge)
                        {
                            min_edge = transitions[ii][jj];
                            iX = jj;
                            jX = ii;
                        }
                    }
                }
            }
        }

        active[iX] = 1;
        visited[iX] = 1;
        prims.push_back({jX + 1, iX + 1});
    }

    for (auto &ii : prims){

        std::cout << ii.first << " ," << ii.second << "\n";
    }

    return prims;
}

//-------------------------------------------------------------------------------

int main()
{

    Graph g(9);

    // 0
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);

    // 1
    g.addEdge(1, 0, 4);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);

    // 2
    g.addEdge(2, 1, 8);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(2, 8, 2);

    // 3
    g.addEdge(3, 2, 7);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);

    // 4
    g.addEdge(4, 3, 9);
    g.addEdge(4, 5, 10);

    // 5
    g.addEdge(5, 2, 4);
    g.addEdge(5, 3, 14);
    g.addEdge(5, 4, 10);
    g.addEdge(5, 6, 2);

    // 6
    g.addEdge(6, 5, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);

    // 7
    g.addEdge(7, 0, 8);
    g.addEdge(7, 1, 11);
    g.addEdge(7, 6, 1);
    g.addEdge(7, 8, 7);

    // 8
    g.addEdge(8, 2, 2);
    g.addEdge(8, 6, 6);
    g.addEdge(8, 7, 7);

    // // Edges for node 0
    // g.addEdge(0, 1, 2);
    // g.addEdge(0, 2, 4);
    // g.addEdge(0, 4, 10);

    // // Edges for node 1
    // g.addEdge(1, 0, 2);
    // g.addEdge(1, 3, 11);
    // g.addEdge(1, 4, 5);

    // // Edges for node 2
    // g.addEdge(2, 0, 4);
    // g.addEdge(2, 3, 3);
    // g.addEdge(2, 5, 1);

    // // Edges for node 3
    // g.addEdge(3, 0, 10);
    // g.addEdge(3, 1, 11);
    // g.addEdge(3, 2, 3);
    // g.addEdge(3, 4, 8);
    // g.addEdge(3, 5, 7);

    // // Edges for node 4
    // g.addEdge(4, 6, 6);
    // g.addEdge(4, 1, 5);
    // g.addEdge(4, 3, 8);

    // // Edges for node 5
    // g.addEdge(5, 6, 9);
    // g.addEdge(5, 4, 7);
    // g.addEdge(5, 2, 1);

    std::vector<std::pair<int, int>> prims = g.runPrims(0);

   std::vector<int> way = g.connectNodes(1, 5, prims);

    for (auto &ii : way)
    {
        std::cout << ii << " -- ";
    }

}