#include "Matrix.h"
int main(){
    Matrix<double> M(50,50);
    init_rand(M,10);
    std::cout<<M;
    std::cout<<inverse(M);
    std::cout<<M*inverse(M);
}