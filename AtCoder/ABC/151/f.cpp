#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main(){
    int n;
    std::cin>>n;
    std::vector<std::pair<double,double>> d;
    for(int i = 0; i < n; ++i){
        double a,b;
        std::cin>>a>>b;
        d.emplace_back(a,b);
    }
    double ans=0;
    for(int i = 0; i < n; ++i){
        for(int j = 1; j < n; ++j){
            double dist=(d[i].first-d[j].first)*(d[i].first-d[j].first)+
            ans=std::max(ans,)
        }
    }
    return 0;
}