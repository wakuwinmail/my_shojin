#include <iostream>
#include <algorithm>
#include <unordered_set>

int main(){
    int s;
    std::cin>>s;
    std::unordered_set<int> us;
    int ans=1;
    us.emplace(s);
    while(true){
        ++ans;
        s=s%2==0?s/2:s*3+1;
        if(us.find(s)!=us.end())break;
        us.emplace(s);
    }
    std::cout<<ans<<"\n";
}