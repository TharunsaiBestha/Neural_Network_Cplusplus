#include "Matrix3D.h"
#pragma once
//#include<bits/stdc++.h>
template<typename T>
struct NN_Objects{
    virtual Matrix<T> forward(Matrix<T>& input)=0;
    virtual Matrix<T> back_propagation(Matrix<T>& output)=0;
};
template<typename T>
struct NN_Matrix{
    Matrix<T> input;
    Matrix<T> weight;
    Matrix<T> del_weight;
    T learning_rate;
    NN_Matrix(Matrix<T>& initial_Weights,T lr){
        weight=initial_Weights;
        learning_rate=lr;
    }
    Matrix<T> forward(Matrix<T>& in){
        input=in;
        return weight*input;
    }
    Matrix<T> back_propagation(Matrix<T>& output){
        del_weight=del_W(output);
        return transpose(weight)*output;
    }
    Matrix<T> del_W(Matrix<T>& output){
        Matrix<T> delta_weight;
        delta_weight=output*transpose(input);
        return delta_weight;
    }
    void update(){
        T temp=-learning_rate;
        weight+=temp*del_weight;
    }
};
template<typename T,typename FF,typename BP>
struct NN_Activation{
    FF Forward;
    BP Back_Prop;
    Matrix<T> output;
    NN_Activation():Forward(FF()),Back_Prop(BP()){}
    Matrix<T> forward(Matrix<T>& in){
        Transform(in,Forward);
        output=in;
        return output;
    }
    Matrix<T> back_propagation(Matrix<T>& in){
        //auto f=[](T temp=transpose(temp);
    }
};
template<typename T,typename BP>
struct SoftMax{
    Matrix<T> output;
    BP Back_Prop;
    SoftMax():Back_Prop(BP()){}
    Matrix<T> forward(Matrix<T>& in){
        auto fun=[](T& a,T& b){return a+std::exp(b);};
        T res=accumulate(in,fun,T{});
        auto fun2=[&](T& x){return std::exp(x)/res;};
        Transform(in,fun2);
        output=in;
        return output;
    }
Matrix<T> back_propagation(Matrix<T>& in){
    Matrix<T> res(in.dim().first,in.dim().first);
    for(std::size_t i=0;i<res.dim().first;i++){
        for(std::size_t j=0;j<res.dim().second;j++){
            res(i,j)=(i==j)?output(i,0)*(1-output(i,0)):-output(i,0)*output(j,0);
            }
    }
    return res*in;
}
};
template<typename T>
struct SoftMax_2d{
    Matrix<T> output;
    //BP Back_Prop;
    SoftMax_2d(){}
    void back_propagation_row(typename std::vector<T>::iterator start_in,typename std::vector<T>::iterator end_in,typename std::vector<T>::iterator start_out,
    typename std::vector<T>::iterator end_out){
        std::size_t n=std::distance(start_in,end_in);
        Matrix<T> res(n,n);
        Matrix<T> out(n,1);
        Matrix<T> in(n,1);
        std::vector<T>& v_out=out.get_vector();
        std::vector<T>& v_in=in.get_vector();
        std::size_t a=0;
        for(auto i=start_out;i!=end_out;++i){
            v_out[a]=*i;
            a++;
        }
        a=0;
        for(auto i=start_in;i!=end_in;++i){
            v_in[a]=*i;
            a++;
        }
        for(std::size_t i=0;i<n;i++){
            for(std::size_t j=0;j<n;j++){
                res(i,j)=(i==j)?out(i,0)*(1-out(i,0)):-out(i,0)*out(j,0);
            }
        }
        a=0;
        out=res*in;
        for(auto i=start_out;i!=end_out;++i){
            *i=v_out[a];
            a++;
        }
    }
    Matrix<T> forward(Matrix<T>& in){
        std::size_t n=in.dim().second;
        std::vector<T> temp_vec(in.dim().first);
        std::size_t j=0;
        auto fun=[](T& a,T& b){return a+std::exp(b);};
        auto fun2=[&](T x){return std::exp(x)/temp_vec[j];};
        auto start=in.get_vector().begin();
        auto end=in.get_vector().begin();
        for(std::size_t i=0;i<in.dim().first;i++){
            std::advance(end,n);
            temp_vec[i]=std::accumulate(start,end,T{},fun);
            std::advance(start,n);
        }
        start=in.get_vector().begin();
        end=in.get_vector().begin();
        for(j=0;j<in.dim().first;j++){
            std::advance(end,n);
            std::transform(start,end,start,fun2);
            std::advance(start,n);
        }
        output=in;
        return output;
    }
    Matrix<T> back_propagation(Matrix<T>& in){
        Matrix<T> out;
        out=output;
        auto start_out=out.get_vector().begin();
        auto end_out=out.get_vector().begin();
        auto start_in=in.get_vector().begin();
        auto end_in=in.get_vector().begin();
        std::size_t n=out.dim().second;
        for(std::size_t i=0;i<in.dim().first;i++){
            std::advance(end_in,n);
            std::advance(end_out,n);
            back_propagation_row(start_in,end_in,start_out,end_out);
            std::advance(start_in,n);
            std::advance(start_out,n);
        }
        return out;
    }  
};
template<typename T,typename FF,typename BP>
struct NN_Error{
    FF Forward;
    BP Back_Prop;
    Matrix<T> real_output;
    NN_Error():Forward(FF()),Back_Prop(BP()){}
    void Real_output(Matrix<T>& out){
        real_output=out;
    }
    Matrix<T> forward(Matrix<T>& in){
        Matrix<T> res(in.dim().first,in.dim().second);
        Transform(in,real_output,res,Forward);
        return res;
    }
    Matrix<T> back_propagation(Matrix<T>& output){
    Transform(output,real_output,output,Back_Prop);
    return output;
    }
};
template<typename T>
struct CNN_Matrix{
    Matrix3D<T> input;
    Matrix3D<T> weight;
    T learning_rate;
    CNN_Matrix(Matrix3D<T>& initial_weights,T lr){
        weight=initial_weights;
        learning_rate=lr;
    }
    Matrix3D<T> forward(Matrix3D<T>& in){
        input=in;
        return Convolve3D(input,weight);
    }
    Matrix3D<T> back_propagation(Matrix3D<T>& output){
        Matrix3D<T> delta_weights;
        Matrix3D<T> mirror_weights,temp_out,res;
        mirror_weights=mirror_image3D(weight);
        temp_out=stride3D(output,weight.size()-1);
        res=Convolve3D(temp_out,mirror_weights);
        delta_weights=Convolve3D(input,output);
        update(delta_weights);
        return res;
    }
    void update(Matrix3D<T>& delta_weights){
        T temp=-learning_rate;
        weight+=temp*delta_weights;
    }
};