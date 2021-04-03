//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1153&lang=jp
#include <iostream>
#include <vector>

bool solve() {
    int n,m;
    std::cin>>n>>m;
    if(n==0)return false;
    std::vector<int> a(n,0),b(m,0);
    int sn=0,sm=0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin>>x;
        a[i]=x;
        sn+=x;
    }

    for (int i = 0; i < m; i++) {
        int x;
        std::cin>>x;
        b[i]=x;
        sm+=x;
    }
    int an=1000,am=1000;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(sn-a[i]+b[j] == sm+a[i]-b[j]) {
                if(an+am > a[i]+b[j]) {
                    an=a[i];
                    am=b[j];
                }
            }
        }
    }

    if(an!=1000) {
        std::cout<<an<<" "<<am<<std::endl;
    }
    else std::cout<<-1<<std::endl;
    
    return true;
}

int main() {
    while(solve());
    return 0;
}