#include <iostream>
#include <cstring>
#include <utility>
#include <stack>

template<typename T>
struct mcomplex{
private:
    T re,im;
    T limit;

    
public:
    mcomplex(){}
    mcomplex(T re,T im,T limit=10000LL):re(re),im(im),limit(limit){}

    std::pair<T,T> value()const{
        return std::pair<T,T>(re,im);
    }

    mcomplex &operator+=(const mcomplex rhs){
        re+=rhs.re;
        im+=rhs.im;
        return *this;
    }

    mcomplex &operator-=(const mcomplex rhs){
        re-=rhs.re;
        im-=rhs.im;
        return *this;
    }

    mcomplex &operator*=(const mcomplex rhs){
        T tre=re*rhs.re-im*rhs.im;
        T tim=re*rhs.im+im*rhs.re;
        re=tre;
        im=tim;
        return *this;
    }
    
    mcomplex operator+(const mcomplex rhs){
        return mcomplex(*this)+=rhs;
    }

    mcomplex operator-(const mcomplex rhs){
        return mcomplex(*this)-=rhs;
    }

    mcomplex operator*(const mcomplex rhs){
        return mcomplex(*this)*=rhs;
    }

    mcomplex operator- (){
        return mcomplex(-re,-im);
    }

    bool overflowcheck(){
        if(re>limit||re<-limit||im>limit||im<-limit){
            return true;
        }
        return false;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& stream,const mcomplex<T>& value){
    std::pair<T,T> val=value.value();
    if(val.first==0){
        if(val.second==0)return stream<<0;
        else return stream<<val.second<<"i";
    }
    else{
        stream<<val.first;
        if(val.second<0)return stream<<val.second<<"i";
        else if(val.second==0)return stream;
        else return stream<<"+"<<val.second<<"i";
    }
}

using ci=mcomplex<long long>;
using strit=std::string::iterator;
std::string s;
bool overflowed=false;
std::stack<ci> stock;

ci parse(strit &t,char stat,ci val);

ci calc(char stat,ci val,ci val2){
    ci ret(0,0);
    //std::cout<<stat<<" "<<val<<" "<<val2<<std::endl;
    switch (stat){
    case '+':
        ret=val+val2;
        break;
    case '-':
        ret=val-val2;
        break;
    case '*':
        ret=val*val2;
        break;
    default:
        std::cout<<"abort"<<std::endl;
        abort();
        break;
    }
    if(ret.overflowcheck())overflowed=true;
    return ret;
}

ci openparentheses(strit &t,char stat,ci val){
    ++t;
    ci ret(0,0);
    if(*t=='('){
        ret=openparentheses(t,stat,val);
    }
    if(ret.overflowcheck())overflowed=true;
    if(val.overflowcheck())overflowed=true;
    //std::cout<<*t<<std::endl;
    while(true){
        if(t==s.end()||*t==')'){
            //std::cout<<"ret,val:"<<ret<<" "<<val<<std::endl;
            ret=calc(stat,ret,val);
            stock.top()+=ret;
            break;
        }
        std::string ts="";
        while(isdigit(*t)){
            ts.push_back(*t);
            ++t;
        }
        if(ts.size()>=6){
            overflowed=true;
            return ret;
        }
        //std::cout<<s<<std::endl;
        if(*t=='i'){
            ++t;
            if(ts!=""){
                ret+=ci(0,std::stoll(ts));
            }
            else{
                ret+=ci(0,1);
            }
        }
        else if(ts!=""){
            ret+=ci(std::stoll(ts),0);
        }
        if(ret.overflowcheck())overflowed=true;
        //std::cout<<"ret:"<<ret<<std::endl;
        if(t==s.end()||*t==')'){
            //std::cout<<"ret,val:"<<ret<<" "<<val<<std::endl;
            ret=calc(stat,ret,val);
            stock.top()+=ret;
            break;
        }
        if(stat=='*'){
            if(*t=='+'||*t=='-'){
                ret*=val;
                ret+=stock.top();
                stock.pop();
                if(ret.overflowcheck())overflowed=true;
                stock.push(ret);
                char op=*t;
                ++t;
                if(op=='-')return parse(t,op,ci(0,0));
                else return parse(t,op,ci(0,0));
            }
            else{
                ret*=val;
                if(ret.overflowcheck())overflowed=true;
                char op=*t;
                ++t;
                return parse(t,op,ret);
            }
        }
        else {
            if(*t=='+'||*t=='-'){
                ret+=val;
                if(ret.overflowcheck())overflowed=true;
                char op=*t;
                ++t;
                if(op=='-')return parse(t,op,ret);
                else return parse(t,op,ret);
            }
            else{
                char op=*t;
                ++t;
                stock.push(val);
                return parse(t,op,ci(0,0));
                if(ret.overflowcheck())overflowed=true;
                //std::cout<<ret<<" "<<val<<std::endl;
            }
        }
    }
    if(ret.overflowcheck())overflowed=true;
    ++t;
    //std::cout<<ret<<std::endl;
    return ret;
}

ci parse(strit &t,char stat,ci val){
    //std::cout<<*t<<" "<<val<<std::endl;
    ci ret(0,0);
    if(*t=='('){
        ret=openparentheses(t,stat,ci(0,0));
        if(stat=='-'){
            ret=-ret;
            stat='+';
        }
    }
    if(ret.overflowcheck())overflowed=true;
    //std::cout<<*t<<std::endl;
    while(true){
        if(t==s.end()||*t==')'){
            //std::cout<<"ret,val:"<<ret<<" "<<val<<std::endl;
            ret=calc(stat,ret,val);
            stock.top()+=ret;
            break;
        }
        std::string ts="";
        bool mi=(stat=='-');
        if(mi)stat='+';
        while(isdigit(*t)){
            ts.push_back(*t);
            ++t;
        }
        if(ts.size()>=6){
            overflowed=true;
            return ret;
        }
        //std::cout<<s<<std::endl;
        if(*t=='i'){
            ++t;
            if(ts!=""){
                if(mi)ret-=ci(0,std::stoll(ts));
                else ret+=ci(0,std::stoll(ts));
            }
            else{
                if(mi)ret-=ci(0,1);
                else ret+=ci(0,1);
            }
        }
        else if(ts!=""){
            if(mi)ret-=ci(std::stoll(ts),0);
            else ret+=ci(std::stoll(ts),0);
        }
        if(ret.overflowcheck())overflowed=true;
        //std::cout<<"ret:"<<ret<<std::endl;
        if(t==s.end()||*t==')'){
            ret=calc(stat,ret,val);
            stock.top()+=ret;
            break;
        }
        if(stat=='*'){
            if(*t=='+'||*t=='-'){
                ret*=val;
                ret+=stock.top();
                stock.pop();
                if(ret.overflowcheck())overflowed=true;
                stock.push(ret);
                char op=*t;
                ++t;
                if(op=='-')return parse(t,op,ci(0,0));
                else return parse(t,op,ci(0,0));
            }
            else{
                ret*=val;
                if(ret.overflowcheck())overflowed=true;
                char op=*t;
                ++t;
                return parse(t,op,ret);
            }
        }
        else {
            if(*t=='+'||*t=='-'){
                ret+=val;
                if(ret.overflowcheck())overflowed=true;
                char op=*t;
                ++t;
                if(op=='-')return parse(t,op,ret);
                else return parse(t,op,ret);
            }
            else{
                char op=*t;
                ++t;
                stock.push(val);
                return parse(t,op,ci(0,0));
                if(ret.overflowcheck())overflowed=true;
                //std::cout<<ret<<" "<<val<<std::endl;
            }
        }
        if(ret.overflowcheck())overflowed=true;
        //std::cout<<ret<<std::endl;
    }
    //std::cout<<"ret,val:"<<ret<<" "<<val<<std::endl;
    if(ret.overflowcheck())overflowed=true;
    return ret;
}

std::string sanitize(std::string s){
    int sit=0;
    std::string ret="";
    while(sit<s.size()){
        while(sit<s.size()&&!isdigit(s[sit])){
            ret.push_back(s[sit]);
            ++sit;
        }
        if(s[sit]=='0'){
            while(sit<s.size()&&s[sit]=='0')++sit;
            if(sit==s.size())--sit;
            else if(!isdigit(s[sit]))--sit;
        }
        while(sit<s.size()&&isdigit(s[sit])){
            ret.push_back(s[sit]);
            ++sit;
        }
    }
    return ret;
}

bool solve(){
    overflowed=false;
    stock=std::stack<ci>();
    std::cin>>s;
    if(std::cin.fail())return false;
    s=sanitize(s);
    //std::cout<<s<<std::endl;
    strit it;
    //if(s.front()=='-')s="0"+s;
    //else s="0+"+s;
    it=s.begin();
    char stat;
    if(*it=='-')stat='-';
    else stat='+';
    parse(it,stat,ci(0,0));
    ci ans=stock.top();
    if(ans.overflowcheck()||overflowed)std::cout<<"overflow"<<std::endl;
    else std::cout<<ans<<std::endl;
    //std::cout<<ans<<std::endl;
    return true;
}

int main(){
    while(solve());
    return 0;
}