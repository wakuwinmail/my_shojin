#include <iostream>
#include <vector>

std::vector<bool> hurui(int n){
    std::vector<bool> isprime(n,true);
    isprime[0]=false;
    isprime[1]=false;
    int p=2;
    while(p*p<n){
        for(size_t i = p+p; i < n; i+=p)
        {
            if(i%p==0)isprime[i]=false;
        }
        for(size_t i = p+1; i < n; i++)
        {
            if(isprime[i]){
                p=i;
                break;
            }
        }
    }
    return isprime;
}

int main(){
    std::vector<bool> isprime=hurui(100001);
    std::vector<int> primes(100001,0);
    for(size_t i = 3; i <= 1e5; i+=2)
    {
        if(isprime[i]&&isprime[(i+1)/2]){
            ++primes[i];
        }
    }
    for(size_t i = 1; i <= 1e5; i++)
    {
        primes[i]+=primes[i-1];
    }

    int q;
    std::cin>>q;
    for(size_t i = 0; i < q; i++)
    {
        int l,r;
        std::cin>>l>>r;
        //std::cout<<primes[r]<<" "<<primes[l]<<"\n";
        std::cout<<primes[r]-primes[l-1]<<"\n";
    }
    return 0;
}