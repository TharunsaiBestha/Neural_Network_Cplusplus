//#include "NN_objects.h"
#include "Matrix.h"
int main(){
    Matrix<double> M(4,4);
    init_rand(M,10);
    std::cout<<M;
    auto res=Dolittle_LU(M);
    std::cout<<res.first;
    std::cout<<res.second;
    std::cout<<res.first*res.second;
    // Matrix<int> W(2,2);
    // Matrix<int> I(4,4);
    // init_rand(W,10);
    // init_rand(I,10);
    // Matrix3D<int> weights(1);
    // Matrix3D<int> Input(1);
    // weights.add(W);
    // Input.add(I);
    // CNN_Matrix<int> CNN_M(weights,1);
    // //CNN_M.forward(Input);
    // std::cout<<weights;
    // std::cout<<Input;
    // std::cout<<CNN_M.forward(Input);
}