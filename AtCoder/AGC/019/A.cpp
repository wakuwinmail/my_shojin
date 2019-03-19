#include <iostream>
#include <algorithm>

int main(){
    long long q,h,s,d;
    std::cin>>q>>h>>s>>d;
    long long b1,b2;
    b1=std::min({q*4,h*2,s});
    b2=std::min(b1*2,d);
    long long n;
    std::cin>>n;
    std::cout<<b2*(n/2)+b1*(n%2)<<std::endl;
    return 0;
}