#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <queue>

#define VELICINA 6

std::vector<std::vector<int>> unos(std::vector<std::vector<int>> &graf)
{
    graf[0][1] = 16;
    graf[0][2] = 13;
    graf[1][2] = 10;
    graf[1][3] = 12;
    graf[2][1] = 4;
    graf[2][4] = 14;
    graf[3][2] = 9;
    graf[3][5] = 20;
    graf[4][3] = 7;
    graf[4][5] = 4;
    return graf;
}

bool Bfs(std::vector<std::vector<int>> residual, int izvor, int kraj, std::vector<int> &roditelj)
{
    std::vector<bool> posjeceno(VELICINA, 0);

    std::queue<int> red;
    red.push(izvor);
    posjeceno[izvor] = true;
    roditelj[izvor] = -1;

    while(!red.empty())
    {
        int u = red.front();
        red.pop();

        for(int v = 0; v < VELICINA; v++)
        {
            if((posjeceno[v] == false) && (residual[u][v] > 0))
            {
                red.push(v);
                roditelj[v] = u;
                posjeceno[v] = true;
            }
        }
    }
    return ( posjeceno[kraj] == true);
}

int Ford_fulkerson(std::vector<std::vector<int>> graf, int izvor, int kraj)
{
    int u, v;

    std::vector<std::vector<int>> residual(VELICINA,std::vector<int>(VELICINA,0));
    std::copy(graf.begin(),graf.end(),residual.begin());
    
    std::vector<int> roditelj(VELICINA,0);
    int max_flow = 0;
    
    while(Bfs(residual, izvor, kraj, roditelj))
    {
        int path_flow = INT_MAX;
        for(v = kraj; v != izvor; v = roditelj[v])
        {
            u = roditelj[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }
        for(v = kraj; v != izvor; v = roditelj[v])
        {
            u = roditelj[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main()
{
    std::vector<std::vector<int>> graf(VELICINA,std::vector<int>(VELICINA,0));
    unos(graf);
    std::cout << "Maximum flow: " << Ford_fulkerson(graf, 0, 5) << std::endl;
}