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

bool compare2(Edge a, Edge b){
	if(a.e.first==b.e.first){
		return a.e.second < b.e.second;
	}else{
		return a.e.first < b.e.first;
	}
}

int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){
		int n; SI(n);

		vvi adj(n, vi(n,0));
		REP(i,n){ REP(j,n){ SI(adj[i][j]); } }

		vector<Edge> mst = Kruskal(adj);

		sort(mst.begin(), mst.end(), compare2);

		printf("Case #%d:\n", testcase);
		FOREACH(e, mst){
			printf("%d %d\n", e->e.first, e->e.second);
		}
    }

    return 0;
}