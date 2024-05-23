#include <map>
#include <unordered_map>
#include <set>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

template<typename T>

class graph{
    private:
        map<T, set<T>> graphData{};
        map<T, set<pair<T, T>>> weightedGraphData{};
        vector<T> bfsList{};
        vector<T> dfsList{};
        vector<T> topoSort{};
        vector<T> topoSortKahn{};
        int M{};
        int N{};

    public:
        void createGraph(int m, int n){
            M = m;
            N = n;
        }

        void insertEdge(int i, int j, bool isDirected){
            graphData[i].insert(j);
            if(!isDirected){
                graphData[j].insert(i);
            }
        }

        void printAdjList(){
            for(auto a: graphData){
                cout<<a.first<<" -> ";
                for(auto b: a.second){
                    cout << b << " ";
                }
                cout << endl;
            }
        }

        void BFSTransverse(T p){
            unordered_map<T, bool> visited{};
            queue<T> qu{};

            if(graphData.find(p) == graphData.end() || graphData[p].empty()){
                cerr<<"Error: Invalid starting point";
                return;
            }

            qu.push(p);
            visited[p] = true;

            while(!qu.empty()){
                T node = qu.front();
                qu.pop();
                bfsList.push_back(node);

                for(auto a: graphData[node]){
                    if(!visited[a]){
                        qu.push(a);
                        visited[a] = true;
                    }
                }
            }

            for(auto a: graphData){
                T node = a.first;
                if(visited[node]){
                    continue;
                }
                qu.push(node);
                visited[node] = true;

                while(!qu.empty()){
                    p = qu.front();
                    qu.pop();
                    bfsList.push_back(p);

                    for(auto a: graphData[p]){
                        if(!visited[a]){
                            qu.push(a);
                            visited[a] = true;
                        }
                    }
                }
            }

            cout<<"BFS Transverse List: ";
            for(auto a: bfsList){
                cout<< a <<" ";
            }
        }

        void DFS(int node, unordered_map<int, bool> &visited){
            visited[node] = true;
            dfsList.push_back(node);

            for(auto a: graphData[node]){
                if(!visited[a]){
                    DFS(a, visited);
                }
            }
        }

        void DFSTransverse(int startingPoint){
            if(graphData.find(startingPoint) == graphData.end() || graphData[startingPoint].empty()){
                cerr<<"Error: Invalid starting point";
                return;
            }

            unordered_map<int, bool> visited{};
            
            DFS(startingPoint, visited);

            for(auto a: graphData){
                if(!visited[a.first]){
                    DFS(a.first, visited);
                }
            }

            cout<<"DFS Transverse List: ";
            for(auto a: dfsList){
                cout<< a <<" ";
            }
        }

        void detectCycleBFS(T start) {
            int countCycles = 0;
            
            if (graphData.find(start) == graphData.end() || graphData[start].empty()) {
                cerr << "Error: Invalid starting point" << endl;
                return;
            }

            unordered_map<T, bool> visited;
            T parent = -1;
            queue<T> qu;

            qu.push(start);
            visited[start] = true;

            while (!qu.empty()) {
                T node = qu.front();
                qu.pop();
                parent = node;

                for (auto neighbor : graphData[node]) {
                    if (!visited[neighbor]) {
                        qu.push(neighbor);
                        visited[neighbor] = true;
                    } else if (neighbor != parent) {
                        countCycles++;
                        break;
                    }
                }
            }

            for (auto entry : graphData) {
                T node = entry.first;
                if (!visited[node]) {
                    qu.push(node);
                    visited[node] = true;

                    while (!qu.empty()) {
                        T current = qu.front();
                        parent = node;
                        qu.pop();

                        for (auto neighbor : graphData[current]) {
                            if (!visited[neighbor]) {
                                qu.push(neighbor);
                                visited[neighbor] = true;
                            } else if (neighbor != parent) {
                                countCycles++;
                                break;
                            }
                        }
                    }
                }
            }

            cout << "Total cycles(BFS): " << countCycles / 2 << " cycles" << endl; // Each cycle is counted twice
        }

        bool DFSCycles(int node, unordered_map<int, bool> visited, int parentNode, int &countCycles){
            visited[node] = true;

            for(auto a: graphData[node]){
                if(!visited[a]){
                    visited[a] = true;
                    DFSCycles(a, visited, node, countCycles);
                }else if(visited[a] && parentNode != a){
                    countCycles++;
                    return true;
                }
            }

            return false;
        }

