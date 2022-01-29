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
typedef vector<list<pair<int,int>>> vlpii;

/* Prim's Algorithm (Minimum spanning tree) */
int Prim(vlpii adj){
	int n = adj.size();
	vb visited(n, false);
	priority_queue<pii, vii, greater<pii>> Q;
	int cost = 0;
	Q.push(make_pair(0,1));

	while(!Q.empty()){
		pii p = Q.top(); Q.pop();
		int v = p.second;
		int w = p.first;

		if(!visited[v-1]){
			cost+=w;
			visited[v-1]=true;
			for(pii nei : adj[v-1]){
				if(!visited[nei.second-1]){
					Q.push(nei);
				}
			}
		}
	}
	return cost;
}

void dfs(vlpii &adj, vb &visited, int i){
    int n = adj.size();
    visited[i-1] = true;
    for(pii p : adj[i-1]){
        if(!visited[p.second-1]){
            dfs(adj, visited, p.second);
        }
    }
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
        int n,m; SII(n,m);
        vlpii adj(n);
        int sum = 0;
        REP(i,m){
            int a,b,x,l; SIIII(a,b,x,l);
            adj[a-1].push_back(make_pair(-x*l,b));
            adj[b-1].push_back(make_pair(-x*l,a));
            sum += x*l;
        }

        vb visited(n,false);
        dfs(adj, visited, 1);
        bool flag = true;
        REP(i,n) flag &= visited[i];

        if(flag){
            int mtn = -Prim(adj);
            printf("Case #%d: %d\n", testcase, sum-mtn);
        }else{
            printf("Case #%d: impossible\n", testcase);
        }
    }

    return 0;
}