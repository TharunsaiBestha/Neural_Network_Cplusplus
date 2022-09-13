#include "Graph_library.h"
#include<stack>
#include<queue>
#include<limits>
template<typename T,typename E>
struct DFS_function{
    typedef typename std::list<Vertex<T,E>>::iterator itr;
    T value;
    DFS_function(){}
    void operator=(itr set){
        value=(*set).value;
    }
    bool operator()(itr iterator){
        return (*iterator).value==value;
    }
};
template<typename T,typename E>
struct DFS{
    typedef typename std::list<Vertex<T,E>>::iterator itr;
    T source;
    std::vector<itr> visited;
    std::stack<itr> sta;
    DFS_function<T,E> fun;
    itr end;
    DFS(T& source,Graph<T,E>& G){
        itr t_itr=G.get_vertex(source);
        source=(*t_itr).value;
        sta.push(t_itr);
        visited.push_back(t_itr);
        end=G.list.end();
    }
    DFS(){}
    void operator()(T& source,Graph<T,E>& G){
        itr t_itr=G.get_vertex(source);
        source=(*t_itr).value;
        sta.push(t_itr);
        visited.push_back(t_itr);
        end=G.list.end();
    }
    std::pair<itr,bool> next_vertex(std::vector<itr>& visited,itr V){
    itr temp;
    for(auto i:(*V).vec){
        fun=i.first;
        if(visited.end()==std::find_if(visited.begin(),visited.end(),fun)){
            return {i.first,true};
        }
        temp=i.first;
    }
    return {temp,false};
}
    std::pair<itr,bool> next_vertex(){
        itr t_itr;
        std::pair<itr,bool> temp_itr;
        if(!sta.empty()){
            t_itr=sta.top();
            temp_itr=next_vertex(visited,t_itr);
            if(temp_itr.second){visited.push_back(temp_itr.first);sta.push(temp_itr.first);return {temp_itr.first,true};}
            else{
                t_itr=sta.top();
                sta.pop();
                return {t_itr,false};
            }
            //return temp_itr.first;
            }
            else{
                return {end,true};
            }
        }
    itr next(){
        std::pair<itr,bool> temp;
        temp=next_vertex();
        while(temp.first!=end && !temp.second){
            temp=next_vertex();
            if(temp.first==end && temp.second)return end;
        }
        return temp.first;
    }
};
template<typename T,typename E>
struct BFS{
    typedef typename std::list<Vertex<T,E>>::iterator itr;
    T source;
    std::vector<itr> visited;
    std::queue<itr> que;
    DFS_function<T,E> fun;
    itr end;
    BFS(T& source,Graph<T,E>& G){
        itr t_itr=G.get_vertex(source);
        source=(*t_itr).value;
        que.push(t_itr);
        visited.push_back(t_itr);
        end=G.list.end();        
    }
    void add_to_queue(std::vector<itr>& vis,std::queue<itr>& q,itr iterator){
        for(auto i:(*iterator).vec){
            fun=i.first;
            if(vis.end()==std::find_if(vis.begin(),vis.end(),fun)){
                q.push(i.first);
                vis.push_back(i.first);
            }
        }
    }
    itr next_vertex(){
        itr t_itr;
        std::pair<itr,bool> temp_itr;
        if(!que.empty()){
            t_itr=que.front();
            //if(temp_itr.second){visited.push_back(temp_itr.first);que.push(temp_itr.first);}
            add_to_queue(visited,que,t_itr);
            que.pop();
            return t_itr;
        }
        else{
            return end;
        }
    }
};
template<typename T,typename E>
struct Topological_Sort{
    typedef typename std::list<Vertex<T,E>>::iterator itr;
    DFS<T,E> DFS_var;
    itr end;
    Topological_Sort(T& source,Graph<T,E>& G){
        DFS_var(source,G);
        itr t_itr=G.get_vertex(source);
        end=G.list.end();
    }
    itr next(){
        auto pair=DFS_var.next_vertex();
        while(!pair.second && pair.first!=end){
            pair=DFS_var.next_vertex();
        }
        return pair.first;
    }
};
template<typename T,typename E>
using itr=typename std::list<Vertex<T,E>>::iterator;
template<typename T,typename E>
std::pair<itr<T,E>,E> Dijikstra(Graph<T,E>& G){
    std::vector<std::pair<itr<T,E>,E>> vec;
    for(auto i=G.list.begin();i!=G.list.end();++i){
        vec.push_back({i,std::numeric_limits<E>::max()});
    }

}