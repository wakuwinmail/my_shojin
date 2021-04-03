//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1159&lang=jp
#include <iostream>
#include <vector>

bool solve() {
    int n,p;
    std::cin>>n>>p;
    if(n==0)return false;
    int ip=p;
    std::vector<int> v(n,0);
    int pos=0;
    while(true) {
        if(p!=0) {
            --p;
            v[pos]+=1;
            if(p==0&&v[pos]==ip) {
                std::cout<<pos<<std::endl;
                return true;
            }
        }
        else {
            p=v[pos];
            v[pos]=0;
        }
        
        ++pos;
        pos%=n;
    }
    return true;
}

int main() {
    while(solve());
    return 0;
}