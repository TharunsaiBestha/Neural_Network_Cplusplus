//#include "Graph_library.h"
#include "Graph_algo.h"
#include<iostream>
int main(){
    Graph<char,int> G;
    //Vertex<int,std::vector<int>::iterator> Ve(10);
    //if(Ve==10)std::cout<<"OK";
    //else{std::cout<<"NO";}
    G.add_vertex('A');G.add_vertex('B');G.add_vertex('C');G.add_vertex('D');G.add_vertex('E');G.add_vertex('F');
    // G.add_edge('A','C',0);G.add_edge('C','A',0);
    // G.add_edge('B','D',0);G.add_edge('D','B',0);
    // G.add_edge('B','E',0);G.add_edge('E','B',0);
    // G.add_edge('C','E',0);G.add_edge('C','E',0);
    // G.add_edge('D','E',0);G.add_edge('E','D',0);
    // G.add_edge('D','F',0);G.add_edge('F','D',0);
    // G.add_edge('E','F',0);G.add_edge('F','E',0);
    // G.add_edge('A','B',0);G.add_edge('B','A',0);
    G.add_edge('A','B',0);G.add_edge('A','C',0);G.add_edge('A','E',0);
    G.add_edge('B','E',0);G.add_edge('C','F',0);G.add_edge('C','D',0);
    //G.add_edge('D','F',0);
    char s='A';
    char t;
   // DFS<char,int> temp(s,G);
   Topological_Sort<char,int> temp(s,G);
   // std::cout<<s;
    // do{
    //     std::cout<<t<<" ";
    //     t=temp.next_vertex();
    // }while(t!=s);
    // 
    auto i=temp.next();
    // while(i.second){
    //     if(i.first!=temp.end)std::cout<<(*i.first).value;
    //     i=temp.next_vertex();
    // }
    while(i!=temp.end){
        std::cout<<(*i).value;
        i=temp.next();
    }
    std::cout<<s;
    std::cout<<"\n";
}