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
typedef vector<list<pair<int,int>>> vlpii;
typedef vector<bool> vb;


int Prim(vlpii adj, vi control, int l){
	int n = adj.size();
	vb visited(n, false);
	priority_queue<pii> PQ;
	int cost = 0;
	PQ.push(make_pair(10000,1));

	int minPossibleLevel = l;
	int minHallwayLevel = 10000;

	while(!PQ.empty()){
		pii p = PQ.top(); PQ.pop();
		int v = p.second;
		int w = p.first;

		if(!visited[v-1]){
			if(w<minPossibleLevel){ return -1; }
			minHallwayLevel = min(minHallwayLevel, w);
			minPossibleLevel = min(minPossibleLevel, control[v-1]);
			

			cost+=w;
			visited[v-1]=true;
			for(pii nei : adj[v-1]){
				if(!visited[nei.second-1]){
					PQ.push(nei);
				}
			}
		}
	}
	return min(l,minHallwayLevel);
}


int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){
        int n,m,k,l; SIIII(n,m,k,l);

		vlpii adj(n);
		REP(i,m){
			int a,b,w; SIII(a,b,w);
			adj[a-1].push_back(make_pair(w,b));
			adj[b-1].push_back(make_pair(w,a));
		}
		vi control(n,l);
		REP(i,k){ int a,d; SII(a,d); control[a-1] = d; }

		int r = Prim(adj, control, l);
		if(r==-1){
			printf("Case #%d: impossible\n", testcase);
		}else{
			printf("Case #%d: %d\n", testcase, r);
		}
		
    }

    return 0;
}