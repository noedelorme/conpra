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
typedef list<pii> lii;
typedef vector<li> vli;


pii dfs(vli adj, vi& parents, int i){
	int n = adj.size();
	int farest = i;
	int distance = 0;
	vector<bool> visited(n);

	stack<pii> S;
	S.push(make_pair(i,0));
	while(!S.empty()){
		pii p = S.top(); S.pop();
		int v = p.first;
		int d = p.second;
		if(!visited[v-1]){
			if(d>distance){
				farest=v;
				distance=d;
			}
			visited[v-1]=true;
			for(int j : adj[v-1]){
				if(!visited[j-1]){
					S.push(make_pair(j,d+1));
					parents[j-1] = v;
				}	
			}
		}
	}
	return make_pair(farest,distance);
}

int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){
		int n; SI(n);

		vli adj(n);
		REP(i,n-1){
			int x,y; SII(x,y);
			adj[x-1].push_back(y);
			adj[y-1].push_back(x);
		}
        
		vi parents(n, -1);
		pii data1 = dfs(adj, parents, 1);
		int a = data1.first;
		pii data2 = dfs(adj, parents, a);
		int b = data2.first;
		int width = data2.second;

		int middle = b; REP(i, width/2){ middle=parents[middle-1]; }

		printf("Case #%d: %d\n", testcase, middle);
    }

    return 0;
}