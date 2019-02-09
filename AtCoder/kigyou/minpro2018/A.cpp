#include <iostream>
#include <string>

int main(){
    std::string s;
    std::cin>>s;
    if(s.substr(0,3)!="yah"){
        std::cout<<"NO"<<std::endl;
        return 0;
    }
    if(s[3]==s[4])std::cout<<"YES"<<std::endl;
    else std::cout<<"NO"<<std::endl;
    return 0;
}