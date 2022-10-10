#include<stdio.h>
#include<stdbool.h>
void fun(int s,int e){
    int N=e;
    int j=0;
    bool flag=true;
    int zeros=e-1;
    for(int i=0;i<2*N-1;i++){
        j=0;
        if(flag==false){
            for(int k=0;k<zeros;k++)printf("%d ",0);
        }
        while(j<=s){
            if(flag)
            printf("%d%d ",j+1,N-s+j);
            else printf("%d%d ",N-s+j,j+1);
            j++;
        }
        if(flag){
            for(int k=0;k<zeros;k++)printf("%d ",0);
        }
        printf("\n");
        s=(i<N-1)?s+1:s-1;
        flag=(i<N-1)?true:false;
        zeros=(i<N-1)?zeros-1:zeros+1;
    }
    // for(int i=0;i<N;i++){
    //  j=0;
    //  while(j<=s){
    //      printf("%d%d ",N-s+j,j+1);
    //      j++;
    //  }
    //  printf("\n");
    //  s=s-1;   
    // }
}
int main(){
    fun(0,5);
}