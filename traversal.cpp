#include "Graph.h"
#include<queue>
template<typename T,typename E>
void print_vertex(Vertex<T,E>& source){
    std::cout<<source.getValue();
}
template<typename T,typename E>
void add_neighbours(std::queue<Vertex<T,E>>& que,std::vector<Vertex<T, E>>&& vec){
    for(auto& i:vec){
        que.push(i);
    }
}
template<typename T,typename E>
std::vector<Vertex<T,E>> difference(std::vector<Vertex<T,E>>& vis,std::vector<Vertex<T,E>>&& all_n){
    std::vector<Vertex<T,E>> d;
    for(auto& i:all_n){
        if(vis.end()==std::find(vis.begin(),vis.end(),i)){
            d.push_back(i);
            //vis.push_back(i);
        }
    }
    return d;
}
template<typename T,typename E>
void BFS(Graph<T,E>& G,Vertex<T,E>& source){
    std::queue<Vertex<T,E>> temp_queue;
    std::vector<Vertex<T, E>> visited;
    Vertex<T,E> temp;
    temp_queue.push(source);
    do{
        temp=temp_queue.front();
        visited.push_back(temp);
       // print_vertex(temp);
        //temp_queue.pop();
        add_neighbours(temp_queue,difference(visited,all_neighbour_vertex(temp)));
        temp_queue.pop();
    }while(!temp_queue.empty());
    for(auto& i:visited){
        print_vertex(i);
    }
}
int main(){
    Graph<char,int> test_Graph(6);
    test_Graph.addVertex('a');
    test_Graph.addVertex('b');
    test_Graph.addVertex('c');
    test_Graph.addVertex('d');
    test_Graph.addVertex('e');
    test_Graph.addVertex('f');
    test_Graph.addEdge('a','b',0);
    test_Graph.addEdge('a','c',0);
    test_Graph.addEdge('b','d',0);
    test_Graph.addEdge('b','e',0);
    test_Graph.addEdge('d','f',0);
    test_Graph.addEdge('d','e',0);
    test_Graph.addEdge('e','f',0);
    BFS(test_Graph,test_Graph[0]);
}