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


void dfs(vlii &adj, vb &reachable, int u){
    int n = adj.size();
    reachable[u] = true;
    for(pii e : adj[u]){
        int v = e.first;
        int w = e.second;
        if(!reachable[v]){
            dfs(adj, reachable, v);
        }
    }
}

int main() {

    int t; SI(t); FOR(testcase, 1, t+1){
        int n; SI(n);
        vlii adj(n);
        vlii incomingAdj(n);
        REP(i,n){
            REP(j,n){
                int w; SI(w);
                if(w){
                    adj[j].push_back(make_pair(i,w));
                    incomingAdj[i].push_back(make_pair(j,w));
                }
            }
        }

        //Compute all nodes that are reachable from Lea
        vb reachable(n, false);
        dfs(adj,reachable,0);

        //Compute maximal incoming edges from a reachable node
        int sum = 0;
        FOR(i,1,n){
            int maxIncomingValue = 0;
            for(pii e : incomingAdj[i]){
                int v = e.first;
                int w = e.second;
                if(reachable[v]){
                    maxIncomingValue = max(maxIncomingValue, w);
                }
            }
            sum += maxIncomingValue;
        }

        printf("Case #%d: %d\n", testcase, sum);
    }
 
    return 0;
}