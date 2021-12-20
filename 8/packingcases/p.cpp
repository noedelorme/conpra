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

typedef struct Case{ int x,y,z; } Case;

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		int h,n; SII(h,n);
		vector<Case> cases(3*n);
		REP(i,n){
			int x,y,z; SIII(x,y,z);

			/*//the 6 possible rotations of the case type
			cases[0*n+i].x = x;
			cases[0*n+i].y = y;
			cases[0*n+i].z = z;

			cases[1*n+i].x = x;
			cases[1*n+i].y = z;
			cases[1*n+i].z = y;

			cases[3*n+i].x = y;
			cases[3*n+i].y = x;
			cases[3*n+i].z = z;

			cases[3*n+i].x = y;
			cases[3*n+i].y = z;
			cases[3*n+i].z = x;

			cases[4*n+i].x = z;
			cases[4*n+i].y = x;
			cases[4*n+i].z = y;

			cases[5*n+i].x = z;
			cases[5*n+i].y = y;
			cases[5*n+i].z = x;*/

			//We can, w.l.o.g only wonsider the rotations s.t. x>y
			cases[i].x = max(y,z);
			cases[i].y = min(y,z);
			cases[i].z = x;

			cases[n+i].x = max(x,z);
			cases[n+i].y = min(x,z);
			cases[n+i].z = y;

			cases[2*n+i].x = max(x,y);
			cases[2*n+i].y = min(x,y);
			cases[2*n+i].z = z;
		}

		//sorting according to the area of the base (x*y)
		sort(cases.begin(), cases.end(), [](const Case a, const Case b){
			return a.x*b.y>b.x*b.y;
		});

		//maxHeight[i]: Maximum height with can achieve by ending with case i
		vi maxHeight(3*n,0);
		//initialization with the case as the only case of the stack
		REP(i,3*n){ maxHeight[i]=cases[i].z; }

		//looking for better precessessor
		FOR(i,0,3*n,1){
			FOR(j,0,i,1){
				if(cases[i].x<cases[j].x && cases[i].y<cases[j].y){
					if(maxHeight[j]+cases[i].z>maxHeight[i]){
						maxHeight[i] = maxHeight[j]+cases[i].z;
					}
				}
			}
		}

		//computing the maximum heigh that can be reached
		int maximum = 0;
		REP(i,3*n){ maximum = max(maximum, maxHeight[i]); }

		if(maximum>=h){
			printf("Case #%d: yes\n", testcase);
		}else{
			printf("Case #%d: no\n", testcase);
		}
		
    }

    return 0;
}
