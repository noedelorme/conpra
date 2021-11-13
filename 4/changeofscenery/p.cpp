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

typedef vector<list<pair<int,pair<int,bool>>>> vliib;
typedef pair<int,pair<int,bool>> iib;

typedef struct Edge{
	int a, b, w;
	bool u;
	Edge(int _a, int _b, int _w, bool _u): a(_a), b(_b), w(_w), u(_u) {};
} Edge;

typedef vector<list<Edge>> vledge;

vvi Dijkstra(vledge adj, int src){
	int n = adj.size();

	auto compare = [](const Edge& a, const Edge& b){ return a.w>b.w; };
	priority_queue<Edge, vector<Edge>, decltype(compare)> PQ(compare);

	vi dist(n,INF);
	vvi parent(n);
	vb visited(n,false);

	dist[src-1] = 0;
	visited[src-1] = true;

	for(Edge &p : adj[src-1]){ PQ.push(p); }

	while(!PQ.empty()){
		Edge e = PQ.top(); PQ.pop();
		int u = e.a; int v = e.b; int w = e.w;

		if(!visited[v-1]){
			visited[v-1] = true;
			dist[v-1] = w;
			parent[v-1].clear();
			parent[v-1].push_back(u);
			for(Edge &q : adj[v-1]){
				if(!q.u){ PQ.push(Edge(q.a,q.b,dist[v-1]+q.w,false)); }
			}
		}else if(w==dist[v-1]){
			parent[v-1].push_back(u);
			for(Edge &q : adj[v-1]){
				if(!q.u){
					q.u=true;
					PQ.push(Edge(q.a,q.b,dist[v-1]+q.w,true));
				}
			}
		}
	}
	return parent;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int n,m,k; SIII(n,m,k);

		vi path(k);
		REP(i,k){ int v; SI(v); path[i]=v; }

		vledge adj(n);
		REP(i,m){
			int u,v,w; SIII(u,v,w);
			adj[u-1].push_back(Edge(u,v,w,false));
			adj[v-1].push_back(Edge(v,u,w,false));
		}

		vvi parent = Dijkstra(adj, 1);

		bool flag = false;
		for(int i : path){if(parent[i-1].size()>1){ flag=true; }}

		if(flag){
			printf("Case #%d: yes\n", testcase);
		}else{
			printf("Case #%d: no\n", testcase);
		}

    }

    return 0;
}