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


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int l,n,d; SIII(l,n,d);
		vi lights(n);
		REP(i,n){ SI(lights[i]); }
		sort(lights.begin(),lights.end());

		int pos = 0;
		int nextLight = 0;
		int usedLights = 0;
		bool flag = true;

		while(pos<l){
			flag = false;
			for(int i=nextLight; i<n; i++){
				if(pos>=lights[i]-d){
					nextLight = i;
					flag = true;
				}else{ break; }
			}
			if(flag){
				pos = lights[nextLight]+d;
				usedLights++; nextLight++;
			}else{ break; }
		}
		
		if(flag){
			printf("Case #%d: %d\n", testcase, usedLights);
		}else{
			printf("Case #%d: impossible\n", testcase);
		}
		
    }

    return 0;
}
