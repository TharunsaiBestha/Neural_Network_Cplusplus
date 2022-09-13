#include<opencv2/highgui.hpp>
#include<string>
#include "Matrix3D.h"
#include "../matplotlib-cpp-master/matplotlibcpp.h"
struct Image{
cv::Mat image_mat;
Image(std::string str){
    image_mat=cv::imread(str,cv::IMREAD_COLOR);
}
template<typename T>
Matrix3D<T> to_3dMat(){
    Matrix3D<T> res(3);
    uint8_t* pixelPtr = (uint8_t*)image_mat.data;
    int cn = image_mat.channels();
    for(int i=0;i<3;i++){
        Matrix<T> temp(image_mat.rows,image_mat.cols);
        res.push_back(temp);
    }
    for(int i = 0; i < image_mat.rows; i++)
{
    for(int j = 0; j < image_mat.cols; j++)
    {
        res(2,i,j) = pixelPtr[i*image_mat.cols*cn + j*cn + 0]; // B
        res(1,i,j)= pixelPtr[i*image_mat.cols*cn + j*cn + 1]; // G
        res(0,i,j) = pixelPtr[i*image_mat.cols*cn + j*cn + 2]; // R
    }
}
return res;
}
};
template<typename T>
void Plot_mat(Matrix<T>& M){
    auto row=M.dim().first;
    auto col=M.dim().second;
    std::vector<T> v=M.get_vector();
    const T* ptr=&(v[0]);
    plt::imshow(ptr,row,col,1);
}