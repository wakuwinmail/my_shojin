#include <iostream>
#include <vector>

int main(){
    int n;
    std::cin>>n;
    std::vector<int> tlim(n);
    for (int i = 0; i < n; i++){
        std::cin>>tlim[i];
    }
    std::vector<int> f(n,0),b(n,0);
    
    return 0;
}