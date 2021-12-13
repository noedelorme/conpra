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

bool onDiagonal(int x){ return x==0 || x==4 || x==7 || x==9; }

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int n,m; SII(n,m);
        vector<string> humans(n);
        vector<string> mouses(m);
        
        REP(i,n){ cin>>humans[i]; }
        REP(i,m){ cin>>mouses[i]; }
        

        vi occurrences = computeOccurrences(humans, mouses);
        vii data(10, make_pair(0,0));
        REP(i,10){ data[i].first=occurrences[i]; data[i].second=i; }
        sort(data.begin(), data.end(), [](const pii a, const pii b){
            if(a.first>b.first){
                return true;
            }else if(a.first==b.first){
                if(a.second==0 || a.second==4 || a.second==7 || a.second==9){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        });

        

        vi scores(10,0);
        int a=0; int b=9;
        while(a<b){
            int aData=data[a].second;
            int bData=data[b].second;

            if(onDiagonal(bData)){
                b--;
            }else{
                if(onDiagonal(aData)){
                    scores[aData]=10; a++;
                    scores[bData]-=5;
                    if(scores[bData]==-10){b--;}
                }else{
                    if(scores[aData]==5){
                        scores[aData]=10; a++;
                        scores[bData]-=5;
                        if(scores[bData]==-10){b--;}
                    }else if(scores[bData]==-5){
                        scores[aData]=5;
                        scores[bData]=-10; b--;
                    }else{
                        scores[aData]=10; a++;
                        scores[bData]=-10; b--;
                    }
                }
            }
        }


        int s=0; REP(i,10){ s+=occurrences[i]*scores[i]; }
        
        printf("Case #%d: %d\n", testcase, s);

    }

    return 0;
}
