//tring
#include <iostream>
#include <vector>

int main(){
    long long a,b;
    std::cin>>a>>b;
    long long d=b-a+1;
    //2**40>10^12
    std::vector<long long> bita(40);
    std::vector<long long> pow2(40,1);
    for (int i = 1; i < 40; ++i) {
        pow2[i]=pow2[i-1]*2;
    }
    for (int i = 0; i < 40; ++i) {
        bita[i]=a%2;
        a-=bita[i];
        a=a/2;
    }
    std::vector<long long> carrycnt(40,0);//次にbitが変わるまでのカウント
    carrycnt[0]=1;
    for (int i = 1; i < 40; ++i) {
        carrycnt[i]=carrycnt[i-1]+(bita[i-1]==1?0:pow2[i-1]);
    }
    long long ans=0;


    if(bita[0]==0){
        int t=d+d%2;
        if((t/2)%2==0)ans+=1;
    }
    else{
        int t=d+d%2;
        if((t/2)%2==1)ans+=1;
    }

    for (int i = 1; i < 40; ++i) {
        long long cnt=0;
        long long cd=d;

        if(cd>=carrycnt[i]){
            cnt+=bita[i]*carrycnt[i];
            cd-=carrycnt[i];
            bita[i]=bita[i]==0?1:0;
        }
        long long tmod=cd%pow2[i];
        cd=(cd-tmod)/pow2[i];

        if(bita[i]==0){
            if(cd%2==0){
                cnt+=(cd/2)*pow2[i];
            }
            else{
                cnt+=(cd+1)/2*pow2[i];
                cnt+=tmod;
            }
        }
        else{
            if(cd%2==0){
                cnt+=(cd/2)*pow2[i];
                cnt+=tmod;
            }
            else{
                cnt+=(cd+1)/2*pow2[i];
            }
        }
        if(cnt%2==1){
            ans+=pow2[i];
            //std::cout<<pow2[i]<<std::endl;
        }
    }
    std::cout<<ans<<std::endl;
    return 0;
}