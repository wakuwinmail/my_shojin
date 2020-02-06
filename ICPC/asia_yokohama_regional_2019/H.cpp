#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <utility>

using pi=std::pair<int,int>;
using ppi=std::pair<pi,int>;

int main(){
    std::string s;
    std::cin>>s;
    int n=s.size();
    std::vector<int> dim(n+2,0);
    int nowdim=0;
    std::stack<ppi> hist;
    int lef=0;
    int ans=0;
    for(int i = 0; i < n; ++i){
        if(s[i]=='('){
            if(nowdim<0){
                hist.push(ppi(pi(dim[1],-2),ans));
                dim[1]=0;
                ++lef;
                nowdim=1;
            }
            else{
                hist.push(ppi(pi(nowdim+1,2),dim[nowdim+1]));
                dim[nowdim+1]=0;
                ++lef;
                ++nowdim;
                hist.push(ppi(pi(nowdim,0),ans));
            }
            
        }
        else if(s[i]==')'){
            if(lef>0){
                --lef;
                ++dim[nowdim];
                ans+=dim[nowdim];
                hist.push(ppi(pi(nowdim,1),ans));
                --nowdim;
            }
            else{
                hist.push(ppi(pi(nowdim,-1),ans));
                nowdim=-1;
                dim[0]=0;
            }
        }
        else{//'-'
            ppi t=hist.top();
            hist.pop();
            if(t.first.second==0){
                ans=t.second;
                --lef;
                --nowdim;
                t=hist.top();
                hist.pop();
                dim[t.first.first]=t.second;
            }
            else if(t.first.second==1){
                ans=t.second;
                ++lef;
                --dim[t.first.first];
            }
            else if(t.first.second==-1){
                nowdim=t.first.first;
                ans=t.second;
            }
            else if(t.first.second==-2){
                dim[1]=t.first.first;
                ans=t.second;
            }
        }
        std::cout<<ans<<std::endl;
    }
    return 0;
}