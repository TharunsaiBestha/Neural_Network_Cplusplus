#include<vector>
#include<complex>
#include<random>
template<typename T,typename Fun>
std::pair<T,T> Bisection_method(Fun& f,T a,T b,int it){
    T temp;
    for(int i=0;i<it;i++){
        temp=(a+b)/2;
        if(f(temp)<0.0)a=temp;
        else b=temp;
    }
    return {a,b};
}
template<typename T,typename Fun>
T Regula_falsi(Fun& f,T a,T b,int it){
    T temp;
    for(int i=0;i<it;i++){
        temp=((b-a)/(f(b)-f(a)))*f(a);
        temp=a-temp;
        if(f(a)*f(temp)>0)a=temp;
        else b=temp;
    }
    return temp;
}
template<typename T,typename Fun,typename Fun_diff>
T Newton_Raphson(Fun& f,Fun_diff& f_diff,T init,int it){
    T next;
    for(int i=0;i<it;i++){
        next=init-(f(init)/f_diff(init));
        init=next;
    }
    return next;
}
template<typename T,typename Fun_diff>
struct Euler_method_inst{
    T operator()(T x,T y,T h,Fun_diff& f){
    return y+h*f(x,y);
}};
template<typename T,typename Fun_diff>
struct Runge_method_inst{
    T operator()(T x,T y,T h,Fun_diff& f){
    T k1,k2,k_t,k3;
    k1=h*f(x,y);
    k2=h*f(x+h/2,y+k1/2);
    k_t=h*f(x+h,y+k1);
    k3=h*f(x+h,y+k_t);
    return (k1+4*k2+k3)/6;
}};
template<typename T,typename Fun_diff>
struct Runge_kutta_method_inst{
    T operator()(T x,T y,T h,Fun_diff& f){
    T k1,k2,k3,k4;
    k1=h*f(x,y);
    k2=h*f(x+h/2,y+k1/2);
    k3=h*f(x+h/2,y+k2/2);
    k4=h*f(x+h,y+k3);
    return (k1+2*k2+2*k3+k4)/6;
}};
struct Trapezoidal_Rule{
    template<typename T,typename R,typename Fun>
    R operator()(T init,T end,T step,Fun& fun,R R_init){
        R sum1;
        R sum2=T{};
        R co_eff=2;
        T temp;
        std::size_t iter=(end-init)/step;
        sum1=fun(init)+fun(end);
        temp=init+step;
        for(std::size_t i=1;i<iter;i++){
            sum2+=fun(temp);
            temp+=step;
        }
        return R_init+(step/co_eff)*(sum1+co_eff*sum2);
    }
};
struct Simpson_one_third_rule{
    template<typename T,typename R,typename Fun>
    R operator()(T init,T end,T step,Fun& fun,R R_init){
        R sum1;
        R sum2=T{};
        R sum3=T{};
        R co_eff1=3,co_eff2=4,co_eff3=2;
        T temp;
        std::size_t iter=(end-init)/step;
        sum1=fun(init)+fun(end);
        temp=init+step;
        for(std::size_t i=1;i<iter;i++){
            if(i&1)sum2+=fun(temp);
            else{
                sum3+=fun(temp);
            }
            temp+=step;
        }
        return R_init+(step/co_eff1)*(sum1+co_eff2*sum2+co_eff3*sum3);
    }
};
struct Simpson_three_eight_rule{
    template<typename T,typename R,typename Fun>
    R operator()(T init,T end,T step,Fun& fun,R R_init){
        R sum1;
        R sum2=T{};
        R sum3=T{};
        T temp;
        R co_eff1=3,co_eff2=8,co_eff3=2;
        std::size_t iter=(end-init)/step;
        sum1=fun(init)+fun(end);
        temp=init+step;
        for(std::size_t i=1;i<iter;i++){
            if(i%3==0)sum3+=fun(temp);
            else{
                sum2+=fun(temp);
            }
            temp+=step;
        }
        return R_init+(co_eff1*step/co_eff2)*(sum1+co_eff1*sum2+co_eff3*sum3);
    }
};
template<typename T>
std::complex<T> com_exp(T f,T x){
    return std::polar(1.0,2*M_PI*f*x);
}
template<typename T,typename Fun,typename Method>
 std::vector<std::complex<T>> fourier_series(Fun& f,Method& M,T init,T end,T step,std::size_t freq,std::size_t N){
     std::complex<T> res;
     std::complex<T> R_init(0,0);
     std::vector<std::complex<T>> co_eff;
     double fr=1.0*freq;
     auto fun=[&](double x){return f(x)*com_exp(fr,x);};
     for(std::size_t i=0;i<N;i++){
         fr=i*freq;
         res=M(init,end,step,fun,R_init);
         co_eff.push_back(res);
     }
     return co_eff;
  }
template<typename T,typename R,typename Fun>
R Monte_Carlo_Int(Fun& f,T a,T b,std::size_t iter,R init){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(a,b);
    T res=T{};
    for(std::size_t i=0;i<iter;i++){
        res+=f(dist(gen));
    }
    return init+((b-a)/iter)*res;
}
template<template<class,class> class Method>
struct Integration{
template<typename T,typename Fun_diff>
std::vector<T> operator()(std::vector<T>& x,T y0,T h,Fun_diff& f){
std::vector<T> y;
auto fun=Method<T,Fun_diff>();
y.reserve(x.size());
T y_temp;
for(auto i:x){
    y_temp=y0+fun(i,y0,h,f);
    y0=y_temp;
    y.push_back(y_temp);
}
return y;
}};