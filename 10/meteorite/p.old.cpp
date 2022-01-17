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



/*
An algorithm to check if a given point lies inside a polygon.
Source: https://www.tutorialspoint.com/Check-if-a-given-point-lies-inside-a-Polygon
*/

struct Point {
   int x, y;
   Point() {};
    Point(int _x, int _y): x(_x), y(_y) {};
};
bool operator==(const Point& a, const Point& b){
    return a.x==b.x && a.y==b.y;
}
bool operator<(const Point& a, const Point& b){
   if(a.x!=b.x){ return a.x<b.x; }
   else{ return a.y<b.y; }
}

struct line {
   Point p1, p2;
};

bool onLine(line l1, Point p) {        //check whether p is on the line or not
   if(p.x <= max(l1.p1.x, l1.p2.x) && p.x <= min(l1.p1.x, l1.p2.x) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y <= min(l1.p1.y, l1.p2.y)))
         return true;

   return false;
}

int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           //colinear
   else if(val < 0)
      return 2;          //anti-clockwise direction
      return 1;          //clockwise direction
}

bool isIntersect(line l1, line l2) {
   //four direction for two lines and points of other line
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);

   if(dir1 != dir2 && dir3 != dir4)
      return true;           //they are intersecting
   if(dir1==0 && onLine(l1, l2.p1))        //when p2 of line2 are on the line1
      return true;
   if(dir2==0 && onLine(l1, l2.p2))         //when p1 of line2 are on the line1
      return true;
   if(dir3==0 && onLine(l2, l1.p1))       //when p2 of line1 are on the line2
      return true;
   if(dir4==0 && onLine(l2, l1.p2)) //when p1 of line1 are on the line2
      return true;
   return false;
}

bool checkInside(vector<Point> poly, int n, Point p) {
   if(n < 3)
      return false;                  //when polygon has less than 3 edge, it is not polygon
   line exline = {p, {9999, p.y}};   //create a point at infinity, y is same as point p
   int count = 0;
   int i = 0;
   do {
      line side = {poly[i], poly[(i+1)%n]};     //forming a line from two consecutive points of poly
      if(isIntersect(side, exline)) {          //if side is intersects exline
         if(direction(side.p1, p, side.p2) == 0)
            return onLine(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;             //when count is odd
}


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
      Point meteor; int n; SIII(meteor.x,meteor.y,n);
      vector<Point> points;
      unordered_map<int,Point> hash;
      REP(i,n){
        Point a,b; SIIII(a.x,a.y,b.x,b.y);
        hash[(a.x+1000)*1000+a.y+1000]=Point(a.x,a.y);
        hash[(b.x+1000)*1000+b.y+1000]=Point(b.x,b.y);
      }

      for(pair<int, Point> p : hash){
        points.push_back(p.second);
      }


      checkInside(points, n, meteor) ? printf("Case #%d: jackpot\n", testcase) : printf("Case #%d: too bad\n", testcase);
		
    }

    return 0;
}
