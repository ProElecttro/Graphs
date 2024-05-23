#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

template<typename T>

class graph{
private:
    unordered_map<T, list<T>> gp;
public:
    void initialize_graph(T p, T q, bool directed){
        if(!directed){
            gp[q].push_back(p);
        }

        gp[p].push_back(q);
    }

    void print_graph(){
        for(auto a : gp){
            cout<<a.first<<" -> ";
            for(auto b : a.second){
                cout<<b<<" ";
            }
            cout<<endl;
        }
    }
};


int main(){
    int i{};
    int j{};
    graph <int> gp{};
    while(true){
        cout<<"Enter: ";
        cin>>i;
        if(i == -1){
            gp.print_graph();
            exit(0);
        }
        cin>>j;
        gp.initialize_graph(i, j, false);
    }

}