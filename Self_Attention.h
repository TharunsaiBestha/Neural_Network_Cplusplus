#include "NN_objects.h"
template<typename TYPE>
struct Self_Attention{
    NN_Matrix<TYPE> Wq;
    NN_Matrix<TYPE> Wk;
    NN_Matrix<TYPE> Wv;
    Matrix<TYPE> Q;
    Matrix<TYPE> K;
    Matrix<TYPE> V;
    Matrix<TYPE> T;
    Matrix<TYPE> S;
    Matrix<TYPE> Z;
    Matrix<TYPE> input;
    SoftMax_2d<double> SM;
    Self_Attention(Matrix<TYPE>& W_q,Matrix<TYPE>& W_k,Matrix<TYPE>& W_v,TYPE lr):Wq(W_q,lr),Wk(W_k,lr),Wv(W_v,lr),SM(){}
    Matrix<TYPE> forward(Matrix<TYPE>& in){
        Matrix<TYPE> temp;
        input=in;
        Q=Wq.forward(in);
        K=Wk.forward(in);
        V=Wv.forward(in);
        T=transpose(K)*Q;
        temp=transpose(T);
        temp=SM.forward(temp);
        S=transpose(temp);
        Z=V*S;
        return Z;
    } 
    Matrix<TYPE> back_propagation(Matrix<TYPE> out){
        Matrix<TYPE> temp;
        std::pair<std::pair<Matrix<TYPE>,Matrix<TYPE>>,Matrix<TYPE>> res;
        temp=out*transpose(S);
        res.second=Wv.back_propagation(temp);
        temp=transpose(V)*out;
        temp=transpose(temp);
        temp=SM.back_propagation(temp);
        temp=transpose(temp);
        temp=K*temp;
        res.first.first=Wq.back_propagation(temp);
        temp=transpose(V)*out;
        temp=transpose(temp);
        temp=SM.back_propagation(temp);
        temp=transpose(temp);
        temp=temp*transpose(Q);
        temp=transpose(temp);
        res.first.second=Wk.back_propagation(temp);
        temp=res.first.first+res.first.second;
        temp=temp+res.second;
        return temp;
    }
    void update(){
        Wq.update();
        Wv.update();
        Wk.update();
    }
};