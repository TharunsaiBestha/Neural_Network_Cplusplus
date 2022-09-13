#include "Matrix.h"
template<typename T>
struct Matrix3D{
    std::vector<Matrix<T>> vec_Matrix;
    Matrix3D(){}
    Matrix3D(std::size_t k){
        vec_Matrix.reserve(k);
    }
    Matrix3D(const Matrix3D& CNN_M){
        for(std::size_t i=0;i<CNN_M.size();i++){
            vec_Matrix.push_back(CNN_M[i]);
        }
    }
    void operator=(const Matrix3D& CNN_M){
        for(std::size_t i=0;i<CNN_M.size();i++){
            vec_Matrix.push_back(CNN_M[i]);
        }   
    }
    void operator=(Matrix3D& CNN_M){
        for(std::size_t i=0;i<CNN_M.size();i++){
            vec_Matrix.push_back(CNN_M[i]);
        }   
    }
    void operator=(Matrix3D&& CNN_M){
        for(std::size_t i=0;i<CNN_M.size();i++){
            vec_Matrix.push_back(std::move(CNN_M[i]));
        }   
    }
    void operator+=(const Matrix3D& CNN_M){
        for(std::size_t i=0;i<CNN_M.size();i++){
            vec_Matrix[i]+=CNN_M[i];
        }
    }
    void add(Matrix<T>& M){
        vec_Matrix.push_back(M);
    }
    void add(Matrix<T>&& M){
        vec_Matrix.push_back(std::move(M));
    }
    std::size_t size() const {
        return vec_Matrix.size();
    }
    std::size_t size(){
        return vec_Matrix.size();
    }
    std::vector<std::size_t> dim(){
        return std::vector<std::size_t>{vec_Matrix.size(),vec_Matrix[0].first,vec_Matrix[0].second};
    }
    Matrix<T>& operator[](std::size_t i){
        return vec_Matrix[i];
    }
    Matrix<T> operator[](std::size_t i)const {
        return vec_Matrix[i];
    }
    T& operator()(std::size_t i,std::size_t j,std::size_t k){
        return vec_Matrix[i].operator()(i,j);
    } 
};
template<typename T>
Matrix3D<T> operator*(const T val,Matrix3D<T>& mat3d){
    Matrix3D<T> res(mat3d.size());
    for(std::size_t i=0;i<mat3d.size();i++){
        res.add(val*mat3d[i]);
    }
    return res;
}
template<typename T>
Matrix3D<T> operator+(const Matrix3D<T>& lhs,const Matrix3D<T>& rhs){
    Matrix3D<T> res;
    for(std::size_t i=0;i<lhs.size();i++){
        res.add(lhs[i]+rhs[i]);
    }
    return res;
}
template<typename T>
Matrix3D<T> operator+(Matrix3D<T>&& lhs,const Matrix3D<T>& rhs){
        lhs+=rhs;
        return lhs;
    }
template<typename T>
Matrix3D<T> operator+(Matrix3D<T>& lhs,Matrix3D<T>&& rhs){
        rhs+=lhs;
        return rhs;
    }
template<typename T>
Matrix3D<T> operator+(Matrix3D<T>&& lhs,Matrix3D<T>&& rhs){
        rhs+=lhs;
        return rhs;
    }
template<typename T>
Matrix3D<T> operator*(const Matrix3D<T>& lhs,const Matrix3D<T>& rhs){
    Matrix3D<T> res;
    for(std::size_t i=0;i<lhs.size();i++){
        res.add(lhs[i]*rhs[i]);
    }
    return res;
}
template<typename T>
std::ostream& operator<<(std::ostream& os,const Matrix3D<T>& m){
    int n=m.size();
        for(int i=0;i<n;i++){
            os<<m[i];
        }
        return os;
}
template<typename T>
Matrix3D<T> Convolve3D(Matrix3D<T>& images,Matrix3D<T>& filters){
    Matrix3D<T> res;
    for(int i=0;i<images.size();i++){
        res.add(Convolve2D(images[i],filters[i]));
    }
    return res;
}
template<typename T>
Matrix3D<T> mirror_image3D(Matrix3D<T>& images){
    Matrix3D<T> res;
    for(std::size_t i=0;i<images.size();i++){
        res.add(mirror_image(images[i]));
    }
    return res;
}
template<typename T>
Matrix3D<T> stride3D(Matrix3D<T>& images,std::size_t stride){
    Matrix3D<T> res;
    for(std::size_t i=0;i<images.size();i++){
        res.add(stride(images[i],stride,stride));
    }
    return res;
}