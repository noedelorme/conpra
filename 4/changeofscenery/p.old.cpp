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


pair<vi,vvi> Dijkstra(vlii adj, int src){
	int n = adj.size();
	priority_queue<pii, vii, greater<pii>> PQ;
	vi dist(n,INF);
	vvi parent(n);
	dist[src-1] = 0;
	PQ.push(make_pair(0,src));
	while(!PQ.empty()){
		int u = PQ.top().second; PQ.pop();
		for(pii p : adj[u-1]){
			int v = p.second; int w = p.first;
			if(dist[u-1]+w==dist[v-1]){
				parent[v-1].push_back(u);
			}
			else if(dist[u-1]+w<dist[v-1]){
				dist[v-1] = dist[u-1]+w;
				parent[v-1].clear();
				parent[v-1].push_back(u);
				PQ.push(make_pair(dist[v-1],v));
			}
		}
	}
	return make_pair(dist,parent);
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int n,m,k; SIII(n,m,k);

		vi path(k);
		REP(i,k){ int v; SI(v); path[i]=v; }

		vlii adj(n);
		REP(i,m){
			int u,v,w; SIII(u,v,w);
			adj[u-1].push_back(make_pair(w,v));
			adj[v-1].push_back(make_pair(w,u));
		}

		pair<vi,vvi> dij = Dijkstra(adj, 1);
		vi dist = dij.first;
		vvi parent = dij.second;

		bool flag = false;
		int current = n;
		while(!parent[current-1].empty()){
			if(parent[current-1].size()>1){
				flag = true; break;
				
			}else{
				current = parent[current-1].front();
			}
		}

		if(flag){
			printf("Case #%d: yes\n", testcase);
		}else{
			printf("Case #%d: no\n", testcase);
		}

    }

    return 0;
}