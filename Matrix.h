//Author :Bestha Gaddam Tharun Sai
#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include <bits/stdc++.h>
#include<limits>
template<typename T>
class Matrix
{
    private:
    typedef  T Mat_Type;
    std::vector<T> vec;
    std::pair<std::size_t,std::size_t> d;
    public:
    Matrix(){};
    Matrix(std::size_t rows,std::size_t col,T val=T{}){
        d.first=rows;
        d.second=col;
        vec.reserve(rows*col);
        for(int i=0;i<rows*col;i++){
            vec.push_back(val);
        }
    }
    Matrix(std::vector<T>& v,std::size_t rows,std::size_t col){
        vec=v;
        d.first=rows;
        d.second=col;
    }
    Matrix(const Matrix& M){
        vec=M.get_vector();
        d=M.dim();
    }
    Matrix(Matrix& M){
        vec=M.get_vector();
        d=M.dim();
    }
    Matrix(Matrix&& M)noexcept{
        vec=std::move(M.get_vector());
        d=std::move(M.dim());
     //   std::cout<<"R value constructor"<<"\n";
    }
    void set_dim(std::size_t rows,std::size_t col,T val=T{}){
        d.first=rows;
        d.second=col;
        vec.reserve(rows*col);
        for(int i=0;i<rows*col;i++){
            vec.push_back(val);
        }
    }
    void operator=(const Matrix& M){
        vec=M.get_vector();
        d=M.dim();
    }
    void operator=(Matrix&& M)noexcept{
        vec=std::move(M.get_vector());
        d=std::move(M.dim());
    //    std::cout<<"R value assignment"<<"\n";
    }
    void operator=(std::vector<T>& V){
        vec=V;
    }
    void operator=(T val){
        std::fill(vec.begin(),vec.end(),val);
    }
    T& operator()(std::size_t row,std::size_t col){
        return vec[d.second*(row)+(col)];
    }
    T operator()(std::size_t row,std::size_t col)const{
        return vec[d.second*(row)+(col)];
    }
    void operator+=(const Matrix& M){
        if(d!=M.dim())
        set_dim(M.dim().first,M.dim().second);
        for(int i=0;i<M.dim().first;i++){
            for(int j=0;j<M.dim().second;j++){
                vec[i*M.dim().second+j]+=M(i,j);
            }
        }
    }
    void operator+=(Matrix&& M){
        if(d!=M.dim())
        set_dim(M.dim().first,M.dim().second);
        for(int i=0;i<M.dim().first;i++){
            for(int j=0;j<M.dim().second;j++){
                vec[i*M.dim().second+j]+=M(i,j);
            }
        }
    }
    void operator-=(const Matrix& M){
        for(int i=0;i<M.dim().first;i++){
            for(int j=0;j<M.dim().second;j++){
                vec[i*M.dim().second+j]-=M(i,j);
            }
        }
    }
    void operator-=(Matrix&& M){
        for(int i=0;i<M.dim().first;i++){
            for(int j=0;j<M.dim().second;j++){
                vec[i*M.dim().second+j]-=M(i,j);
            }
        }
    }
    std::vector<T>& get_vector(){
        return vec;
    }
    std::vector<T> get_vector() const {
        return vec;
    }
    std::pair<std::size_t,std::size_t>& dim(){
        return d;
    }
    std::pair<std::size_t,std::size_t> dim() const {
        return d;
    }
    void set_dims(std::size_t rows,std::size_t cols){
        d.first=rows;
        d.second=cols;
    }
    ~Matrix(){
    }
};
template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs,const Matrix<T>& rhs){
        std::pair<std::size_t,std::size_t> temp_d=lhs.dim();
        Matrix<T> temp(temp_d.first,temp_d.second);
        temp+=lhs;
        temp+=rhs;
        return temp;
    }
template<typename T>
Matrix<T> operator+(Matrix<T>&& lhs,const Matrix<T>& rhs){
        lhs+=rhs;
        return lhs;
    }
template<typename T>
Matrix<T> operator+(Matrix<T>& lhs,Matrix<T>&& rhs){
        rhs+=lhs;
        return rhs;
    }
template<typename T>
Matrix<T> operator+(Matrix<T>&& lhs,Matrix<T>&& rhs){
        rhs+=lhs;
        return rhs;
    }
