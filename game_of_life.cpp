#include "Matrix.h"
#include "../matplotlib-cpp-master/matplotlibcpp.h"
namespace plt=matplotlibcpp;
template<typename T>
void Random_mat(Matrix<T>& M,int n,int num){
srand(time(NULL));
auto row=M.dim().first;
auto col=M.dim().second;
for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
        M(i,j)=((rand()%n)==num);
    }
}
}
template<typename T>
void Update_cell(Matrix<T>& M,std::size_t r,std::size_t c){
auto row=M.dim().first;
auto col=M.dim().second;
int t_r=0,t_c=0;
int val=0;
for(int i=-1;i<2;i++){
    for(int j=-1;j<2;j++){
        t_r=r+i;
        t_c=c+j;
        if((t_r>0 && t_r<row) &&(t_c>0 && t_c<col)){
            val+=M(t_r,t_c);
        }
    }
}
if(M(r,c)){
    if(val!=2 && val!=3)M(r,c)=0;
}else{
    if(val==3)M(r,c)=1;
}
}
template<typename T>
void Update_GOL(Matrix<T>& M){
auto row=M.dim().first;
auto col=M.dim().second;
for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
        Update_cell(M,i,j);
    }
}
}
template<typename T>
void Plot_mat(Matrix<T>& M){
    auto row=M.dim().first;
    auto col=M.dim().second;
    std::vector<T> v=M.get_vector();
    const T* ptr=&(v[0]);
    plt::clf();
    plt::imshow(ptr,row,col,1);
    plt::pause(0.1);
}
int main(int argc,char** argv){
    int it=std::stoi(argv[1]);
    int n=std::stoi(argv[2]);
    int num=std::stoi(argv[3]);
    Matrix<float> M(200,200);
    Random_mat(M,n,num);
    for(int i=0;i<it;i++){
        Plot_mat(M);
        Update_GOL(M);
    }
}