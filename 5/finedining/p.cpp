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

bool FordFulkersonBFS(vvi &residualAdj, int s, int t, vi &parent){
	int n = residualAdj.size();
  	vb visited(n, false);
  	queue<int> q;
  	q.push(s);
  	visited[s-1] = true;
  	parent[s-1] = -1;

  	while(!q.empty()){
		//cout<<"oui"<<endl;
    	int u = q.front(); q.pop();
    	REP(v,n){
      		if(!visited[v] && residualAdj[u-1][v]>0) {
        		q.push(v+1);
        		parent[v] = u;
        		visited[v] = true;
				if(visited[t-1]){return true;}
      		}
    	}
  	}
  	return visited[t-1];
}


int FordFulkerson(vvi adj, int s, int t){
	int n = adj.size();
	vvi residualAdj(n, vi(n));
	REP(i,n){ REP(j,n){ residualAdj[i][j] = adj[i][j]; } }
  	vi parent(n);
  	int maxFlow = 0;

  	while(FordFulkersonBFS(residualAdj, s, t, parent)){
    	int pathFlow = INF;
		int u;
		int v = t;
		while(v != s){
			u = parent[v-1];
			pathFlow = min(pathFlow, residualAdj[u-1][v-1]);
			v = u;
		}

		v = t;
		while(v != s){
			u = parent[v-1];
			residualAdj[u-1][v-1] -= pathFlow;
			residualAdj[v-1][u-1] += pathFlow;
			v = u;
		}

    	maxFlow += pathFlow;
  	}
  	return maxFlow;
}


int main(){

	int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n,m,b; SIII(n,m,b);
		int N = m+b+2;
		vvi adj(N, vi(N, 0));
		FOR(i,1,m+1,1){ adj[0][i] = 1; }
		FOR(i,1,n+1,1){
			int mi,bi; SII(mi,bi);
			adj[mi][m+bi] = 1;
		}
		FOR(i,1,b+1,1){ adj[m+i][m+b+1] = 1; }

		//REP(i,N){REP(j,N){cout<<adj[i][j]<<" ";}cout<<endl;}

		int maxFlow = FordFulkerson(adj, 1, m+b+2);

		printf("Case #%d: %d\n", testcase, maxFlow);
    }

    return 0;
}
