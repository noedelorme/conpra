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
		double x1,y1,x2,y2,x3,y3;
		SD(x1);SD(y1);
        SD(x2);SD(y2);
        SD(x3);SD(y3);
		
        Vect p1 = {x1,y1,1};
        Vect p2 = {x2,y2,1};
        Vect p3 = {x3,y3,1};

        Vect m12 = {(p1.x+p2.x)/2, (p1.y+p2.y)/2, 1};
        Vect m23 = {(p2.x+p3.x)/2, (p2.y+p3.y)/2, 1};
        Vect m31 = {(p3.x+p1.x)/2, (p3.y+p1.y)/2, 1};

        //Centroid
        Vect median12 = crossProduct(p3, m12);
        Vect median23 = crossProduct(p1, m23);

        Vect centroid = crossProduct(median12, median23);
        centroid.normalize();

        //Orthocenter
        Vect line12 = crossProduct(p1, p2);
        Vect q12 = crossProduct(line12, {0,0,1});
        Vect r12 = {q12.y, -q12.x, 0};
        Vect altitude12 = crossProduct(p3, r12);

        Vect line23 = crossProduct(p2, p3);
        Vect q23 = crossProduct(line23, {0,0,1});
        Vect r23 = {q23.y, -q23.x, 0};
        Vect altitude23 = crossProduct(p1, r23);

        Vect orthocenter = crossProduct(altitude12, altitude23);
        orthocenter.normalize();

        //Circumcenter
        Vect bisector12 = crossProduct(m12, r12);
        Vect bisector23 = crossProduct(m23, r23);

        Vect circumcenter = crossProduct(bisector12, bisector23);
        circumcenter.normalize();

        printf("Case #%d:\n", testcase);
        printf("%lf %lf\n", centroid.x, centroid.y);
        printf("%lf %lf\n", orthocenter.x, orthocenter.y);
        printf("%lf %lf\n", circumcenter.x, circumcenter.y);
    }

    return 0;
}