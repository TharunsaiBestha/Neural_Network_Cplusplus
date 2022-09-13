#include "Self_Attention.h"
#include "NN_Fun.h"
int main(){
    Matrix<double> Wv=read_from_file<double>("Wv.txt");
    Matrix<double> Wq=read_from_file<double>("Wq.txt");
    Matrix<double> Wk=read_from_file<double>("Wk.txt");
    Matrix<double> X=read_from_file<double>("X.txt");
    Matrix<double> Y_real=read_from_file<double>("Y_real.txt");
    NN_Error<double,Squared_Error<double>,Squared_Error_Backprop<double>> SE;
    Self_Attention<double> SA(Wq,Wk,Wv,0.01);
    Matrix<double> temp;
    SE.Real_output(Y_real);
    temp=SA.forward(X);
    temp=SE.back_propagation(temp);
    temp=SA.back_propagation(temp);
    std::cout<<SA.Wv.del_weight;
    std::cout<<SA.Wq.del_weight;
    std::cout<<SA.Wk.del_weight;
    std::cout<<temp;
}