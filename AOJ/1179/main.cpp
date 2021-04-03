//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1179&lang=jp
#include <iostream>
#include <set>
#include <utility>

constexpr int nyd = (20 + 19)*5;
constexpr int tyd = nyd*2 + 20 * 10;

int cal(int y, int m, int d) {
    int ret=0;
    y-=1;
    ret += tyd*(y/3);
    y%=3;
    ret += nyd*y;
    if(y==2) {
        ret += 20*(m-1)+d;
    }
    else {
        for(int i = 1; i < m; ++i) {
            ret += (i%2==0)?19:20;
        }
        ret += d;
    }

    return ret;
}

bool solve() {
    int n;
    std::cin>>n;
    if(n==0)return false;
    for(int i = 0; i < n; ++i) {
        int y,m,d;
        std::cin>>y>>m>>d;
        int x = cal(1000,1,1);
    	std::cout<<x-cal(y,m,d)<<std::endl;
	}

    
    return true;
}

int main() {
    solve();
    return 0;
}