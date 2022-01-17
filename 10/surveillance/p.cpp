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


struct Point{
    double x, y;
    Point() {};
    Point(double _x, double _y): x(_x), y(_y) {};
};

double dist(Point a, Point b){ return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2)); }
double area(double r){ return PI*r*r; }

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
        vector<Point> cameras(n);
        REP(i,n){ SD(cameras[i].x); SD(cameras[i].y); }

        //Normal case: other cameras have maximal radius
        double radiusOtherCam = INF;
        REP(i,n){
            FOR(j,i+1,n,1){
                if(i==0){
                    radiusOtherCam = min(radiusOtherCam, dist(cameras[i],cameras[j]));
                }else{
                    radiusOtherCam = min(radiusOtherCam, dist(cameras[i],cameras[j])/2);
                }
                
            }
        }
        double radiusFirstCamNormalCase = INF;
        FOR(i,1,n,1){
            radiusFirstCamNormalCase = min(radiusFirstCamNormalCase, dist(cameras[0],cameras[i])-radiusOtherCam);
        }
        double areaNormalCase = (n-1)*area(radiusOtherCam)+area(radiusFirstCamNormalCase);

        //Special case: first camera have maximal radius
        double radiusFirstCam = INF;
        FOR(i,1,n,1){
            radiusFirstCam = min(radiusFirstCam, dist(cameras[0],cameras[i]));
        }
        double areaSpecialCase = area(radiusFirstCam);


		printf("Case #%d: %lf\n", testcase, max(areaNormalCase,areaSpecialCase));
    }

    return 0;
}
