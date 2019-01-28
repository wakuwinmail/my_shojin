#include <iostream>
#include <algorithm>

int main(){
    int a,b,c;
    std::cin>>a>>b>>c;
    std::cout<<a*b*c/(std::max(std::max(a,b),c)*2)<<std::endl;
    return 0;
}