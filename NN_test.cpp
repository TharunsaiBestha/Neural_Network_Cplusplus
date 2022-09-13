#include "NN_objects.h"
#include "NN_objects.h"
#include "NN_Fun.h"
#include<iostream>
int main(){
    Matrix<double> W=read_from_file<double>("W.txt");
    Matrix<double> Y_real=read_from_file<double>("Y_real.txt");
    Matrix<double> Y;
    Matrix<double> temp;
    SoftMax_2d<double> fun;
    NN_Error<double,Squared_Error<double>,Squared_Error_Backprop<double>> error_fun;
    error_fun.Real_output(Y_real);
    temp=fun.forward(W);
    std::cout<<temp;
    temp=error_fun.back_propagation(temp);
    temp=fun.back_propagation(temp);
    std::cout<<temp;
}