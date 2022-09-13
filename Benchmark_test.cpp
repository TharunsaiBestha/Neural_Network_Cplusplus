#include<benchmark/benchmark.h>
#include "Matrix.h"
static void det(benchmark::State& state){
    int x;
    int N=100;
    Matrix<float> W(N,N);
    float res=0;
    srand(time(NULL));
    for(std::size_t i=0;i<N;i++){
        for(std::size_t j=0;j<N;j++){
            W(i,j)=std::rand()%10;
           // W(i,j)=a++;
        }
    }
    while(state.KeepRunning()){
	    res=det(W);}
}
BENCHMARK(det);
BENCHMARK_MAIN();
