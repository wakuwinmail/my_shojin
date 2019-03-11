#include <iostream>

int main(){
    int h,w,a,b;
    std::cin>>h>>w>>a>>b;
    std::cout<<h*w-(a*w+b*h-a*b)<<std::endl;
    return 0;
}