        void detectCycleDFS(int startingPoint){
            int countCycles{};
            if(graphData.find(startingPoint) == graphData.end() || graphData[startingPoint].empty()){
                cerr<<"Error: Invalid starting point";
                return;
            }

            unordered_map<int, bool> visited{};
            visited[startingPoint] = true;
            int parentNode = startingPoint;
            DFSCycles(startingPoint, visited, parentNode, countCycles);

            for(auto a: graphData){
                if(!visited[a.first]){
                    DFSCycles(a.first, visited, -1, countCycles);
                }
            }

            cout<<"Total cycles(DFS): "<<countCycles<<" cycles"<<endl;
        }

        void topologicalSortDFS(int node, unordered_map<T, bool>& visited, stack<T>& st){
            for(auto a: graphData[node]){
                if(!visited[a]){
                    visited[a] = true;
                    topologicalSortDFS(a, visited, st);
                }
            }

            st.push(node);
        }

        void topologicalSort(){
            unordered_map<T, bool> visited{};
            stack<T> st{};
            for(auto a: graphData){
                if(!visited[a.first]){
                    visited[a.first]=true;
                    topologicalSortDFS(a.first, visited, st);
                }
            }

            cout<<"TopologicalSort: ";
            while(!st.empty()){
                topoSort.push_back(st.top());
                cout<<st.top()<< " ";
                st.pop();
            }
            cout<<endl;
        }

        void topolyKahnsSort(){
            unordered_map<T, int> indegree{};

            for(auto a: graphData){
                for(auto b: a.second){
                    indegree[b]++;
                }
            }

            queue<T> qu{};
            for(auto a: graphData){
                if(indegree[a.first] == 0){
                    qu.push(a.first);
                }
            }

            while(!qu.empty()) {
                T p = qu.front();
                qu.pop();
                topoSortKahn.push_back(p);

                for(auto a: graphData[p]){
                    indegree[a]--;
                    if(indegree[a] == 0){
                        qu.push(a);
                    }
                }
            }

            cout<<"TopologicalSort by Kahn's Method(BFS): ";
            for(auto a: topoSortKahn){
                cout<<a<<" ";
            }
            cout<<endl;

            cout<<"Is it cyclic? : ";
            if(int(topoSortKahn.size()) == int(N)){
                cout<<"No."<<endl;
            }else{
                cout<<"Yes."<<endl;
            }
        }

