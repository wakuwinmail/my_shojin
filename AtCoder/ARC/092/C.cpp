#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cassert>

int main(){
    int n;
    std::cin>>n;
    std::vector<std::tuple<int,int,int>> dots(n*2);
    for(size_t i = 0; i < n; i++)
    {
        int a,b;
        std::cin>>a>>b;
        dots[i]=std::make_tuple(a,b,1);//red-1
    }
    for(size_t i = 0; i < n; i++)
    {
        int c,d;
        std::cin>>c>>d;
        dots[i+n]=std::make_tuple(c,d,2);//blue-2
    }
    std::sort(dots.begin(),dots.end());
    std::vector<bool> used(n*2,false);
//std::cout<<"OK\n";
    int ans=0;
    for(int i = 0; i < 2*n; i++)
    {

        int &it=std::get<2>(dots[i]);
        if(it==2){
            if(i==0)continue;
            //std::cout<<"OK\n";
            int redmaxy=-1,redmaxyit=i;
            int &by=std::get<1>(dots[i]);
            for(int j = i-1; j >= 0; --j)
            {
                assert(j>=0);
                if(used[j])continue;
                int &y=std::get<1>(dots[j]);
                int &k=std::get<2>(dots[j]);
                if(k==2)continue;
                if(y<by){
                    if(redmaxy<y){
                        redmaxy=y;
                        redmaxyit=j;
                    }
                }
            }
            if(redmaxyit!=i){
                ++ans;
                used[i]=true;
                used[redmaxyit]=true;
            }
        }
    }
    std::cout<<ans<<std::endl;
    return 0;
}