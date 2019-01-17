#include <iostream>
#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>

template<typename T,typename E>
struct avl_node{
private:
    typedef avl_node<T,E> node;

public:
    T key;
    E value;
    node* left;
    node* right;
    int height;
    int size;
    E minvalue;
    explicit avl_node(T k,E v,int h){
        key=k;
        value=v;
        left=nullptr;
        right=nullptr;
        height=h;
        size=1;
        minvalue=v;
    }
};

template<typename T,typename E>
struct AVLTree{
private:
    typedef avl_node<T,E> node;
    typedef std::function<node*(node*,node*)> F;
    typedef std::function<node*(node*)> G;
    node* root;
    bool change;
    T lmaxkey;
    E lmaxvalue;
    int lmaxsize;
public:
    explicit AVLTree(){
        root=nullptr;
        change=false;
    }

private:
    int height(node* u){
        return u==nullptr?0:u->height;
    }

    int size(node* u){
        return u==nullptr?0:u->size;
    }

    E minvalue(node* u){
        return u==nullptr?std::numeric_limits<E>::max():u->minvalue;
    }

    void updateheight(node *u){
        u->height=std::max(height(u->left),height(u->right))+1;
    }

    node* rotateR(node *u){
        node* v=u->left;
        u->left=v->right;
        v->right=u;

        u->size-=size(v->left)+1;
        v->size+=size(u->right)+1;

        v->minvalue=std::min(v->value,u->minvalue);
        u->minvalue=std::min(u->value,std::min(minvalue(u->left),minvalue(u->right)));

        updateheight(u);
        updateheight(v);
        return v;
    }

    node* rotateL(node* u){
        node* v=u->right;
        u->right=v->left;
        v->left=u;

        u->size-=size(v->right)+1;
        v->size+=size(u->left)+1;

        v->minvalue=std::min(v->value,u->minvalue);
        u->minvalue=std::min(u->value,std::min(minvalue(u->left),minvalue(u->right)));

        updateheight(u);
        updateheight(v);
        return v;
    }

    node* rotateLR(node* u){
        u->left=rotateL(u->left);
        return rotateR(u);
    }

    node* rotateRL(node* u){
        u->right=rotateR(u->right);
        return rotateL(u);
    }

    int bias(node* u){
        int lh=0,rh=0;
        if(u->left!= nullptr)lh=u->left->height;
        if(u->right!= nullptr)rh=u->right->height;
        return lh-rh;
    }

    node* adjustL(node* u){//insert from left, erase from right
        if(!change)return u;
        int h=u->height;
        if(bias(u)==2){
            if(bias(u->left)>= 0)u=rotateR(u);
            else u=rotateLR(u);
        }
        updateheight(u);
        change=h!=u->height;
        return u;
    }

    node* adjustR(node* u){//insert from right, erase from left
        if(!change)return u;
        int h=u->height;
        //std::cout<<"in adjust2"<<std::endl;
        if(bias(u)==-2){
            if(bias(u->right) <= 0)u=rotateL(u);
            else u=rotateRL(u);
        }
        //std::cout<<"upd h not complete"<<std::endl;
        updateheight(u);
        change=h!=u->height;
        //std::cout<<"upd h complete"<<std::endl;
        return u;
    }
public:
    E* find(T k){
        node* u=root;
        while(u!=nullptr){
            if(u->key<k)u=u->right;
            else if(u->key>k)u=u->left;
            else return &u->value;
        }
        //std::cout<<"key:"<<k<<" is nullptr"<<std::endl;
        return nullptr;
    }

    E find_ind(int x){
        auto ret=find_ind(x,root);
        assert(ret!=nullptr);
        return ret->value;
    }

private:
    node* find_ind(int x,node* u){
        if(u==nullptr){
            return nullptr;
        }
        else if(size(u->left)<x){
            return find_ind(x-size(u->left)-1,u->right);
        }
        else if(size(u->left)>x){
            return find_ind(x,u->left);
        }
        else{
            //std::cout<<u->key<<std::endl;
            return u;
        }
    }

public:
    void insert(T k,E v){
        root=insert(root,k,v);
    }

    void insert_ind(int x,T k,E v){
        root=insert_ind(x,root,k,v);
    }

private:
    node* insert(node* u,T k,E v){
        if(u==nullptr){
            change=true;
            //std::cout<<"key:"<<k<<" value:"<<v<<" inserted"<<std::endl;
            return new node(k,v,1);
        }
        else if(u->key<k){
            u->right=insert(u->right,k,v);
            ++u->size;
            u->minvalue=std::min(u->minvalue,v);
            return adjustR(u);
        }
        else if(u->key>k){
            u->left=insert(u->left,k,v);
            ++u->size;
            u->minvalue=std::min(u->minvalue,v);
            return adjustL(u);
        }
        else{
            change=false;
            u->value=v;
            u->minvalue=std::min(u->minvalue,v);
            return u;
        }
    }

    node* insert_ind(int x,node* u,T k,E v){
        if(u==nullptr){
            change=true;
            //std::cout<<"key:"<<k<<" value:"<<v<<" inserted"<<std::endl;
            return new node(k,v,1);
        }
        else if(size(u->left)<x){
            u->right=insert_ind(x-size(u->left)-1,u->right,k,v);
            ++u->size;
            u->minvalue=std::min(u->minvalue,v);
            return adjustR(u);
        }
        else if(size(u->left)>=x){
            u->left=insert_ind(x,u->left,k,v);
            ++u->size;
            u->minvalue=std::min(u->minvalue,v);
            return adjustL(u);
        }
    }

public:
    void erase(T k){
        root=erase(root,k);
    }

