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

void printConfig(vi config){
    int n=config.size();
    //printf("___________\n");
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
        if(config[i]!=-1){
            int qx = i;
            int qy= config[i];
            if(x==qx && y!=qy){ return false; }
            if(y==qy && x!=qx){ return false; }
            if(abs(x-qx)==abs(y-qy) && abs(x-qx)>0){ return false; }
        }
    }
    if(config[x]==y){ return true; }

    return true;
}

bool isValidConfig(vi config){
    int n = config.size();
    REP(i,n){
        if(config[i]!=-1 && !isValidPosition(config, i, config[i])){ return false; }
    }
    return true;
}


bool backtrack(vi &config, int queens){
    int n = config.size();
    if(queens==n){
        printConfig(config);
        return true;
    }

    //Search first empty row
    int r = -1;
    REP(i,n){
        if(config[i]==-1){
            r=i; break;
        }
    }

    REP(i,n){
        if(isValidPosition(config, r, i)){
            config[r]=i;
            if(backtrack(config, queens+1)){ return true; }
            config[r]=-1;
        }
    }

    return false;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

        printf("Case #%d:\n", testcase);

        int n; SI(n); scanf("\n");
        vi initConfig(n,-1);
        int initQueens=0;
        bool flag1 = false;
        REP(i,n){
            REP(j,n){
                char c; SC(c);
                if(c=='x'){
                    if(initConfig[i]!=-1){ flag1=true;}
                    initConfig[i]=j;
                    initQueens++;
                }
            }
            scanf("\n");
        }

        if(flag1){ printf("impossible\n"); continue; }
        bool flag2 = isValidConfig(initConfig) && backtrack(initConfig, initQueens);
        if(!flag2){ printf("impossible\n"); }
        
    }

    return 0;
}
