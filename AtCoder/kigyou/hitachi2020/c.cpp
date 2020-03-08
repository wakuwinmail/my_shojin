#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
using graph = std::vector<std::vector<int>>;
graph G;
using pi = std::pair<int,int>;

void dfs(int x,int p,int dist,int &maxdist,int &maxdistv) {
    for(auto i:G[x]) {
        if(i==p)continue;
        if(dist+1>maxdist) {
            maxdist=dist+1;
            maxdistv=i;
        }
        dfs(i,x,dist+1,maxdist,maxdistv);
    }
}

int treediam() {
    int maxdist=0;
    int maxdistv=0;
    dfs(0,-1,0,maxdist,maxdistv);
    maxdist=0;
    dfs(maxdistv,-1,0,maxdist,maxdistv);
    return maxdist;
}

int main() {
    int n;
    std::cin>>n;
    G.resize(n);
    for(int i = 0;i < n-1;++i) {
        int a,b;
        std::cin>>a>>b;
        --a;--b;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    if(treediam()<3) {
        for(int i = 0;i < n;++i) {
            std::cout<<i+1;
            if(i==n-1)std::cout<<std::endl;
            else std::cout<<" ";
        }
        return 0;
    }
    std::vector<std::vector<int>> v(n);
    v[0].emplace_back(0);
    std::queue<pi> q;
    std::vector<bool> visited(n,false);
    q.push(pi(0,0));
    visited[0] = true;
    int os = 0,es = 1;
    while(!q.empty()) {
        auto t = q.front();
        q.pop();
        int x = t.first;
        int cnt = t.second;
        for(auto i:G[x]) {
            if(visited[i])continue;
            visited[i]=true;
            v[cnt+1].emplace_back(i);
            if(cnt%2==0)++os;
            else ++es;
            q.push(pi(i,cnt+1));
        }
    }
    int u=n/3,d=n/3,t=n/3;
    if(n%3==1)++u;
    if(n%3==2) {
        ++d;
        ++u;
    }
    std::vector<int> ans(n,-1);
    if(os>=u+d) {
        for(int i = 0;i < n;++i) {
            for(auto x:v[i]) {
                if(i%2==0) {
                    ans[x]=3*t;
                    --t;
                }
                else {
                    if(u>0) {
                        ans[x]=3*u-2;
                        --u;
                    }
                    else if(d>0) {
                        ans[x]=3*d-1;
                        --d;
                    }
                    else {
                        ans[x]=3*t;
                        --t;
                    }
                }
            }
        }
    }
    else if(es>=u+d) {
        for(int i = 0;i < n;++i) {
            for(auto x:v[i]) {
                if(i%2==1) {
                    ans[x]=3*t;
                    --t;
                }
                else {
                    if(u>0) {
                        ans[x]=3*u-2;
                        --u;
                    }
                    else if(d>0) {
                        ans[x]=3*d-1;
                        --d;
                    }
                    else {
                        ans[x]=3*t;
                        --t;
                    }
                }
            }
        }
    }
    else {
        for(int i = 0;i < n;++i) {
            for(auto x:v[i]) {
                if(i%2==1) {
                    if(u>0) {
                        ans[x]=3*u-2;
                        --u;
                    }
                    else {
                        ans[x]=3*t;
                        --t;
                    }
                }
                else {
                    if(d>0) {
                        ans[x]=3*d-1;
                        --d;
                    }
                    else {
                        ans[x]=3*t;
                        --t;
                    }
                }
            }
        }
    }
    for(int i = 0;i < n;++i) {
        std::cout<<ans[i];
        if(i==n-1)std::cout<<std::endl;
        else std::cout<<" ";
    }
    return 0;
}
