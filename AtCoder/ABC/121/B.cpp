#include <iostream>
#include <vector>

int main(){
    int n,m,c;
    std::cin>>n>>m>>c;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin>>b[i];
    }
    int ans=0;
    for (int i = 0; i < n; ++i) {
        int score=0;
        for (int j = 0; j < m; ++j) {
            int t;
            std::cin>>t;
            score+=t*b[j];
        }
        if(score+c>0)++ans;
    }
    std::cout<<ans<<std::endl;
    return 0;
}