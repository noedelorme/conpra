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


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int N,M; SII(N,M);
        vi rents(N);
        REP(i,N){ SI(rents[i]); }
        vvi deli(N, vi(M));
        REP(i,N){ REP(j,M){ SI(deli[i][j]); } }

        vb used(N,false);
        vli users(N);
        int totalCost = 0;
        REP(i,M){
            int bestLoc=1;
            int min=INF;
            REP(j,N){
                int cost = deli[j][i];
                if(!used[j]){ cost+= rents[j]; }
                if(cost<min){ min=cost; bestLoc=j+1; }
            }

            users[bestLoc-1].push_back(i+1);
            used[bestLoc-1] = true;
            totalCost += min;
        }

        printf("Case #%d: %d\n", testcase, totalCost);
		REP(i,N){
            if(users[i].size()>0){
                printf("%d ", i+1);
                for(int u : users[i]){ printf("%d ", u); }
                printf("\n");
                
            }
        }

    }

    return 0;
}
