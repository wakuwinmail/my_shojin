#include <iostream>
#include <string>
#include <vector>
using ll=long long;

template<typename T>
constexpr T modpow(T a,T n,T mod){//(a^n)%MOD
    T ret=1;
    while(n>0){
        if((n&1)!=0){//n%2==1
            ret=ret*a%mod;
        }
        a=a*a%mod;
        n=n/2;
    }
    return ret;
}

int main() {
    ll n,p;
    std::cin>>n>>p;
    std::string s;
    std::cin>>s;
    ll ans=0;
    if(p==2) {
        for(int i = 0;i < n; ++i) {
            if((int)(s[i]-'0')%2==0)ans+=i+1;
        }
    }
    else if(p==5) {
        for(int i = 0;i < n; ++i) {
            if((int)(s[i]-'0')%5==0)ans+=i+1;
        }
    }
    else {
        std::vector<ll> res(p,0);
        res[0]=1;
        ll t=(s[n-1]-'0')%p;
        ans+=res[t];
        ++res[t];
        for(int i = n-2;i >= 0; --i) {
            t+=(int)(s[i]-'0')*modpow(10LL,n-i-1,p);
            t%=p;
            ans+=res[t];
            ++res[t];
        }
    }
    std::cout<<ans<<std::endl;
    return 0;
}
