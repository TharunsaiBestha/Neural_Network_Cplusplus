#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
template<typename T,typename V>
class Edge{
    public:
    Edge(T v,V& one,V& two){
        value=v;
        rone=&one;
        rtwo=&two;
    }
    Edge(){
        value=T{};
        rone=NULL;
        rtwo=NULL;
    }
    Edge(const Edge& x){
        value=x.value;
        rone=x.rone;
        rtwo=x.rtwo;
    }
    void operator=(const Edge& x){
        value=x.value;
        rone=x.rone;
        rtwo=x.rtwo;
    }
    friend bool operator==(const Edge& lhs,const Edge& rhs){
        if((lhs.rone->getValue()==rhs.rone->getValue())&&(lhs.rtwo->getValue()==rhs.rtwo->getValue()))
        return lhs.value==rhs.value;
        else{return false;}
    }
    friend bool operator!=(const Edge& lhs,const Edge& rhs){
        return !(lhs==rhs);
    }
    std::pair<T,T> nextelem(){
        return {rone->getValue(),rtwo->getValue()};
    }
    bool is_vertex(T x){
        return rone->getValue()==x || rtwo->getValue()==x;
    }
    T getValue(){return value;}
    T value;
    V* rone;
    V* rtwo;
};
template<typename T,typename E>
class Vertex{
    public:
    Vertex(T v){
        value=v;
    }
    Vertex(){
        value=T{};
    }
    Vertex(const Vertex& v){
        value=v.getValue();
        Evec.clear();
        for(int i=0;i<v.degree();i++){
            Evec.push_back(v[i]);
        }}
        Vertex(Vertex&& v){
        value=v.getValue();
        Evec.clear();
        for(int i=0;i<v.degree();i++){
            Evec.push_back(v[i]);
        }
    }
    void operator=(const Vertex& v){
        value=v.getValue();
        Evec.clear();
        for(int i=0;i<v.degree();i++){
            Evec.push_back(v[i]);
        }}
    void operator=(Vertex&& v){
        value=v.getValue();
        Evec.clear();
        for(int i=0;i<v.degree();i++){
            Evec.push_back(v[i]);
        }
    }
    void update(Edge<E,Vertex<T,E>>& x){
        Evec.push_back(x);
    }
    std::size_t degree() const{
        return Evec.size();
    }
    T getValue() const{
        return value;
    }
    friend bool operator==(const Vertex& lhs,const Vertex& rhs){
        return  lhs.getValue()==rhs.getValue();
    }
    friend bool operator!=(const Vertex& lhs,const Vertex& rhs){
        return !(lhs==rhs);
    }
    friend bool operator<(const Vertex& lhs,const Vertex& rhs){
        return lhs.getValue()<rhs.getValue();
    }
    friend bool operator>(const Vertex& lhs,const Vertex& rhs){
        return rhs<lhs;
    }
    friend bool operator<=(const Vertex& lhs,const Vertex& rhs){
        return !(lhs>rhs);
    }
    friend bool operator>=(const Vertex& lhs,const Vertex& rhs){
        return !(lhs<rhs);
    }
    Edge<E,Vertex<T,E>> operator[](std::size_t n) const {
        return Evec[n];
    }
    Edge<E,Vertex<T,E>> min_edge(){
        Edge<E,Vertex<T, E>> temp{};
        T tempe=T{};
        for(auto& i:Evec){
           if(i.getValue()<=tempe){tempe=i.getValue();
           temp=i;}
        }
        return temp;
    }
    T value;
    std::vector<Edge<E,Vertex<T,E>>> Evec;
};
template<typename T,typename E>
class Graph{
    public:
    Graph(int n){
        lver.reserve(n);
    }
    Vertex<T,E>& operator[](std::size_t n){
        return lver[n];
    }
    std::pair<std::size_t,std::size_t> minmax_degree(){
        std::size_t min=std::numeric_limits<std::size_t>::max();
        std::size_t max=std::numeric_limits<std::size_t>::min();
        std::size_t temp;
        for(auto& i:lver){
            temp=i.degree();
            if(temp<=min)min=temp;
            if(temp>=max)max=temp;
        }
        return {min,max};
    }
    bool is_connected(){
        std::size_t N=order();
        std::pair<std::size_t,std::size_t> res;
        res=minmax_degree();
        return res.first>=(N-1)/2;
    }
    std::size_t order(){
        return lver.size();
    }
    void addVertex(T x){
        Vertex<T,E> tver(x);
        lver.push_back(std::move(tver));
    }
    Vertex<T,E>& findVertex(T value){
        Vertex<T,E> temp=NULL;
        for(auto& i:lver){
            if(i.getValue()==value){
                return i;
            }
        }
        return temp;
    }
    void addEdge(T onev,T secv,E edgev){
        Vertex<T,E>& tone=findVertex(onev);
        Vertex<T,E>& tsec=findVertex(secv);
        Edge<E,Vertex<T,E>> tedge(edgev,tone,tsec);
        AddEdge(tedge);
    }
    Edge<E,Vertex<T,E>> min_edge(Vertex<T,E>& Ver){
     return Ver.min_edge();   
    }
    std::vector<Vertex<T,E>> lver;
};
template<typename T,typename E>
void AddEdge(Edge<E,Vertex<T,E>>& x){
        x.rone->update(x);
        x.rtwo->update(x);
    }
template<typename T,typename E>
 Vertex<T,E>& next_vertex(Vertex<T,E>& V,Edge<E,Vertex<T,E>>& Ed){
        std::pair<T,T> tempe;
        T tempv=V.getValue();
        tempe=Ed.nextelem();
        return tempv==tempe.first?*(Ed.rtwo):*(Ed.rone);
    }
template<typename T,typename E>
std::vector<Vertex<T, E>> all_neighbour_vertex(Vertex<T,E>& V){
    std::vector<Vertex<T, E>> vec;
    Edge<E,Vertex<T,E>> temp;
    for(int i=0;i<V.degree();i++){
        temp=V[i];
        vec.push_back(next_vertex(V,temp));
    }
    return vec;
}
//  int main(){
//      Graph<char,int> test_Graph(6);
//      test_Graph.addVertex('a');
//      test_Graph.addVertex('b');
//      test_Graph.addVertex('c');
//      test_Graph.addVertex('d');
//      test_Graph.addVertex('e');
//      test_Graph.addVertex('f');
//      test_Graph.addEdge('a','c',0);
//      test_Graph.addEdge('a','b',1);
//      test_Graph.addEdge('b','e',4);
//      test_Graph.addEdge('b','c',2);
//      test_Graph.addEdge('c','e',3);
//      test_Graph.addEdge('c','d',2);
//      test_Graph.addEdge('d','e',4);
//      test_Graph.addEdge('d','f',5);
//      test_Graph.addEdge('e','f',5);
//      auto res=prim(test_Graph);
//      for(auto& i:res){
//          std::cout<<'('<<i.rone->getValue()<<','<<i.rtwo->getValue()<<')'<<'\n';
//      }
//  }