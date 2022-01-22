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
#define FOR(i, s, k) for(int i=s; i<k; i++)
#define REP(i, n) FOR(i, 0, n)
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

struct Vect{
	double x,y,z;

	void normalize(){
		if(abs(z)>0.00000001){
			x = x/z;
			y = y/z;
			z = 1;
		}
	}
};

Vect crossProduct(Vect a, Vect b){
	return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
		double x11,y11,x12,y12,x13,y13,x21,y21,x22,y22,x23,y23;
		SD(x11);SD(y11);SD(x12);SD(y12);SD(x13);SD(y13);
		SD(x21);SD(y21);SD(x22);SD(y22);SD(x23);SD(y23);

		Vect crossguard11 = {x11,y11,1};
		Vect crossguard12 = {x12,y12,1};
		Vect pommel1 = {x13,y13,1};
		Vect crossguard1line = crossProduct(crossguard11, crossguard12);
		Vect q1 = crossProduct(crossguard1line, {0,0,1});
		Vect r1 = {q1.y, -q1.x, 0};
		Vect m1 = crossProduct(pommel1, r1);

		Vect crossguard21 = {x21,y21,1};
		Vect crossguard22 = {x22,y22,1};
		Vect pommel2 = {x23,y23,1};
		Vect crossguard2line = crossProduct(crossguard21,crossguard22);
		Vect q2 = crossProduct(crossguard2line, {0,0,1});
		Vect r2 = {q2.y, -q2.x, 0};
		Vect m2 = crossProduct(pommel2, r2);

		Vect intersection = crossProduct(m1, m2);
		intersection.normalize();
		
		//If intersection point is at infinity
		if(abs(intersection.z)<0.0000001){
			printf("Case #%d: strange\n", testcase);
		}else{
			Vect base1 = crossProduct(m1, crossguard1line);
			base1.normalize();
			Vect base2 = crossProduct(m1, crossguard1line);
			base2.normalize();
			//If two hilts overlap
			if(intersection.y<base1.y || intersection.y<base2.y){
				printf("Case #%d: strange\n", testcase);
			}
			//Normal case
			else{
				printf("Case #%d: %lf %lf\n", testcase, intersection.x, intersection.y);
			}
		}
		
    }

    return 0;
}