#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main(){
    int n,m;
    std::cin>>n>>m;
    std::vector<std::pair<int,int>> ed;
    for (int i = 0; i < n; ++i) {
        int a,b;
        std::cin>>a>>b;
        ed.emplace_back(a,b);
    }
    std::sort(ed.begin(),ed.end());
    long long int ans=0;
    for(auto p:ed){
        if(m<=0)break;
        else ans+= static_cast<long long>(p.first)* static_cast<long long>(std::min(m,p.second));
        m-=p.second;
    }
    std::cout<<ans<<std::endl;
    return 0;
}