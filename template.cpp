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
		

		printf("Case #%d: \n", testcase);
    }

    return 0;
}

/* Union Find Integer */
map<int, pair<int, unsigned int>> Sets;
void AddSet(int x){ Sets.insert(make_pair(x, make_pair(x, 1))); }
int Find(int x){
	if(Sets[x].first == x){ return x; }
	else{ return Sets[x].first = Find(Sets[x].first); }
}
void Union(int x, int y) {
	int parentX = Find(x), parentY = Find(y);
	int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
	if (parentX == parentY){ return; }
	else if(rankX < rankY){
		Sets[parentX].first = parentY;
		Sets[parentY].second += Sets[parentX].second;
	}else{
		Sets[parentY].first = parentX;
		Sets[parentX].second += Sets[parentY].second;
	}
}
int Size(int x){ return Sets[Find(x)].second; }
void Reset(){ Sets.clear(); }

/* Kruskal's Algorithm (Minimum spanning tree) */
typedef struct Edge{
	pii e;
	int w;
} Edge;
bool compareWeight(Edge a, Edge b){ return a.w < b.w; }
vector<Edge> Kruskal(vvi adj){
	int n = adj.size();
	vector<Edge> mst;
	vector<Edge> edges;
	FOR(i,1,n,1){
		FOR(j,0,i,1){
			edges.push_back({make_pair(j+1,i+1),adj[i][j]});
		}
	}
	sort(edges.begin(), edges.end(), compareWeight);
	REP(i,n){ AddSet(i); }
	for(auto e : edges){
		if(Find(e.e.first-1)!=Find(e.e.second-1)){
			mst.push_back(e);
			Union(e.e.first-1,e.e.second-1);
		}
	}
	Reset();
	return mst;
}

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

/* Dijkstra's Algorithm (Shortest paths from source) */
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

/* Bellman-Ford's Algorithm (Shortest paths from source and negative weight) */
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

/* Chrono */
auto start = chrono::steady_clock::now();
auto stop = chrono::steady_clock::now();
chrono::duration<double> duration = stop-start;
cout << "duration: " << duration.count() << "s\n";
