#include <iostream>
#include <deque>
#include <algorithm>

int main(){
    int n;
    std::cin>>n;
    std::deque<int> dq(3*n);
    for(int i=0;i < 3*n; ++i){
        std::cin>>dq[i];
    }
    std::sort(dq.begin(),dq.end());
    long long ans=0;
    while(dq.size()>=3){
        dq.pop_back();
        ans+=dq.back();
        dq.pop_back();
        dq.pop_front();
    }
    std::cout<<ans<<std::endl;
    return 0;
}