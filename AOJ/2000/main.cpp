//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2000&lang=jp
#include <iostream>
#include <set>
#include <utility>

bool solve() {
    int n;
    std::cin>>n;
    if(n==0)return false;
    std::set<std::pair<int,int>> g;
    for(int i = 0; i < n; ++i) {
        int a,b;
        std::cin>>a>>b;
        g.emplace(a,b);
    }
    int m;
    std::cin>>m;
    int y=10,x=10;
    int ans=0;
    for(int i = 0; i < m; ++i) {
        char c;
        int d;
        std::cin>>c>>d;
        for(int j = 0; j < d; ++j) {
            switch (c)
            {
            case 'N':
                y+=1;
                break;
            case 'S':
                y-=1;
                break;
            case 'E':
                x+=1;
                break;
            case 'W':
                x-=1;
                break;
            default:
                break;
            }
            if(g.find(std::make_pair(x,y))!=g.end())g.erase(std::make_pair(x,y));
        }
    }

    if(g.empty())std::cout<<"Yes"<<std::endl;
    else std::cout<<"No"<<std::endl;
    
    return true;
}

int main() {
    while(solve());
    return 0;
}