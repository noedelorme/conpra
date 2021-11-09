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
#define INF (int)1e9
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
typedef vector<li> vli;


int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){
        

		printf("Case #%d: \n", testcase);
    }

    return 0;
}

/* UNION FIND INTEGER */
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

/*
auto start = chrono::steady_clock::now();
auto stop = chrono::steady_clock::now();
chrono::duration<double> duration = stop-start;
cout << "duration: " << duration.count() << "s\n";
*/