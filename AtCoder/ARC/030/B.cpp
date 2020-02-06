#include <iostream>
#include <vector>

using graph=std::vector<std::vector<int>>;
std::vector<int> gem;
graph G;
int ans=0;

bool dfs(int x,int p){
    bool ret = gem[x]==1;
    for(auto i:G[x]){
        if(i==p)continue;
        if(dfs(i,x)){
            ret=true;
            ans+=2;
        }
    }
    return ret;
}

int main(){
    int n,x;
    std::cin>>n>>x;
    --x;
    gem.resize(n);
    G.resize(n);
    for(int i = 0; i < n; ++i){
        std::cin>>gem[i];
    }
    for(int i = 0; i < n-1; ++i){
        int a,b;
        std::cin>>a>>b;
        --a;--b;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    dfs(x,-1);
    std::cout<<ans<<std::endl;
    return 0;
}