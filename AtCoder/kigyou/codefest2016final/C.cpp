#include <iostream>
#include <vector>

struct UnionFind{
private:
    std::vector<int> par;
    std::vector<int> siz;
public:
    UnionFind(int size){
        par=std::vector<int>(size);
        siz=std::vector<int>(size);
        for(int i=0;i<size;++i){
            par[i]=i;
            siz[i]=1;
        }
    }

    int root(int x){
        if(par[x]==x)return x;
        else {
            par[x]=root(par[x]);
            return par[x];
        }
    }

    bool same(int x,int y){//0-indexed
        return root(x)==root(y);
    }

    void unite(int x,int y){//0-indexed
        x=root(x);
        y=root(y);
        if(x==y)return;

        if(siz[x]<siz[y]){
            par[x]=y;
            siz[y]+=siz[x];
        }
        else{
            par[y]=x;
            siz[x]+=siz[y];
        }
    }

    int component_size(int x){
        return siz[root(x)];
    }
};

int main(){
    int n,m;
    std::cin>>n>>m;
    std::vector<std::vector<int>> l(m);
    for(int i = 0; i < n; ++i){
        int k;
        std::cin>>k;
        for(int j = 0; j < k; ++j){
            int t;
            std::cin>>t;
            --t;
            l[t].push_back(i);
        }
    }
    UnionFind uf(n);
    for(int i = 0; i < m; ++i){
        if(l[i].size()==0)continue;
        int x=l[i][0];
        for(int j = 1; j < l[i].size(); ++j){
            uf.unite(x,l[i][j]);
        }
    }
    if(uf.component_size(0)==n)std::cout<<"YES"<<std::endl;
    else std::cout<<"NO"<<std::endl;
    return 0;
}