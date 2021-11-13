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
typedef pair<double,int> pdi;
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


pair<bool,vd> BellmanFordCycle(vldi adj, int src){
	int n = adj.size();
	deque<int> Q, Qp;
	vd dist(n,DBL_MAX);
	vi parent(n, -1);
	dist[src-1] = 0;
	Q.push_back(src);
	REP(i,n){
		
		while(!Q.empty()){
			int v;
			v = Q.front(); Q.pop_front();
			
			for(pdi p : adj[v-1]){
				int w = p.second; double c = p.first;
				if(dist[v-1]+c<dist[w-1]){
					dist[w-1] = dist[v-1]+c;
					parent[w-1] = v;
					if(find(Qp.begin(),Qp.end(),w)==Qp.end()){
						Qp.push_back(w);
					}
				}
			}
		}
		swap(Q,Qp);
	}
	return make_pair(!Q.empty(),dist);
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int n,m; SII(n,m);
		vldi adj(n);
		REP(i,m){
			int u,v; double w; SII(u,v); SD(w);
			adj[u-1].push_back(make_pair(log(w),v));
		}

		pair<bool,vd> bellman = BellmanFordCycle(adj, 1);
		vd dist = bellman.second;


		if(bellman.first){
			printf("Case #%d: Jackpot\n", testcase);
		}else if(dist[n-1]==DBL_MAX){
			printf("Case #%d: impossible\n", testcase);
		}else{
			printf("Case #%d: %.6lf\n", testcase, exp(dist[n-1]));
		}

    }

    return 0;
}