//https://atcoder.jp/contests/abc193/tasks/abc193_e
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

using ll = long long;

ll extgcd(ll a, ll b, ll &x, ll &y) {//ax + by = gcd(a,b)を求める
    if(b==0) {
        x=1;
        y=0;
        return a;
    }
    //ax + by = dであるx,y,dが得られる
    ll d = extgcd(b,a%b,y,x);
    y -= a/b * x;
    return d;
}

std::pair<ll,ll> crt(ll a, ll b, ll p, ll q) {//x%p=a,x%q=bであるxを求める
    ll m,n;
    ll d = extgcd(p,q,m,n);
    if((b-a)%d!=0)return std::make_pair(0,-1);
    ll lcm = p*(q/d);
    ll tmp = (b-a)/d*m%(q/d);
    ll x = (a+p*tmp)%lcm;
    return std::make_pair(x,lcm);
}

void solve() {
    ll x,y,p,q;
    std::cin>>x>>y>>p>>q;
    ll ans=-1;
    ll a=x*2+y*2,b=p+q;
    for(int i = p;i < p+q;++i) {
        ll tans,z;
        std::tie(tans,z)=crt(x,i,a,b);
        if(tans==0&&z==-1)continue;
        while(tans<0) {
            tans+=z;
        }
        if(ans==-1)ans=tans;
        ans=std::min(ans,tans);
    }
    for(int i = x;i < x+y;++i) {
        ll tans,z;
        std::vector<ll> tr={p,i},tm={b,a};
        std::tie(tans,z)=crt(p,i,b,a);
        if(tans==0&&z==-1)continue;
        while(tans<0) {
            tans+=z;
        }
        if(ans==-1)ans=tans;
        ans=std::min(ans,tans);
    }
    if(ans==-1)std::cout<<"infinity"<<std::endl;
    else std::cout<<ans<<std::endl;
    return;
}

int main() {
    int T;
    std::cin>>T;
    for(int i = 0;i < T;++i) {
        solve();
    }
    return 0;
}
