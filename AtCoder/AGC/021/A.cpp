#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

long long ipow(long long x,long long n){
    long long ret=1;
    for(int i = 0; i < n; i++){
        ret=ret*x;
    }
    return ret;
}

int main(){
    long long int n;
    std::cin>>n;
    std::vector<std::vector<std::pair<int,long long>>> dp(17,std::vector<std::pair<int,long long>>(10,std::make_pair(0,0)));
    for(int i = 0; i <= 9; i++){
        long long nextnum=ipow(10,16)*i;
        if(nextnum<=n)dp[16][i]=std::make_pair(i,nextnum);
        else dp[16][i]=std::make_pair(0,0);
    }

    for(int i = 15; i >= 0; --i){
        for(int t = 0; t <= 9; t++){
            for(int p = 0; p <= 9; p++){
                long long nextnum=dp[i+1][p].second+ipow(10,i)*t;
                if(nextnum>n){
                    if(dp[i][t].first<dp[i+1][p].first)dp[i][t]=dp[i+1][p];
                    else if(dp[i][t].second<dp[i+1][p].second)dp[i][t]=dp[i+1][p];
                }
                else if (dp[i][t].first<=dp[i+1][p].first){
                    dp[i][t]=std::make_pair(dp[i+1][p].first+t,nextnum);
                    //std::cout<<"i "<<i<<"p "<<p<<"t "<<t<<"dp[i][t].first "<<dp[i][t].first<<"\n";
                }
            }
            //std::cout<<dp[i][t].second<<"\n";
        }
    }
    int ans=0;
    for(auto i : dp[0])
    {
        ans=std::max(ans,i.first);
    }
    std::cout<<ans<<std::endl;
    return 0;
}