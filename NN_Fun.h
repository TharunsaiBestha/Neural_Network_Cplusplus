#include<math.h>
template<typename T>
struct Sigmoid{
    T operator()(T in){
        return 1/(1+std::exp(-in));
    }
};
template <typename T>
struct Grad_Sigmoid{
    T operator()(T in){
        return in*(1.0-in);
    }
};
template<typename T>
struct Squared_Error{
    T operator()(T out,T real_out){
        return (out-real_out)*(out-real_out)/2.0;
    }
};
template<typename T>
struct Squared_Error_Backprop{
    T operator()(T out,T real_out){
        return (out-real_out);
    }
};
template<typename T>
struct Cross_Entropy{
    T operator()(T out,T real_out){
        return -real_out*std::log(out);
    }
};
template<typename T>
struct Cross_Entropy_Backprop{
    T operator()(T out,T real_out){
        return -real_out/out;
    }
};
template<typename T>
struct Softmax_Backprop{
    T operator()(T in){
        return in*(1.0-in);
    }
};