        void shortestPath(T source, T destination){
            unordered_map<T, bool> visited{};
            unordered_map<T, T> parent{};
            parent[source] = source;

            queue<T> qu{};
            qu.push(source);
            visited[source] = true;

            while(!qu.empty()){
                T p = qu.front();
                qu.pop();

                for(auto a: graphData[p]){
                    if(!visited[a]){
                        visited[a] = true;
                        parent[a] = p;
                        qu.push(a);

                        if(a == destination) break;
                    }
                }
            }

            if (!visited[destination]) {
                cout << "No path found from " << source << " to " << destination << endl;
                return;
            }
            
            T current = destination;
            vector<T> path{};
            while(current != source){
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            cout<<"Shortest path: ";
            for(auto a: path){
                cout<<a<<" ";
            }
            cout<<endl;
        }

        void setWeightedGraphData(T u, T v, T weight){
            pair<T, T> p = make_pair(v, weight);
            weightedGraphData[u].insert(p);
        }

        void printWeightedGraph(){
            for(auto a: weightedGraphData){
                cout<<a.first<<" -> ";
                for(auto b: weightedGraphData[a.first]){
                    cout<<b.first<<" weight: "<<b.second<<", ";
                }
                cout<<endl;
            }
        }

        vector<T> topologicalSortWeighted() {
            unordered_map<T, int> indegree;

            // Initialize indegree of all nodes to 0
            for (const auto& a : weightedGraphData) {
                indegree[a.first];
                for (const auto& b : a.second) {
                    indegree[b.first]++;
                }
            }

            queue<T> qu;
            for (const auto& a : indegree) {
                if (a.second == 0) {
                    qu.push(a.first);
                }
            }

            vector<T> ans;

            while (!qu.empty()) {
                T node = qu.front();
                qu.pop();
                ans.push_back(node);

                for (const auto& a : weightedGraphData[node]) {
                    indegree[a.first]--;
                    if (indegree[a.first] == 0) {
                        qu.push(a.first);
                    }
                }
            }

            return ans;
        }

        void shortestPathWeighted(T source) {
            unordered_map<T, int> dist;
            for (const auto& a : weightedGraphData) {
                dist[a.first] = INT_MAX;
            }
            dist[source] = 0;

            vector<T> topoOrder = topologicalSortWeighted();

            for (const auto& current : topoOrder) {
                cout << "........." << current << endl;
                if (dist[current] != INT_MAX) {
                    for (const auto& a : weightedGraphData[current]) {
                        if (dist[a.first] > dist[current] + a.second) {
                            dist[a.first] = dist[current] + a.second;
                        }
                    }
                }
            }

            cout << "Source: " << source << endl;
            for (const auto& a : dist) {
                if (a.second == INT_MAX) {
                    cout << a.first << " : " << "INF" << endl;
                } else {
                    cout << a.first << " : " << a.second << endl;
                }
            }
        }

        void Dijkstra(T source){
            set<pair<T, T>> minDist;
            unordered_map<T, int> dist;

            for(auto a: weightedGraphData){
                dist[a.first] = INT_MAX;
            }

            dist[source] = 0;
            minDist.insert(make_pair(dist[source], source));

            while(!minDist.empty()){
                pair<T, T> nearest = *minDist.begin();
                minDist.erase(minDist.begin());
                for(auto a: weightedGraphData[nearest.second]){
                    if(dist[a.first] > dist[nearest.second] + a.second){
                        dist[a.first] = dist[nearest.second] + a.second;
                        minDist.insert(make_pair(dist[a.first], a.first));
                    }
                }
            }
            
            cout<<"Source: "<<source<<endl;
            for(auto a: dist){
                cout<<a.first<<" : "<<a.second<<endl;
            }
            cout<<endl;
        }
};

int main(){
    int N{};
    int M{};
    
    cout<<"Enter number of nodes: ";
    cin>>N;
    cout<<"Enter number of edges: ";
    cin>>M;

    graph<int> gp{};
    gp.createGraph(M, N);

    // int i{};
    // int j{};
    // bool isDirected{};

    // string isDirectedString{};
    // cout<<"Is the graph directed? (yes/no) : ";
    // cin>>isDirectedString;

    // if(isDirectedString == "yes"){
    //     isDirected = true;
    // }else if(isDirectedString == "no"){
    //     isDirected = false;
    // }


    // for(int k{}; k < M; k++){
    //     cout<<"Enter Edge "<<k<<": ";
    //     cin>>i>>j;
    //     gp.insertEdge(i, j, isDirected);
    // }

    // gp.printAdjList();

    // int startingPoint{};
    
    // cout<<"Enter Starting Point BFS Transversal: ";
    // cin>>startingPoint;
    // gp.BFSTransverse(startingPoint);
    
    // cout<<"Enter Starting Point DFS Transversal: ";
    // cin>>startingPoint;
    // gp.DFSTransverse(startingPoint);
    
    // cout<<"Enter Starting Point finding Cycles with BFS : ";
    // cin>>startingPoint;
    // gp.detectCycleBFS(startingPoint);
    
    // cout<<"Enter Starting Point finding Cycles with DFS : ";
    // cin>>startingPoint;
    // gp.detectCycleDFS(startingPoint);

    // gp.topologicalSort(); //only for DAG(directed acyclic graph)
    // gp.topolyKahnsSort();

    // cout<<"Enter the source and destination points: ";
    // int source{};
    // int destination{};
    // cin>>source>>destination;

    // gp.shortestPath(source, destination);

    // int weight{};
    gp.setWeightedGraphData(0, 1, 5);
    gp.setWeightedGraphData(0, 2, 3);
    gp.setWeightedGraphData(1, 2, 2);
    gp.setWeightedGraphData(1, 3, 6);
    gp.setWeightedGraphData(2, 3, 7);
    gp.setWeightedGraphData(2, 4, 4);
    gp.setWeightedGraphData(2, 5, 2);
    gp.setWeightedGraphData(3, 4, -1);
    gp.setWeightedGraphData(4, 5, -2);
    // for(int k{}; k < M; k++){
    //     cout<<"Enter Edge "<<k<<": ";
    //     cin>>i>>j>>weight;
    //     gp.setWeightedGraphData(i, j, weight);
    // }

    gp.printWeightedGraph();
    int s{};
    cout<<"Enter Source: ";
    cin>>s;
    gp.shortestPathWeighted(s);
    
    gp.Dijkstra(s);
}
