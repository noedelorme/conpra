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



int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){

		int N,K,R,D; SI(N); SI(K); SI(R); SI(D);

		vvi adj(N);
		vector<bool> mets(N, false);
		vector<bool> rems(N, false);
		stack<int> S;

		REP(i, K){ int current; SI(current); S.push(current); }
		REP(i, R){ int current; SI(current); rems[current-1]=true; }
		REP(i, D){
			int u,d; SII(u,d);
			adj[u-1].push_back(d);
		}

		while(!S.empty()){
			int current = S.top(); S.pop();
			if(!mets[current-1]){
				mets[current-1] = true;
				if(adj[current-1].size()<=200001){ for(int d : adj[current-1]){ S.push(d); } }
			}
		}

		bool flag = false;
		REP(i, N){
			if(mets[i] && rems[i]){
				flag = true;
				break;
			}
		}

		if(flag){ printf("Case #%d: conflict\n", testcase); }
		else{ printf("Case #%d: ok\n", testcase); }

    }

    return 0;
}