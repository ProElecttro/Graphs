#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

int main()
{
    int N; // nodes
    int M; // edges

    cout << "Enter number of nodes and edges: ";
    cin >> N >> M;

    unordered_map<int, set<int>> adjList;

    int i, j;
    for (int k = 0; k < M; k++)
    {
        cout << "Enter edge " << k + 1 << ": ";
        cin >> i >> j;
        adjList[i].insert(j);
        adjList[j].insert(i);
    }

    for (auto a : adjList)
    {
        cout << a.first << " -> ";
        for (auto b : a.second)
        {
            cout << b << " ";
        }
        cout << endl;
    }

    

    cout << "Acyclic Graph" << endl;

    return 0;
}
