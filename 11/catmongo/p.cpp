#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <climits>
#include <cfloat>

using namespace std;

#define SI(x) scanf("%d",&x)
#define SII(x,y) scanf("%d %d",&x,&y)
#define SIII(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define SIIII(x,y,z,w) scanf("%d %d %d %d",&x,&y,&z,&w)
#define SL(x) scanf("%lld",&x)
#define SD(x) scanf("%lf",&x)
#define SC(x) scanf("%c",&x)
#define SS(x) scanf("%s",x)
#define FOR(i, s, k) for(int i=s; i<k; i++)
#define REP(i, n) FOR(i, 0, n)
#define INF INT_MAX
#define EPS 1e-9
#define PI acos(-1)

typedef long long int lint;
typedef unsigned long long int ulint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<lint> vl;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef list<int> li;
typedef list<double> ld;
typedef list<bool> lb;
typedef vector<vector<int>> vvi;
typedef vector<vector<lint>> vvl;
typedef vector<vector<double>> vvd;
typedef vector<pair<int, int>> vii;
typedef list<pair<int, int>> lii;
typedef vector<list<int>> vli;
typedef vector<list<pair<int, int>>> vlii;
typedef vector<list<pair<double,int>>> vldi;

/*************************************************
Segment tree implementation using lazy propagation
*************************************************/
struct Node{
    int v,l,r,lazy;
    bool reset;
};

int build(vi &arr, vector<Node> &tree, int p, int l, int r){
    tree[p].l = l;
    tree[p].r = r;
    if(l==r){
        tree[p].v = arr[l];
        return tree[p].v;
    }
    int m = (l+r)/2;
    tree[p].v = build(arr,tree,2*p+1,l,m)+build(arr,tree,2*p+2,m+1,r);
    return tree[p].v;
}

void propagate(vector<Node> &tree, int p){
    tree[p].v += (tree[p].r-tree[p].l+1)*tree[p].lazy;
    if(tree[p].r!=tree[p].l){
        if(tree[p].reset){
            tree[2*p+1].reset = true;
            tree[2*p+2].reset = true;
            tree[2*p+1].v = 0;
            tree[2*p+2].v = 0;
            tree[2*p+1].lazy = 0;
            tree[2*p+2].lazy = 0;
        }else{
            tree[2*p+1].lazy += tree[p].lazy;
            tree[2*p+2].lazy += tree[p].lazy;
        }
    }
    tree[p].lazy = 0;
    tree[p].reset = false;
}

int rangeSum(vector<Node> &tree, int p, int l, int r){
    if(l>tree[p].r || r<tree[p].l) return 0;

    propagate(tree, p);

    if(l<=tree[p].l && tree[p].r<=r){
        return tree[p].v;
    }
    return rangeSum(tree,2*p+1,l,r) + rangeSum(tree,2*p+2,l,r);
}

void rangeAdd(vector<Node> &tree, int p, int l, int r, int v){
    propagate(tree, p);

    if(l>tree[p].r || r<tree[p].l) return;

    if(l<=tree[p].l && tree[p].r<=r){
        tree[p].lazy = tree[p].lazy + v;
        propagate(tree, p);
    }else if(tree[p].l != tree[p].r){
        rangeAdd(tree,2*p+1,l,r,v);
        rangeAdd(tree,2*p+2,l,r,v);
        tree[p].v = tree[2*p+1].v + tree[2*p+2].v;
    }
}

void rangeReset(vector<Node> &tree, int p, int l, int r){
    propagate(tree, p);

    if(l>tree[p].r || r<tree[p].l) return;

    if(l<=tree[p].l && tree[p].r<=r){
        tree[p].reset = true;
        tree[p].v = 0;
        tree[p].lazy = 0;
        propagate(tree, p);
    }else if(tree[p].l != tree[p].r){
        rangeReset(tree,2*p+1,l,r);
        rangeReset(tree,2*p+2,l,r);
        tree[p].v = tree[2*p+1].v + tree[2*p+2].v;
    }
}


int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
		int n,k; SII(n,k);
        int n2 = pow(2,ceil(log2(n))+1); //n rounded up to a power of 2
        vi arr(n,0);
        vector<Node> tree(n2);

        build(arr,tree,0,0,n-1);

        int total = 0;
        REP(i,k){
            scanf("\n"); char c; SC(c);
            if(c=='s'){
                int a; SI(a); a--;
                rangeAdd(tree,0,a,a,1);
            }else if(c=='d'){
                int a; SI(a); a--;
                if(rangeSum(tree,0,a,a)>0){
                    rangeAdd(tree,0,a,a,-1);
                }
            }else{
                int l,r; SII(l,r); l--; r--;
                total += rangeSum(tree,0,l,r);
                rangeReset(tree,0,l,r);
            }
        }

        printf("Case #%d: %d\n", testcase, total);
    }

    return 0;
}
