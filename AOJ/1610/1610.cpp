#include <bits/stdc++.h>

using namespace std;

bool solve() {
    int m,n;
    cin>>m>>n;
    if(m==0)return false;
    vector<bool> bloomed(7368792,false);
    int itr=m;
    while(n>0) {
        while(itr<7368792&&bloomed[itr])++itr;
        for(int i = itr; i < 7368792; i+=itr){
            bloomed[i]=true;
        }
        --n;
    }
    while(itr<7368792&&bloomed[itr])++itr;
    cout<<itr<<endl;
    return true;
}

int main() {
    while(solve());
    return 0;
}