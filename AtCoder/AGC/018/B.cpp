#include <iostream>
#include <vector>
#include <utility>

bool canmake(int mid,int m,int n,std::vector<std::vector<int>> &a){
    std::vector<int> usecnt(n,0);
    std::vector<bool> canuse(m, true);
    for (int i = 0; i < m; ++i) {
        std::vector<int> pcnt(m,0);
        std::pair<int,int> maxk=std::make_pair(0,-1);
        for (int j = 0; j < n; ++j) {
            if(canuse[a[j][usecnt[j]]])++pcnt[a[j][usecnt[j]]];
            if(pcnt[a[j][usecnt[j]]]>maxk.first){
                maxk=std::make_pair(pcnt[a[j][usecnt[j]]],a[j][usecnt[j]]);
            }
        }
        if(maxk.first<=mid)return true;
        else{
            canuse[maxk.second]=false;
            for (int j = 0; j < n; ++j) {
                for (int l = usecnt[j]; l < m; ++l) {
                    if(!canuse[a[j][usecnt[j]]])++usecnt[j];
                    else break;
                }
            }
        }
    }
    return false;
}

int main(){
    int n,m;
    std::cin>>n>>m;
    std::vector<std::vector<int>> a(n,std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin>>a[i][j];
            --a[i][j];
        }
    }
    int pok=n,png=0;
    int pmid=(pok+png)/2;
    while(pok-png!=1){
        pmid=(pok+png)/2;
        if(canmake(pmid,m,n,a))pok=pmid;
        else png=pmid;
    }
    std::cout<<pok<<std::endl;
    return 0;
}