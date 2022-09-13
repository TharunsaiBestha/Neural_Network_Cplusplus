#include "Graph.h"
template<typename T>
bool findele(std::vector<T>& v,T ele){
    return std::find(v.begin(),v.end(),ele)!=v.end();
}
template<typename T,typename E>
Edge<E,Vertex<T,E>> min_edge_without_v(Vertex<T,E>& Ver,std::vector<T>& v){
    Edge<E,Vertex<T,E>> tempe{};
    tempe.value=std::numeric_limits<E>::max();
    for(auto& i:Ver.Evec){
        if(findele(v,next_vertex(Ver,i).getValue())){}
        else{
            if(i.value < tempe.value){
                tempe=i;
            }
        }
    }
    return tempe;
}
template<typename T,typename E>
 Edge<E,Vertex<T,E>> find_Min_Neibour(std::vector<T> &v,Graph<T,E>& G){
     T temp{};
     Edge<E,Vertex<T,E>> tempe{};
     Edge<E,Vertex<T,E>> tempemin{};
     tempemin.value=std::numeric_limits<E>::max();
     Vertex<T,E> tempv{};
     bool tempb;
     for(auto& i:v){
         tempv=G.findVertex(i);
         tempe=min_edge_without_v(tempv,v);
        // tempb=(findele(v,next_vertex(tempv,tempe).getValue()));
         if(tempe.value<=tempemin.value && tempe.value<std::numeric_limits<E>::max()){
             tempemin=tempe;
             temp=next_vertex(tempv,tempe).getValue();
         }
     }
     v.push_back(temp);
     return tempemin;
 }
template<typename T,typename E>
std::vector<Edge<E,Vertex<T,E>>> prim(Graph<T,E>& G){
    std::vector<Edge<E,Vertex<T,E>>> tempe{};
    std::vector<T> tempv;
    tempv.push_back(G.lver[0].getValue());
    int NV=G.lver.size();
    for(int i=0;i<NV-1;i++){
        tempe.push_back(find_Min_Neibour(tempv,G));
    }
    return tempe; 
}