//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1147&lang=jp
#include <iostream>

bool solve() {
    int n;
    std::cin>>n;
    if(n==0)return false;
    int ans=0;
    int min=1000,max=0;
    for(int i = 0; i < n; ++i) {
        int a;
        std::cin>>a;
        ans+=a;
        if(a<min)min=a;
        if(a>max)max=a;
    }
    std::cout<<(ans-min-max)/(n-2)<<std::endl;
    return true;
}

int main() {
    while(solve());
    return 0;
}