    void erase_ind(int x){
        root=erase_ind(x,root);
    }

private:
    node* erase(node* u,T k){
        if(u==nullptr){
            change=false;
            return nullptr;
        }
        else if(u->key<k){
            u->right=erase(u->right,k);
            --u->size;
            u->minvalue=std::min(minvalue(u->left),minvalue(u->right));
            return adjustL(u);
        }
        else if(u->key>k){
            u->left=erase(u->left,k);
            --u->size;
            u->minvalue=std::min(minvalue(u->left),minvalue(u->right));
            return adjustR(u);
        }
        else{
            if(u->left==nullptr){
                //std::cout<<"erase"<<std::endl;
                change=true;
                return u->right;
            }
            else{
                u->left=erasemax(u->left);
                u->key=lmaxkey;
                u->value=lmaxvalue;
                --u->size;
                //std::cout<<"lmaxsize:"<<lmaxsize<<std::endl;
                return adjustR(u);
            }
        }
    }

    node* erase_ind(int x,node* u){
        if(u==nullptr){
            change=false;
            return nullptr;
        }
        else if(size(u->left)<x){
            u->right=erase_ind(x-size(u->left)-1,u->right);
            --u->size;
            u->minvalue=std::min(minvalue(u->left),minvalue(u->right));
            return adjustL(u);
        }
        else if(size(u->left)>x){
            u->left=erase_ind(x,u->left);
            --u->size;
            u->minvalue=std::min(minvalue(u->left),minvalue(u->right));
            return adjustR(u);
        }
        else{
            if(u->left==nullptr){
                //std::cout<<"erase"<<std::endl;
                change=true;
                return u->right;
            }
            else{
                u->left=erasemax(u->left);
                u->key=lmaxkey;
                u->value=lmaxvalue;
                --u->size;
                //std::cout<<"lmaxsize:"<<lmaxsize<<std::endl;
                return adjustR(u);
            }
        }
    }

    node* erasemax(node* u){
        if(u->right!=nullptr){
            u->right=erasemax(u->right);
            --u->size;
            return adjustL(u);
        }
        else{
            change=true;
            lmaxkey=u->key;
            lmaxvalue=u->value;
            lmaxsize=u->size;
            return u->left;
        }
    }

public:
    T nth_min(int x=0){//return x-th minimum key, x is 0 indexed
        return nth_min(root,x)->key;
    }

private:
    node* nth_min(node* u,int x){
        //std::cout<<u->key<<" "<<u->size<<std::endl;
        assert(u!=nullptr);

        node* v=u->left;
        node* w=u->right;

        if(size(v)<x){//go right subtree
            return nth_min(w,x-1-size(v));
        }
        else if(size(v)>x){//go left subtree
            return nth_min(v,x);
        }
        else {
            return u;
        }
    }

public:
    node* range_query(T l,T r,F f){//[l,r) 2項演算(最小値など) 可換であるもの　TODO:遅延評価で書く
        return range_query(root,l,r,f);
    }

    node* range_query(T l,T r,G g){//[l,r) 単項演算
        return range_query(root,l,r,g);
    }

    E range_min_query_ind(int l,int r){//[l,r)
        return range_min_query_ind(root,l,r);
    }
private:
    node* range_query(node* u,T l,T r,F f){
        if(u==nullptr)return nullptr;

        if(u->key<l)return range_query(u->right,l,r,f);
        else if(u->key>=r)return range_query(u->left,l,r,f);
        else{
            node* v=range_query(u->left,l,r,f);
            node* w=range_query(u->right,l,r,f);
            if(v==nullptr){
                if(w==nullptr)return u;
                return f(u,w);
            }
            else if(w==nullptr){
                return f(u,v);
            }
            else return f(f(u,v),w);
        }
    }

    node* range_query(node* u,T l,T r,G g){
        if(u==nullptr)return nullptr;

        if(u->key<l)return range_query(u->right,l,r,g);
        else if(u->key>=r)return range_query(u->left,l,r,g);
        else{
            node* v=range_query(u->left,l,r,g);
            node* w=range_query(u->right,l,r,g);
            return g(u);
        }
    }

    E range_min_query_ind(node* u,T l,T r){
        if(u==nullptr)return std::numeric_limits<E>::max();
        //std::cout<<u->key<<" l and r:"<<l<<" "<<r<<" u->minvalue"<<minvalue(u)<<std::endl;

        if(r<0||size(u)<=l)return std::numeric_limits<E>::max();
        if(l<=0&&size(u)<r)return minvalue(u);

        if(size(u->left)<l)return range_min_query_ind(u->right,l-size(u->left)-1,r-size(u->left)-1);
        else if(size(u->left)>=r)return range_min_query_ind(u->left,l,r);
        else {
            E v=range_min_query_ind(u->left,l,r);
            E w=range_min_query_ind(u->right,l-size(u->left)-1,r-size(u->left)-1);
            E ret=std::min(v,w);
            //std::cout<<"ret:"<<ret<<" u->value:"<<u->value<<std::endl;
            return std::min(ret,u->value);
        }
    }
};

void solve(){
    //http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508
    int n,q;
    std::cin>>n>>q;
    AVLTree<int,int> at;
    for(size_t i = 0; i < n; ++i)
    {
        int a;
        std::cin>>a;
        at.insert_ind(i,a,a);
    }

    for(size_t i = 0; i < q; ++i)
    {
        int x,l,r;
        std::cin>>x>>l>>r;
        if(x==0){
            int v=at.find_ind(r);
            at.erase_ind(r);
            at.insert_ind(l,v,v);
        }
        else if(x==1){
            auto ret=at.range_min_query_ind(l,r+1);
            std::cout<<ret<<std::endl;
        }
        else{
            at.erase_ind(l);
            at.insert_ind(l,r,r);
        }
    }
}

int main(){
    solve();
    return 0;
}