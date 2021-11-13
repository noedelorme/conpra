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

using namespace std;

#define SI(x) scanf("%d",&x)
#define SII(x,y) scanf("%d %d",&x,&y)
#define SIII(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define SIIII(x,y,z,w) scanf("%d %d %d %d",&x,&y,&z,&w)
#define SLLI(x) scanf("%lld",&x)
#define SF(x) scanf("%f",&x)
#define SD(x) scanf("%lf",&x)
#define SC(x) scanf("%c",&x)
#define SS(x) scanf("%s",x)
#define P(x) cout<<"> x:"<<x<<endl
#define FOR(i, s, k, p) for(int i=s; i<k; i+=p)
#define REP(i, n) FOR(i, 0, n, 1)
#define FOREACH(it, l) for(auto it = l.begin(); it != l.end(); it++)
#define INF INT_MAX
#define EPS 1e-9
#define PI acos(-1)

typedef long long int lint;
typedef unsigned long long int ulint;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<vi> vvi;
typedef pair<lint, lint> pll;
typedef vector<lint> vl;
typedef vector<pll> vll;
typedef vector<vl> vvl;
typedef list<int> li;
typedef list<pii> lii;
typedef vector<li> vli;
typedef vector<lii> vlii;


vi Dijkstra(vlii adj, int src){
	int n = adj.size();
	priority_queue<pii, vii, greater<pii>> PQ;
	vi dist(n,INF);
	vi parent(n, -1);
	dist[src-1] = 0;
	PQ.push(make_pair(0,src));
	while(!PQ.empty()){
		int u = PQ.top().second; PQ.pop();
		for(pii p : adj[u-1]){
			int v = p.second; int w = p.first;
			if(dist[u-1]+w<dist[v-1]){
				dist[v-1] = dist[u-1]+w;
				parent[v-1] = u;
				PQ.push(make_pair(dist[v-1],v));
			}
		}
	}
	return dist;
}

int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){
		int n,m; SII(n,m);
		vlii adj(n);
		REP(i,m){
			int u,v,w; SIII(u,v,w);
			adj[u-1].push_back(make_pair(w,v));
			adj[v-1].push_back(make_pair(w,u));
		}

		printf("Case #%d: %d\n", testcase, Dijkstra(adj, 1)[n-1]);
    }

    return 0;
}