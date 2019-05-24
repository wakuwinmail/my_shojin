#include <string>
#include <iostream>
#include <cctype>
#include <cassert>

using strit=std::string::iterator;

void opcal(char op,int &a,int &b){
    switch (op){
        case '+':
            a+=b;
            break;
        case '-':
            a-=b;
            break;
        case '*':
            a*=b;
            break;
        case '/':
            a=a/b;
            break;
        default:
            a=b;
    }
}

int cal(strit it,std::string &s){
    int ret=0;
    int t=0;
    int ti=0;
    char co='+';
    ++it;
    while(it!=s.end()){
        if(*it=='('){
            int pn=cal(it,s);
            assert(*it==')');
            opcal(co,t,pn);
        }
        else if(*it==')'){
            opcal(co,ret,t);
            return ret;
        }
        else if(isdigit(*it)){
            while(isdigit(*it)){
                ti=ti*10;
                ++it;
            }
            --it;
            ti+=(*it)-'0';
        }
        else{
            opcal(co,t,ti);
            ti=0;
            if(*it=='+'||*it=='-'){
                opcal(co,ret,t);
                t=0;
            }
            co=*it;
        }
        ++it;
    }
    return ret;
}

void solve(std::string s){
    std::cout<<cal(s.begin(),s)<<std::endl;
}
int main(){
    int n;
    std::cin>>n;
    std::string s;
    for (int i = 0; i < n; ++i) {
        std::cin>>s;
        solve(s);
    }
    return 0;
}