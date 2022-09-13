#include<fstream>
#include<string>
#include "Matrix.h"
struct image{
    std::size_t row;
    std::size_t col;
    std::size_t color;
    Matrix<std::int8_t> M;

}