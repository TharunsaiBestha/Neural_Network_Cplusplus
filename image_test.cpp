#include<opencv2/highgui.hpp>
#include<iostream>
int main(int argc,char** argv){
    cv::Mat image;
    image=cv::imread(argv[1],cv::IMREAD_COLOR);
    uchar* r=image.data;
    int w=*(r+1000);
    std::cout<<"("<<image.rows<<","<<image.cols<<")\n";
    std::cout<<image.total()<<" "<<image.dims<<" "<<w<<"\n";
    std::cout<<image.channels()<<" "<<image.depth()<<"\n";
}