#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

int main(){
    int n;
    std::cin>>n;
    std::vector<int> a(n),b(n);
    std::vector<std::pair<long long,int>> c(n);
    for(size_t i = 0; i < n; i++)
    {
        std::cin>>a[i]>>b[i];
        c[i]=std::make_pair(a[i]+b[i],i);
    }
    using plli=std::pair<long long,int>;
    std::sort(c.begin(),c.end(),[](plli a,plli b){return a.first>b.first;});


    long long ans=0;
    for(size_t i = 0; i < n; i++)
    {
        if(i%2==0){
            ans+=a[c[i].second];
        }
        else{
            ans-=b[c[i].second];
        }
    }
    std::cout<<ans<<std::endl;
    return 0;
}