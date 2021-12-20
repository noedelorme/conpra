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
typedef unordered_map<int,int> umii;

int rec(vi &dp, vi &used, vi &values, int c){
	int n=values.size();

	if(dp[c]!=0){ return dp[c]; }

	int mindpi=INF;
	int mini=0;
	REP(i,n){
		if(c-values[i]>=0){
			int dpi = rec(dp, used, values, c-values[i]);
			if(dpi<=mindpi){
				mindpi=dpi; mini=i;
			}
		}
	}
	
	dp[c]=mindpi+1;
	used[c]=mini;
	return dp[c];
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		int n,c; SII(n,c);
		vi values(n); REP(i,n){ SI(values[i]); }
		vi dp(c+1,0);
		vi used(c+1,0);
		dp[0]=0;
		
		FOR(i,1,c+1,1){
			int mindpj=INF; int minj=0;
			REP(j,n){
				if(i-values[j]>=0){
					if(dp[i-values[j]]<=mindpj){
						mindpj=dp[i-values[j]]; minj=j;
					}
				}
			}
			dp[i]=mindpj+1; used[i]=minj;

		}

		vi coins(n,0);
		int current = c;
		while(current>0){
			coins[used[current]]++;
			current -= values[used[current]];
		}

		printf("Case #%d: ", testcase);
		REP(i,n){ printf("%d ", coins[i]); }
		printf("\n");
    }

    return 0;
}
