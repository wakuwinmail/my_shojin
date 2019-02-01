#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

int main(){
    std::string s;
    std::cin>>s;
    char t='0';
    for(size_t i = 0; i < s.size(); i++){
        if(s[i]==t){
            std::cout<<i<<" "<<i+1<<std::endl;
            return 0;
        }
        t=s[i];
    }
    for(size_t i = 0; i+2 < s.size(); i++){
        if(s[i]==s[i+2]){
            std::cout<<i+1<<" "<<i+3<<std::endl;
            return 0;
        }    
    }
    std::cout<<"-1 -1"<<std::endl;
    return 0;
}