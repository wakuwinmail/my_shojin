#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <utility>
#include <iterator>

template <typename T>
struct SegmentTree{
private:
    int n;
    T init;
    std::vector<T> node;

public:
    explicit SegmentTree(int sz,T initv = 0) {
        n=1;
        init=initv;
        while(n<sz)n=n*2;
        node.resize(static_cast<unsigned int>(2 * n - 1), init);
        for (int i = 0; i <sz ; ++i) node[i+n-1]=init;
        for (int i = n-2; i >= 0 ; --i) node[i]=std::max(node[2*i+1],node[2*i+2]);
    }

    void update(int x, T val){//x:0-indexed
        x+=n-1;
        node[x]=val;
        while(x>0){
            x=(x-1)/2;
            node[x]=std::max(node[2*x+1],node[2*x+2]);
        }
    }

    T getmax(int p,int q,int k=0,int l=0,int r=-1){//[p,q):0-indexed
        if(r<0)r=n;
        if(r<=p||l>=q)return init;//out of range
        if(p<=l&&r<=q)return node[k];

        return std::max(getmax(p,q,2*k+1,l,(l+r)/2),getmax(p,q,2*k+2,(l+r)/2,r));
    }
};

using ll = long long;
using pi = std::pair<ll,ll>;
const ll mod = 998244353;
int main() {
    int n;
    std::cin>>n;
    if(n==1){
        std::cout<<2<<std::endl;
        return 0;
    }
    SegmentTree<ll> st(n);
    std::vector<pi> robo(n);
    for(int i = 0;i < n;++i) {
        int x,d;
        std::cin>>x>>d;
        robo[i]=pi(x,d);
    }
    std::sort(robo.begin(),robo.end());
    std::vector<ll> lim(n);
    for(int i = n-1;i >= 0;--i) {
        auto it=std::lower_bound(robo.begin(),robo.end(),pi(robo[i].first+robo[i].second,0));
        st.update(i,i);
        if(it==robo.begin()+i){
            continue;
        }
        else --it;
        int d=it-robo.begin();
        st.update(i,st.getmax(i,d+1));
    }
    std::vector<ll> dp(n,0);
    dp[n-1]=2;
    for(int i = n-2;i >= 0;--i) {
        dp[i]+=dp[i+1];
        dp[i]%=mod;
        auto t=st.getmax(i,i+1);
        if(t<n-1)dp[i]+=dp[t+1];
        else ++dp[i];
        dp[i]%=mod;
    }
    std::cout<<dp[0]<<std::endl;
    return 0;
}
