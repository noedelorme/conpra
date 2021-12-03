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
#define FOR(i, s, k, p) for(int i=s; i<k; i+=p)
#define REP(i, n) FOR(i, 0, n, 1)
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
typedef vector<vector<bool>> vvb;
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
typedef vector<char> vc;
typedef vector<vector<char>> vvc;

void printBoard(vi config){
    int n=config.size();
    cout<<"___________"<<endl;
    REP(i,n){
        REP(j,n){
            if(config[i]==j){ printf("x"); }
            else{ printf("."); }
        }
        printf("\n");
    }
}

bool isValidPosition(vi config, int x, int y){
    int n = config.size();
    REP(i,n){
        int qx = i;
        int qy= config[i];
        if(x==qx && y!=qy){ return false; }
        if(y==qy && x!=qx){ return false; }
        if(abs(x-qx)==abs(y-qy) && abs(x-qx)>0){ return false; }
    }
    if(config[x]==y){ return true; }

    return true;
}

bool isValidBoard(vi config){
    int n = config.size();
    REP(i,n){
        if(!isValidPosition(config, i, config[i])){ return false; }
    }
    return true;
}

bool queensMatchConfig(lii preConfig, vi currentConfig){
    for(pii q : preConfig){
        if(currentConfig[q.first]!=q.second){ return false; }
    }
    return true;
}

pair<bool,vi> nextConfig(vi currentConfig){
    int n = currentConfig.size();

    vi nextConfig = currentConfig;
    //Find largest k s.t. a[k]<a[k+1]
    int k=n-1-1; while(k>=0 && nextConfig[k]>=nextConfig[k+1]){ k--; }
    //If k does not exist then this is the last permutation
    if(k<0){ return make_pair(false,nextConfig); }
    //Find largest l s.t. a[k]<a[l]
    int l=n-1; while(l>=0 && currentConfig[k]>=currentConfig[l]){ l--; }
    //Swap value a[k] and a[l]
    swap(nextConfig[k],nextConfig[l]);
    //Reverse sequence from a[k+1] to a[m]
    reverse(nextConfig.begin()+k+1, nextConfig.end());

    return make_pair(true,nextConfig);
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

        printf("Case #%d:\n", testcase);

        int n; SI(n); scanf("\n");
        lii preConfig;
        REP(i,n){
            REP(j,n){
                char c; SC(c);
                if(c=='x'){
                    preConfig.push_back(make_pair(i,j));
                }
            }
            scanf("\n");
        }

        vi currentConfig(n); REP(i,n){ currentConfig[i]=i; }
        bool flag = true;
        while(flag && !(queensMatchConfig(preConfig, currentConfig) && isValidBoard(currentConfig))){
            printBoard(currentConfig);
            flag = nextConfig(currentConfig).first;
            currentConfig = nextConfig(currentConfig).second;
        }
        if(queensMatchConfig(preConfig, currentConfig) && isValidBoard(currentConfig)){
            printBoard(currentConfig);
        }else{
            printf("impossible\n");
        }
        
    }

    return 0;
}
