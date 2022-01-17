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
    int x, y;
    Point() {};
    Point(int _x, int _y): x(_x), y(_y) {};
};
bool operator!=(const Point& a, const Point& b){
    return a.x!=b.x || a.y!=b.y;
}
bool operator==(const Point& a, const Point& b){
    return a.x==b.x && a.y==b.y;
}
bool operator<(const Point& a, const Point& b){
   if(a.x!=b.x){ return a.x<b.x; }
   else{ return a.y<b.y; }
}

struct Triangle{
    Point a,b,c;
    vector<Point> toVector(){
        vector<Point> vec;
        vec.push_back(a);
        vec.push_back(b);
        vec.push_back(c);
        return vec;
    }
};

struct Rectangle{
    Point a,b,c,d;
    vector<Point> toVector(){
        vector<Point> vec;
        vec.push_back(a);
        vec.push_back(b);
        vec.push_back(c);
        vec.push_back(d);
        return vec;
    }
};




/*
An algorithm that 
    - checks if a point is inside a polygon (isInside).
    - checks if two given line segments intersect (doIntersect).
SOURCE: https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
*/
#define INF 10000 
// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
            (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0; // collinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are collinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
    // p2, q2 and q1 are collinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(vector<Point> polygon, int n, Point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3) return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, p.y+1001}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is collinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
            return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1; // Same as (count%2 == 1) 
} 







/*
    Check if angle abc is a right angle (90°).
*/
bool orthoAngle(Point a, Point b, Point c){
    return (b.x-a.x)*(b.x-c.x)+(b.y-a.y)*(b.y-c.y) == 0;
}
bool isRectangle(Point a, Point b, Point c, Point d){
    return orthoAngle(a, b, c) && orthoAngle(b, c, d) && orthoAngle(c, d, a);
}

/*
    Check if a triangle intersect with a rectangle.
*/
bool triangleIntersectRectange(Rectangle rect, Triangle tri){
    Point ra = rect.a, rb = rect.b, rc = rect.c, rd = rect.d;
    Point ta = tri.a, tb = tri.b, tc = tri.c;

    //Check segment intersections
    bool test = doIntersect(ra,rb,ta,tb) || doIntersect(ra,rb,tb,tc) || doIntersect(ra,rb,tc,ta)
            ||  doIntersect(rb,rc,ta,tb) || doIntersect(rb,rc,tb,tc) || doIntersect(rb,rc,tc,ta)
            ||  doIntersect(rc,rd,ta,tb) || doIntersect(rc,rd,tb,tc) || doIntersect(rc,rd,tc,ta)
            ||  doIntersect(rd,ra,ta,tb) || doIntersect(rd,ra,tb,tc) || doIntersect(rd,ra,tc,ta);

    //test |= doIntersect(ra,rc,ta,tb) || doIntersect(ra,rc,tb,tc) || doIntersect(ra,rc,tc,ta)
    //    ||  doIntersect(rb,rd,ta,tb) || doIntersect(rb,rd,tb,tc) || doIntersect(rb,rd,tc,ta);

    //Check if triangle inside rectangle
    test |= isInside(rect.toVector(), 4, ta);

    //Check if rectangle inside triangle
    test |= isInside(tri.toVector(), 3, ra);

    return test;
}




int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
		int n; SI(n);
        vector<Point> points(n); REP(i,n){ SII(points[i].x, points[i].y); }
        vector<vector<Point>> configs;


        //We compute all possible configs with a rectangle
        FOR(i,0,n){ FOR(j,i+1,n){ FOR(k,j+1,n){ FOR(l,k+1,n){
            //Check order ABCD
            if(isRectangle(points[i],points[j],points[k],points[l])){
                vector<Point> config;
                config.push_back(points[i]);
                config.push_back(points[j]);
                config.push_back(points[k]);
                config.push_back(points[l]);
                REP(m,n){
                    if(m!=i && m!=j && m!=k && m!=l){ config.push_back(points[m]); }
                }
                configs.push_back(config);
            }
            //Check order ACBD
            else if(isRectangle(points[i],points[k],points[j],points[l])){
                vector<Point> config;
                config.push_back(points[i]);
                config.push_back(points[k]);
                config.push_back(points[j]);
                config.push_back(points[l]);
                REP(m,n){
                    if(m!=i && m!=j && m!=k && m!=l){ config.push_back(points[m]); }
                }
                configs.push_back(config);
            }
            //Check order ACDB
            else if(isRectangle(points[i],points[k],points[l],points[j])){
                vector<Point> config;
                config.push_back(points[i]);
                config.push_back(points[k]);
                config.push_back(points[l]);
                config.push_back(points[j]);
                REP(m,n){
                    if(m!=i && m!=j && m!=k && m!=l){ config.push_back(points[m]); }
                }
                configs.push_back(config);
            }
        } } } }


        //For each possible config (with a rectangle)
        //Check all possible triangles with remaining points
        //For each possible triangle, check intersection with rectangle
        bool flag = false;
        Rectangle rect;
        Triangle tri;
        REP(i, configs.size()){
            FOR(j,4,n){
                FOR(k,j+1,n){
                    FOR(l,k+1,n){
                        Rectangle currentRect;
                        currentRect.a = configs[i][0];
                        currentRect.b = configs[i][1];
                        currentRect.c = configs[i][2];
                        currentRect.d = configs[i][3];

                        //a,b,c are points of the current triangle
                        Triangle currentTri;
                        currentTri.a = configs[i][j];
                        currentTri.b = configs[i][k];
                        currentTri.c = configs[i][l];

                        if(!triangleIntersectRectange(currentRect, currentTri)){
                            flag = true;
                            tri = currentTri;
                            rect = currentRect;
                            break;
                        }
                    }if(flag){break;}
                }if(flag){break;}
            }if(flag){break;}
        }


        if(flag){
            printf("Case #%d: possible\n", testcase);
            printf("%d %d\n", rect.a.x, rect.a.y);
            printf("%d %d\n", rect.b.x, rect.b.y);
            printf("%d %d\n", rect.c.x, rect.c.y);
            printf("%d %d\n", rect.d.x, rect.d.y);
            printf("%d %d\n", tri.a.x, tri.a.y);
            printf("%d %d\n", tri.b.x, tri.b.y);
            printf("%d %d\n", tri.c.x, tri.c.y);
        }else{
            printf("Case #%d: impossible\n", testcase);
        }
    }

    return 0;
}