template<typename T>
Matrix<T> operator+(const T val,const Matrix<T>& rhs){
        std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        Matrix<T> temp(temp_d.first,temp_d.second);
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                temp(i,j)=val+rhs(i,j);
            }
        }
        return temp;
}
template<typename T>
Matrix<T> operator+(const T val,Matrix<T>&& rhs){
    std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                rhs(i,j)=val+rhs(i,j);
            }
        }
    return rhs;}
template<typename T>
Matrix<T> operator+(const Matrix<T>& rhs,const T val){
    return val+rhs;}
template<typename T>
Matrix<T> operator+(Matrix<T>&& rhs,const T val){
    return val+std::move(rhs);}
template<typename T>
Matrix<T> operator-(const Matrix<T>& lhs,const Matrix<T>& rhs){
        std::pair<std::size_t,std::size_t> temp_d=lhs.dim();
        Matrix<T> temp(temp_d.first,temp_d.second);
        temp-=lhs;
        temp-=rhs;
        return temp;
    }
template<typename T>
Matrix<T> operator-(Matrix<T>&& lhs,const Matrix<T>& rhs){
        lhs-=rhs;
        return lhs;
    }
template<typename T>
Matrix<T> operator-(Matrix<T>& lhs,Matrix<T>&& rhs){
        rhs-=lhs;
        return rhs;
    }
template<typename T>
Matrix<T> operator-(Matrix<T>&& lhs,Matrix<T>&& rhs){
        rhs-=lhs;
        return rhs;
    }
template<typename T>
Matrix<T> operator-(const T val,const Matrix<T>& rhs){
        std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        Matrix<T> temp(temp_d.first,temp_d.second);
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                temp(i,j)=val-rhs(i,j);
            }
        }
        return temp;
}
template<typename T>
Matrix<T> operator-(const T val,Matrix<T>&& rhs){
    std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                rhs(i,j)=val-rhs(i,j);
            }
        }
    return rhs;}
template<typename T>
Matrix<T> operator-(const Matrix<T>& rhs,const T val){
    return val-rhs;}
template<typename T>
Matrix<T> operator-(Matrix<T>&& rhs,const T val){
    return val-std::move(rhs);}
template<typename T>
Matrix<T> operator*(const T val,const Matrix<T>& rhs){
        std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        Matrix<T> temp(temp_d.first,temp_d.second);
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                temp(i,j)=val*rhs(i,j);
            }
        }
        return temp;
    }
template<typename T>
Matrix<T> operator*(const T val,Matrix<T>&& rhs){
    std::pair<std::size_t,std::size_t> temp_d=rhs.dim();
        for(int i=0;i<temp_d.first;i++){
            for(int j=0;j<temp_d.second;j++){
                rhs(i,j)=val*rhs(i,j);
            }
        }
        return rhs;
    }
template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs,const Matrix<T>& rhs){
        Matrix<T> temp(lhs.dim().first,rhs.dim().second);
        for(int i=0;i<lhs.dim().first;i++){
            for(int j=0;j<rhs.dim().second;j++){
                for(int k=0;k<lhs.dim().second;k++){
                    temp(i,j)+=lhs(i,k)*rhs(k,j);
                }
            }
        }
        return temp;
    }
template<typename T>
Matrix<T> operator*(Matrix<T>&& lhs,Matrix<T>& rhs){
        Matrix<T> temp(lhs.dim().first,rhs.dim().second);
        temp=lhs*rhs;
//        lhs.~Matrix<T>();
        return temp;
    }
template<typename T>
Matrix<T> operator*(Matrix<T>& lhs,Matrix<T>&& rhs){
        Matrix<T> temp(lhs.dim().first,rhs.dim().second);
        temp=lhs*rhs;
  //      rhs.~Matrix<T>();
        return temp;
    }
template<typename T>
Matrix<T> operator*(Matrix<T>&& lhs,Matrix<T>&& rhs){
        Matrix<T> temp(lhs.dim().first,rhs.dim().second);
        temp=lhs*rhs;
    //    rhs.~Matrix<T>();
    //    lhs.~Matrix<T>();
        return temp;
    }
template<typename T>
std::ostream& operator<<(std::ostream& os,const Matrix<T>& M){
        os<<std::endl;
        for(int i=0;i<M.dim().first;i++){
            for(int j=0;j<M.dim().second-1;j++){
                os<<M(i,j)<<' ';
            }
            os<<M(i,M.dim().second-1)<<std::endl;
        }
        return os;
    }
