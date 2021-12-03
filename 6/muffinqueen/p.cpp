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


bool SAT(vb &bakers, vli &judges, int m, int n){
	REP(i,n){
		bool flag=false;
		for(int r : judges[i]){
			bool sign = r>=0;
			int recipe = abs(r);
			if(bakers[recipe-1]==sign){ flag=true; break; }
		}
		if(!flag){ return false; }
	}
	return true;
}

bool assignements(vb &bakers, vli &judges, int m, int n, int i){
	if(i==m){ return SAT(bakers, judges, m, n); }
	bakers[i]=true;
	if(assignements(bakers, judges, m, n, i+1)){ return true; }
	bakers[i]=false;
	if(assignements(bakers, judges, m, n, i+1)){ return true; }
	return false;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		int m,n; SII(m,n);
		vb bakers(m,true);
		vli judges(n);

		REP(i,n){
			int r; SI(r);
			while(r!=0){ judges[i].push_back(r); SI(r); }
		}

		if(assignements(bakers, judges, m, n, 0)){
			printf("Case #%d: yes\n", testcase);
		}else{
			printf("Case #%d: no\n", testcase);
		}

    }

    return 0;
}
