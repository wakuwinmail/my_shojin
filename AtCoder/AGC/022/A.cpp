#include <iostream>
#include <string>
#include <unordered_map>

char find_upperchar(std::unordered_map<char,int> &um,char x){
    char ret='@';
    for(char c=x+1;c<='z';++c){
        if(um[c]==0){
            ret=c;
            break;
        }
    }
    return ret;
}

int main(){
    std::string s;
    std::cin>>s;
    std::unordered_map<char,int> um;
    std::string ans="";
    for(auto c:s)um[c]++;
    if(s.size()==26){
        for (int i = s.size()-1; i >= 0; --i) {
            char t=find_upperchar(um,s[i]);
            um[s[i]]=0;
            if(isalpha(t)){
                ans=s.substr(0,i);
                ans.push_back(t);
                break;
            }
        }
    }
    else{
        for(char c='a';c<='z';++c){
            if(um[c]==0){
                ans=s;
                ans.push_back(c);
                break;
            }
        }
    }
    if(ans.size()==0)ans="-1";
    std::cout<<ans<<std::endl;
    return 0;
}