#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    vector<pair<char,char>> sp;
    for (int i = 0; i < q; i++)
    {
        char a,b;
        cin>>a>>b;
        sp.emplace_back(a,b);
    }
    
    int ng=-1,ok=n;
    int mid;
    int la,ra;
    while(ok-1>ng) {
        mid=(ok+ng)/2;
        int t=mid;
        bool surv=true;
        for (int i = 0; i < q; i++)
        {
            if(sp[i].first==s[t]) {
                if(sp[i].second=='L')--t;
                else ++t;
            }
            if(t<0) {
                surv=false;
                break;
            }
        }
        if(surv)ok=mid;
        else ng=mid;
    }
    la=ok;
//cerr<<la<<endl;
    ng=n,ok=-1;
    while(ng-1>ok) {
        mid=(ok+ng)/2;
        int t=mid;
        bool surv=true;
        for (int i = 0; i < q; i++)
        {
            if(sp[i].first==s[t]) {
                if(sp[i].second=='L')--t;
                else ++t;
            }
            if(t>=n) {
                surv=false;
                break;
            }
        }
        if(surv)ok=mid;
        else ng=mid;
    }
    ra=ok;
//cerr<<ra<<endl;
    int ans;
    if(ra<la)ans=0;
    else ans=ra-la+1;
    cout<<ans<<endl;
    return 0;
}