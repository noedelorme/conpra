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

typedef struct Tournament{
	int a,b,p;
} Tournament;

int gain(vector<list<Tournament>> &data, vi &memo, int t){
	if(t==0){ return 0; }
	if(memo[t]!=-1){ return memo[t]; }

	int gainMax = gain(data, memo, t-1);
	for(Tournament trmt : data[t]){
		int gainWithTrmt = trmt.p + gain(data, memo, trmt.a-1); //gain with trmt
		gainMax = max(gainMax, gainWithTrmt);
	}

	memo[t] = gainMax;
	return memo[t];
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		int n; SI(n);
		vector<Tournament> tournaments(n);
		int T = 0; //max date
		REP(i,n){
			int a,b,p; SIII(a,b,p);
			tournaments[i].a = a;
			tournaments[i].b = b;
			tournaments[i].p = p;
			T = max(T,b);
		}
		vector<list<Tournament>> data(T+1); //data[t]: list of tournament ending at day t
		REP(i,n){
			data[tournaments[i].b].push_back(tournaments[i]);
		}

		vi memo(T+1,-1); //memoization
		int g = gain(data, memo, T);

		printf("Case #%d: %d\n", testcase, g);
    }

    return 0;
}