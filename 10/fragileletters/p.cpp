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
bool operator!=(const Point& a, const Point& b){
    return a.x!=b.x || a.y!=b.y;
}

double CCW(Point a, Point b, Point p){
    return (p.y-a.y)*(b.x-a.x)-(p.x-a.x)*(b.y-a.y);
}

//Return the angle defined by ABC (degree)
double angle(Point a, Point b, Point c){
    double aa = pow(b.x-a.x,2) + pow(b.y-a.y,2);
    double bb = pow(b.x-c.x,2) + pow(b.y-c.y,2);
    double cc = pow(c.x-a.x,2) + pow(c.y-a.y,2);
    return acos((aa+bb-cc)/sqrt(4*aa*bb))*180/PI;
}

//Return the centroid of a polygon
Point centroid(vector<Point> points){
    int n = points.size();
    Point centroid = {0, 0};
    double area = 0;
    double x0=0; double y0=0;
    double x1=0; double y1=0;
    double partialArea = 0.0;

    REP(i,n){
        x0 = points[i].x;
        y0 = points[i].y;
        x1 = points[(i+1)%n].x;
        y1 = points[(i+1)%n].y;
        partialArea = x0*y1 - x1*y0;
        area += partialArea;
        centroid.x += (x0+x1)*partialArea;
        centroid.y += (y0+y1)*partialArea;
    }

    area *= 0.5;
    centroid.x /= (6.0*area);
    centroid.y /= (6.0*area);

    return centroid;
}


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
        vector<Point> points(n); REP(i,n){ SD(points[i].x); SD(points[i].y); }

        int count=0;
        REP(i,n){ //For all edges
            Point a = points[i];
            Point b = points[(i+1)%n];

            //Check if all other points are strictly in the same
            //side of the line (a,b) ==> flag
            bool flag = true;
            REP(j,n){
                Point p = points[j];
                Point q = points[(j+1)%n];
                if(p!=a && p!=b && q!=a && q!=b){
                    double ccwp = CCW(a,b,p);
                    double ccwq = CCW(a,b,q);
                    flag &= (ccwp>0 && ccwq>0) || (ccwp<0 && ccwq<0);
                }
            }

            Point G = centroid(points);
            //Test if the centroid is above the lowermost edge (with angles)
            if(flag && angle(G,a,b)<=90 && angle(G,b,a)<=90){ count++; }
        }

		printf("Case #%d: %d\n", testcase, count);
    }


    return 0;
}
