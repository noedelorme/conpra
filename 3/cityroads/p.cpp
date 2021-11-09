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
#define P(x) cout<<"> "<<x<<endl
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


vi topologicalSort(vli adj){
	int n = adj.size();
	vi o(n,-1);
	vi pres(n,0); 
	REP(i,n){ for(int j : adj[i]){ pres[j-1]++; } }
	stack<int> S;
	int i=1;
	REP(u,n){
		if(pres[u]==0){
			if(o[u]==-1){ S.push(u+1); }
			while(!S.empty()){
				int v = S.top(); S.pop();
				o[v-1] = i; i++;
				for(int w : adj[v-1]){
					pres[w-1]--;
					if(pres[w-1]==0){ S.push(w); }
				}
			}
		}
	}
	return o;
}

bool isCyclicRecurence(vli* adj, vector<bool>* visited, vector<bool>* visiting, int i){
	if((*visiting)[i]){ return true; }
	if((*visited)[i]){ return false; }
	(*visited)[i] = true;
	(*visiting)[i] = true;
	for(int j : (*adj)[i]){
		if(isCyclicRecurence(adj, visited, visiting, j-1)){ return true; }
	}
	(*visiting)[i] = false;
	return false;
}

bool isCyclic(vli adj){
	int n = adj.size();
	vector<bool> visited(n, false);
	vector<bool> visiting(n, false);
	REP(i,n){
		if(isCyclicRecurence(&adj, &visited, &visiting, i)){ return true; }
	}	
	return false;
}

int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){

		int n,m,l; SIII(n,m,l);
		vli adj(n);
		REP(i, m){ int a,b; SII(a,b); adj[a-1].push_back(b); }

		vi topo = topologicalSort(adj);
		vii edges;

		REP(i, l){
			int a,b; SII(a,b);
			if(topo[a-1]<topo[b-1]){
				adj[a-1].push_back(b);
				edges.push_back(make_pair(a,b));
			}else{
				adj[b-1].push_back(a);
				edges.push_back(make_pair(b,a));
			}
		}
		
		if(isCyclic(adj)){
			printf("Case #%d: no\n", testcase);
		}else{
			printf("Case #%d: yes\n", testcase);
			for(pii e : edges){
				printf("%d %d\n", e.first, e.second);
			}
		}

    }

    return 0;
}