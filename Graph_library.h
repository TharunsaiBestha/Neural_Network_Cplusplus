#include<list>
#include<vector>
#include<algorithm>
template<typename T,typename E>
struct Vertex{
    typedef typename std::list<Vertex<T,E>>::iterator Edge;
    T value;
    std::vector<std::pair<Edge,E>> vec;
    Vertex(T val){
        value=val;
        vec={};
    }
    Vertex(const Vertex& V){
        value=V.value;
        vec=V.vec;
    }
    Vertex(){}
    void operator=(const Vertex& V){
        value=V.value;
        vec=V.vec;
    }
    void add(Edge ptr,E val){
        vec.push_back({ptr,val});
    }
    friend bool operator==(const Vertex<T,E>& lhs,const Vertex<T,E>& rhs){
        return lhs.value==rhs.value;
    }
    friend bool operator==(const Vertex<T,E>& lhs,const T& rhs){
        return lhs.value==rhs;
    }
};
template<typename T,typename E>
struct Graph{
    typedef typename std::list<Vertex<T,E>>::iterator Edge;
    std::list<Vertex<T,E>> list;
    Graph(){}
    void add_vertex(T ver){
        Vertex<T, E> v(ver);
        list.push_back(v);
    }
    void add_edge(T start,T end,E edge_val){
        auto its=std::find(list.begin(),list.end(),start);
        auto ite=std::find(list.begin(),list.end(),end);
        (*its).add(ite,edge_val);
    }
    Edge get_vertex(T source){
        auto its=std::find(list.begin(),list.end(),source);
        return its;
    }
};