template<typename T>
Matrix<T> dot_prod(const Matrix<T>& lhs,const Matrix<T>& rhs){
    Matrix<T> res(lhs.dim().first,lhs.dim().second);
    for(int i=0;i<res.dim().first;i++){
        for(int j=0;j<res.dim().second;j++){
            res(i,j)=lhs(i,j)*rhs(i,j);
        }
    }
    return res;
}
template<typename T>
void write_to_file(std::string filename,const Matrix<T>& M){
    std::ofstream fout;
    fout.open(filename,std::ofstream::out | std::ofstream::app);
    fout<<M.dim().first<<" "<<M.dim().second;
    fout<<M;
    fout.close();
}
template<typename T>
std::vector<T> get_vec(std::string S,char sep){
    std::vector<T> vec;
    T val;
    std::string word;
    std::stringstream ss(S);
    while(ss>>word){
        val=atof(word.c_str());
        vec.push_back(val);
    }
    //for(auto i:vec){
    //    std::cout<<i<<" ";
   // }
    //std::cout<<"\n";
    return vec;
}
template<typename T>
Matrix<T> read_from_file(std::string filename){
    std::ifstream fin;
    std::string line;
    std::vector<T> vec;
    std::vector<std::size_t> v;
    Matrix<T> M;
    fin.open(filename);
    getline(fin,line);
    v=get_vec<std::size_t>(line,' ');
    //std::cout<<v[0]<<" "<<v[1];
    M.set_dim(v[0],v[1]);
    std::size_t i;
    i=0;    
    while(fin){
        getline(fin,line);
        if(line=="")break;
        vec=get_vec<T>(line,' ');
        for(std::size_t j=0;j<M.dim().second;j++){
            M(i,j)=vec[j];
        }
        i++;
    }
    fin.close();
    return M;
}
template<typename T>
void init_rand(Matrix<T>& M,std::size_t seed){
    std::size_t row=M.dim().first;
    std::size_t col=M.dim().second;
    srand(time(NULL));
    for(std::size_t i=0;i<row;i++){
        for(std::size_t j=0;j<col;j++){
        M(i,j)=rand()%seed;
        }
    }
}
template<typename T>
void init_eye(Matrix<T>& M,std::size_t seed){
    std::size_t row=M.dim().first;
    std::size_t col=M.dim().second;
    //srand(time(NULL));
    for(std::size_t i=0;i<row;i++){
        M(i,i)=seed;
    }
}
template<typename T>
Matrix<T> transpose(const Matrix<T>& M){
        std::pair<std::size_t,std::size_t> temp=M.dim();
        Matrix<T> temp_m(temp.second,temp.first);
        for(std::size_t i=0;i<temp.first;i++){
            for(std::size_t j=0;j<temp.second;j++){
                temp_m(j,i)=M(i,j);
            }
        }
        return temp_m;
    }
template<typename T>
Matrix<T> striding(Matrix<T>& M,std::size_t row,std::size_t col){
    Matrix<T> res(M.dim().first+2*row,M.dim().second+2*col);
    for(std::size_t i=row;i<row+M.dim().first;i++){
        for(std::size_t j=col;j<col+M.dim().second;j++){
            res(i,j)=M(i-row,j-col);
        }
    }
    return res;
}
template<typename T>
T Filter(Matrix<T>& image,Matrix<T>& filter,std::size_t row,std::size_t col){
    T res=T{};
    for(std::size_t i=0;i<filter.dim().first;i++){
        for(std::size_t j=0;j<filter.dim().second;j++){
            res+=filter(i,j)*image(row+i,col+j);
        }
    }
    return res; 
}
template<typename T>
Matrix<T> Convolve2D(Matrix<T>& image,Matrix<T>& filter){
    std::size_t row=image.dim().first-filter.dim().first+1;
    std::size_t col=image.dim().second-filter.dim().second+1;
    Matrix<T> res(row,col);
    for(std::size_t i=0;i<row;i++){
        for(std::size_t j=0;j<col;j++){
            res(i,j)=Filter(image,filter,i,j);
        }
    }
    return res;
}
template<typename T>
Matrix<T> mirror_image(Matrix<T>& m){
    Matrix<T> res(m.dim().first,m.dim().second);
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    for(std::size_t i=0,x=row-1;i<row && x>=0;i++,x--){
        for(std::size_t j=0,y=col-1;j<col && y>=0;j++,y--){
        res(i,j)=m(x,y);
        }}
        return res;
}
template<typename T>
void Modify(Matrix<T>& m,std::size_t row_1,std::size_t row_2,T val){
    std::size_t col=m.dim().second;
    for(int i=0;i<col;i++){
        m(row_1,i)+=val*m(row_2,i);
    }
    }
