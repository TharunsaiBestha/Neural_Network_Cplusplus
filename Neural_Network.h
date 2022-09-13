#include "Matrix.h"
#include<math.h>
struct sigmoid{
    float operator()(float x){
        return 1/(1+exp(x));
    }
};
template<typename T>
class Neural_Network{
    public:
    Neural_Network(std::vector<int>& v){
        Parameters.reserve(v.size()-1);
        for(int i=0;i<v.size()-1;i++){
            Parameters.push_back(Matrix<T>(v[i+1],v[i]));
        }
    }
    Matrix<T> Forward(Matrix<T>& Input){
        Matrix<T> temp;
        temp=Parameters[0]*Input;
        for(auto i=1;i<Parameters.size();i++){
            temp=Parameters[i]*temp;
        }
        return temp;
    }
    private:
    std::vector<Matrix<T>> Parameters; 
};