#include <iostream>
#include <vector>

int counter = 1;
int brojac= 0;

void bumpProcedure(std::vector<std::vector<int>> &P, std::vector<std::vector<int>> &Q, int bump, int level)
{
    brojac++;
    if(P.size() < level+1)
    {
        std::vector<int> row;
        P.push_back(row);
        Q.push_back(row);
    }
    if(P[level].empty())
    {
        P[level].push_back(bump);
        Q[level].push_back(counter++);
    }
    else
        for(int j = 0; j < P[level].size(); j++)
        {
            if(bump > P[level][j] && bump > P[level].back()) //najveci u redu
            {
                P[level].push_back(bump);
                Q[level].push_back(counter++);
            }
            else if(bump < P[level][j]) //izbija nekog
            {
                int help = P[level][j];
                P[level][j] = bump;
                bumpProcedure(P,Q,help,level+1);
                break;
            }
        }
}


void schensted(std::vector<std::vector<int>> &P, std::vector<std::vector<int>> &Q, std::vector<int> &ulaz)
{
    int bump;
    std::vector<int> row;
    P.push_back(row);
    P[0].push_back(ulaz[0]);
    Q.push_back(row);
    Q[0].push_back(counter++);

    for(int i = 1; i < ulaz.size(); i++)
    {
        for(int j = 0; j < P[0].size(); j++)
        {
            if(ulaz[i] > P[0][j] && ulaz[i] > P[0].back()) //najveci u redu
            {
                P[0].push_back(ulaz[i]);
                Q[0].push_back(counter++);
            }
            else if(ulaz[i] < P[0][j]) //izbija nekog
            {
                bump = P[0][j];
                P[0][j] = ulaz[i];
                bumpProcedure(P,Q,bump,0+1);
                break;
            }
        }
    }
}

void printVector(std::vector<std::vector<int>> vector)
{
    for(auto &i : vector)
    {
        for(auto &j : i)
            std::cout<< j<< " ";
        std::cout<<"\n";
    }
    std::cout<<std::endl;
        
}

int main()
{
    std::vector<std::vector<int>> P,Q;
    std::vector<int> ulaz {8,7,6,5,4,3,2,1};
    std::cout<<"Ulaz: "<<"\n";
    for(auto &i:ulaz)
        std::cout<< i << " ";
    std::cout<<std::endl;
    schensted(P,Q,ulaz);
    std::cout<<"\nP: "<<"\n";
    printVector(P);
    std::cout<<"Q: "<<"\n";
    printVector(Q);
    std::cout<<brojac<<std::endl;
    return 0;
}