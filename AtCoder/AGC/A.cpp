#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n;
    std::cin>>n;
    std::vector<int> l(n*2);
    for (int i = 0; i < n*2; ++i) {
        std::cin>>l[i];
    }
    std::sort(l.begin(),l.end(),std::greater<int>());
    int ans=0;
    for (int i = 1; i < n*2; i+=2) {
        ans+=l[i];
    }
    std::cout<<ans<<std::endl;
    return 0;
}