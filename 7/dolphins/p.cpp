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

/*
  A C T G
A 0 1 2 3
C # 4 5 6
T # # 7 8
G # # # 9
*/
int coupleToInt(pair<char,char> couple){
    if(couple.first=='A' && couple.second=='A'){ return 0; }
    if(couple.first=='A' && couple.second=='C'){ return 1; }
    if(couple.first=='C' && couple.second=='A'){ return 1; }
    if(couple.first=='A' && couple.second=='T'){ return 2; }
    if(couple.first=='T' && couple.second=='A'){ return 2; }
    if(couple.first=='A' && couple.second=='G'){ return 3; }
    if(couple.first=='G' && couple.second=='A'){ return 3; }
    if(couple.first=='C' && couple.second=='C'){ return 4; }
    if(couple.first=='C' && couple.second=='T'){ return 5; }
    if(couple.first=='T' && couple.second=='C'){ return 5; }
    if(couple.first=='C' && couple.second=='G'){ return 6; }
    if(couple.first=='G' && couple.second=='C'){ return 6; }
    if(couple.first=='T' && couple.second=='T'){ return 7; }
    if(couple.first=='T' && couple.second=='G'){ return 8; }
    if(couple.first=='G' && couple.second=='T'){ return 8; }
    if(couple.first=='G' && couple.second=='G'){ return 9; }
    return -1;
}

vi computeOccurrences(vector<string> humans, vector<string> mouses){
    int n=humans.size();
    int m=mouses.size();
    vi occurrences(10,0);
    REP(i,n){
        REP(j,m){
            REP(k,humans[i].size()){
                occurrences[coupleToInt(make_pair(humans[i][k],mouses[j][k]))]++;
            }
        }
    }
    return occurrences;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int n,m; SII(n,m);
        vector<string> humans(n);
        vector<string> mouses(m);
        
        REP(i,n){ cin>>humans[i]; }
        REP(i,m){ cin>>mouses[i]; }
        
        vi occurrences = computeOccurrences(humans, mouses);
        
        vi vall = {-10, -5, 0, 5, 10};
        vi vdia = {0, 5, 10};
        vi perm(10);
        int ma = 0;
        int s = 0;
        for(int v0 : vdia){
            for(int v1 : vall){
                for(int v2 : vall){
                    for(int v3 : vall){
                        for(int v4 : vdia){
                            for(int v5 : vall){
                                for(int v6 : vall){
                                    for(int v7 : vdia){
                                        for(int v8 : vall){
                                            for(int v9 : vdia){
                                                if(v0+v1*2+v2*2+v3*2+v4+v5*2+v6*2+v7+v8*2+v9==0){
                                                    perm = {v0,v1,v2,v3,v4,v5,v6,v7,v8,v9};
                                                    s=0; REP(i,10){ s+=occurrences[i]*perm[i]; }
                                                    ma = max(ma,s);
                                                }
                                            }  
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        printf("Case #%d: %d\n", testcase, ma);

    }

    return 0;
}
