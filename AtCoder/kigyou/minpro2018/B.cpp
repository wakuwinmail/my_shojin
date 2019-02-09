#include <iostream>
#include <string>

long long ipow(long long x,int n){
    long long ret=1;
    while(n>0){
        ret=ret*x;
        --n;
    }
    return ret;
}

int main(){
    long long x,k;
    std::cin>>x>>k;
    long long mod=ipow(10ll,k);
    long long ans=0;
    while(true){
        if(ans>x){
            std::cout<<ans<<std::endl;
            break;
        }
        else ans+=mod;
    }
    return 0;
}