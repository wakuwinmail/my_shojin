#include <iostream>
#include <algorithm>

int main(){
    long long a,b,c;
    std::cin>>a>>b>>c;
    if(a%2==0||b%2==0||c%2==0)std::cout<<0<<std::endl;
    else{
        long long ans=1;
        if(a<=b||a<=c)ans=ans*a;
        if(b<a||b<=c)ans=ans*b;
        if(c<a||c<b)ans=ans*c;
        std::cout<<ans<<std::endl;
    }
    return 0;
}