template<typename T>
void swap(Matrix<T>& m,std::size_t row1,std::size_t row2){
    std::size_t col=m.dim().second;
    for(int i=0;i<col;i++)std::swap(m(row1,i),m(row2,i));
}
template<typename T>
void rearrange(Matrix<T>& m){
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    for(int i=0;i<row;i++){
        if(m(i,i)==T{}){
            for(int j=i+1;j<row;j++){
                if(m(i,j)!=T{})swap(m,i,j);
            }
        }
    }
}
template<typename T>
void row_mul(Matrix<T>& m,std::size_t row,T val){
    for(int i=0;i<m.dim().second;i++)m(row,i)=val*m(row,i);
}
template<typename T,typename Fun>
T row_op(Matrix<T> M,std::size_t row,Fun f){
    T res{};
    for(int i=0;i<M.dim().second;i++)res+=f(res,M(row,i));
    return res;
}
template<typename T,typename Fun>
T row_transform(Matrix<T> M,std::size_t row,Fun f){
    T res{};
    for(int i=0;i<M.dim().second;i++)M(row,i)=f(M(row,i));
    return res;
}
template<typename T>
Matrix<T> inverse(Matrix<T>& m){
    Matrix<T> temp(m.dim().first,2*m.dim().second);
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    Matrix<T> res(row,col);
    T var;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            temp(i,j)=m(i,j);
        }
        temp(i,col+i)=1;
    }
    rearrange(temp);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(i!=j){
                Modify(temp,j,i,-temp(j,i)/temp(i,i));
            }
        }
        rearrange(temp);
        row_mul(temp,i,1/temp(i,i));
    }
    for(int i=0;i<row;i++){
        for(int j=col;j<2*col;j++){
            res(i,j-col)=temp(i,j);
        }
    }
    return res;
}
template<typename T>
void Upper_diogonlised(Matrix<T>& m){
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    rearrange(m);
    for(int i=0;i<row;i++){
        for(int j=i+1;j<col;j++){
            Modify(m,j,i,-m(j,i)/m(i,i));
          //  rearrange(m);
        }
        rearrange(m);
    }
}
template<typename T>
T det(Matrix<T>& m){
    Matrix<T> temp;
    T res=1;
    std::size_t row=m.dim().first;
    temp=m;
    Upper_diogonlised(temp);
    for(int i=0;i<row;i++){
        res=res*temp(i,i);
    }
    return res;
}
template<typename T>
Matrix<T> liner_equ_solver(Matrix<T>& m){
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    Matrix<T> X(row,1);
    T temp;
    Upper_diogonlised(m);
    for(int i=row-1;i>=0;i--){
        temp=T{};
        for(int j=row-1;j>i;j--){
            temp+=m(i,j)*X(j,0);
        }
        X(i,0)=(m(i,col-1)-temp)/m(i,i);
    }
    return X;
}
template<typename T,typename Fun>
void Transform(Matrix<T>& M,Fun f){
    std::vector<T>& vec=M.get_vector();
    std::transform(vec.begin(),vec.end(),vec.begin(),f);
}
template<typename T,typename Fun>
void Transform(Matrix<T>& M,Matrix<T>& M_res,Fun f){
    std::vector<T>& vec_M=M.get_vector();
    std::vector<T>& vec_M_res=M_res.get_vector();
    std::transform(vec_M.begin(),vec_M.end(),vec_M_res.begin(),f);
}
template<typename T,typename Fun>
void Transform(Matrix<T>& lhs,Matrix<T>& rhs,Matrix<T>& res,Fun f){
std::vector<T>& vec_lhs=lhs.get_vector();
std::vector<T>& vec_rhs=rhs.get_vector();
std::vector<T>& vec_res=res.get_vector();
std::transform(vec_lhs.begin(),vec_lhs.end(),vec_rhs.begin(),vec_res.begin(),f);
}
template<typename T>
Matrix<T> Cholesky_decomposition(Matrix<T>& m){
    std::size_t row=m.dim().first;
    std::size_t col=m.dim().second;
    Matrix<T> chol(row,col); 
    T temp=T{};
    for(int i=0;i<row;i++){
        for(int j=0;j<=i;j++){
            temp=T{};
            if(j==i){
                for(int k=0;k<j;k++)temp+=(chol(j,k)*chol(j,k));
                chol(j,j)=std::sqrt(m(j,j)-temp);
            }
            else{
                for(int k=0;k<j;k++)
                temp+=(chol(i,k)*chol(j,k));
                chol(i,j)=(m(i,j)-temp)/chol(j,j);
            }
        }
    }
    return chol;
}
template<typename T>
std::pair<Matrix<T>,Matrix<T>> Dolittle_LU(Matrix<T>& M){
    std::size_t row=M.dim().first;
    std::size_t col=M.dim().second;
    T temp=T{};
    Matrix<T> L(row,col);
    Matrix<T> U(row,col);
    for(int j=0;j<col;j++){U(0,j)=M(0,j);L(j,j)=1;}
    for(int j=0;j<col;j++){L(j,0)=M(j,0)/U(0,0);}
    for(int i=1;i<row;i++){
        for(int j=i;j<col;j++){
            temp=T{};
            for(int s=0;s<i;s++)temp+=L(i,s)*U(s,j);
            U(i,j)=M(i,j)-temp;
        }
        for(int k=i+1;k<col;k++){
            temp=T{};
            for(int s=0;s<i;s++)temp+=L(k,s)*U(s,i);
            L(k,i)=(M(k,i)-temp)/U(i,i);
        }
    }
    return {L,U};
}
template<typename T>
Matrix<T> mean(Matrix<T>& M,bool flag=false){
    Matrix<T> res;
    if(!flag){
        res.set_dim(1,1);
        res(0,0)=std::accumulate(M.get_vector().begin,M.get_vector().end)/(M.dim().first*M.dim().second);
    }
    else{
        res.set_dim(1,M.dim().first);
        for(int i=0;i<M.dim().first;i++){
            res(0,i)=row_op(M,i,[](T y,T x){return y+x;});
            res(0,i)=res(0,i)/M.dim().second;}
    }
    return res;
}
template<typename T>
Matrix<T> varience(Matrix<T>& M,bool flag=false){
    Matrix<T> mu=mean(M,flag);
    Matrix<T> res;
    if(!flag){
        res(0,0)=std::accumulate(M.get_vector().begin,M.get_vector().end,
        [&](T x,T y){return x+std::pow(y-mu(0,0),2);});
    }
    else{
        res.set_dim(1,M.dim().first);
        for(int i=0;i<M.dim().second;i++){
            res(0,i)=row_op(M,[&](T x,T y){return x+std::pow(y-mu(0,i),2);});
            res(0,i)=res(0,i)/M.dim().second;
        }
    }
    return res;
}
template<typename T>
std::pair<Matrix<T>,Matrix<T>> normalization(Matrix<T>& M,T gemma=1,T beta=0,T epsolon=0,bool flag=false){
    Matrix<T> m,v;
    Matrix<T> out(M.dim().first,M.dim().second);
    std::pair<Matrix<T>,Matrix<T>> res;
    int x=0;
    res.second.set_dim(3,std::max(M.dim().second,4));
    m=mean(M,flag);
    v=varience(M,flag);
    if(!flag){
        res.second(2,3)=std::numeric_limits<T>::max();
        Transform(M,out,[&](T x){return (x-m(0,0))/std::sqrt(v(0,0)+epsolon);});
        res(0,0)=m(0,0);
        res(1,0)=v(0,0);       
    }
    else{
        res.second(2,3)=std::numeric_limits<T>::lowest();
        for(int i=0;i<M.dim().second;i++){
            row_transform(M,i,[&](T x){return (x-m(0,i))/std::sqrt(v(0,i)+epsolon);});
        }
    }
    for(int i=0;i<M.dim().second;i++){
        res.second(0,i)=m(0,i);
        res.second(1,i)=v(0,i);
    }
    res.second(2,0)=gemma;res.second(2,1)=beta;res.second(2,2)=epsolon;
    res.first=gemma*out+beta;
    return res;
}
template<typename T,typename Fun>
Matrix<T> math_fun(Matrix<T>& M,Fun f){
    Matrix<T> res(M.dim().first,M.dim().second);
    Transform(M,res,f);
    return res;
}
template<typename T>
Matrix<T> tanh(Matrix<T>& M){
    return math_fun(M,[](T x){return std::tanh(x);});
}
template<typename T>
Matrix<T> pow(Matrix<T>& M,T n){
    return math_fun(M,[&](T x){return n>0?std::pow(x,n):(1.0/std::pow(x,n));});
}
template<typename T>
Matrix<T> sigmoid(Matrix<T>& M){
    return math_fun(M,[](T x){1.0/(1+std::exp(-x));});
}
