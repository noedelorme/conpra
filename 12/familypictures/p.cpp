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

vector<vector<double>> matrixInverse(vector<vector<double>> M){
    double det = 0;
    REP(i,3){
        det = det + (M[0][i] * (M[1][(i+1)%3] * M[2][(i+2)%3] - M[1][(i+2)%3] * M[2][(i+1)%3]));
    }

    vector<vector<double>> MInv({
            {0,0,0},
            {0,0,0},
            {0,0,0}
    });
    REP(i,3){
        REP(j,3){
            MInv[i][j] = ((M[(j+1)%3][(i+1)%3] * M[(j+2)%3][(i+2)%3]) - (M[(j+1)%3][(i+2)%3] * M[(j+2)%3][(i+1)%3]))/ det;
        }
    }

    return MInv;
}

Vect matrixProductVector(vector<vector<double>> M, Vect v){
    double x = v.x*M[0][0] + v.y*M[0][1] + v.z*M[0][2];
    double y = v.x*M[1][0] + v.y*M[1][1] + v.z*M[1][2];
    double z = v.x*M[2][0] + v.y*M[2][1] + v.z*M[2][2];

    return {x,y,z};
}

vector<vector<double>> matrixProduct(vector<vector<double>> M, vector<vector<double>> N){
    vector<vector<double>> product({
            {0,0,0},
            {0,0,0},
            {0,0,0}
    });
    REP(i,3){
        REP(j,3){
            product[i][j] = M[i][0]*N[0][j] + M[i][1]*N[1][j] + M[i][2]*N[2][j];
        }
    }

    return product;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
        double ax,ay,bx,by,cx,cy,dx,dy,ex,ey,fx,fy;
        SD(ax);SD(ay);SD(bx);SD(by);SD(cx);SD(cy);
        SD(dx);SD(dy);SD(ex);SD(ey);SD(fx);SD(fy);

        Vect a = {1,0,0};
        Vect b = {0,1,0};
        Vect c = {0,0,1};
        Vect d = {1,1,1};

        Vect ap = {ax,ay,1};
        Vect bp = {bx,by,1};
        Vect cp = {cx,cy,1};
        Vect dp = {dx,dy,1};

        //Compute M1 and M1Inv
        vector<vector<double>> M1temp({
            {ap.x,bp.x,cp.x},
            {ap.y,bp.y,cp.y},
            {ap.z,bp.z,cp.z}
        });
        vector<vector<double>> M1tempInv = matrixInverse(M1temp);
        Vect lambda1 = matrixProductVector(M1tempInv,dp);
        vector<vector<double>> M1({
            {lambda1.x*ap.x,lambda1.y*bp.x,lambda1.z*cp.x},
            {lambda1.x*ap.y,lambda1.y*bp.y,lambda1.z*cp.y},
            {lambda1.x*ap.z,lambda1.y*bp.z,lambda1.z*cp.z}
        });
        vector<vector<double>> M1Inv = matrixInverse(M1);

        //Compute M2 and M2Inv
        vector<vector<double>> M2temp({
            {0,1,1},
            {0,0,1},
            {1,1,1}
        });
        vector<vector<double>> M2tempInv = matrixInverse(M2temp);
        Vect lambda2 = matrixProductVector(M2tempInv,{0,1,1});
        vector<vector<double>> M2({
            {lambda2.x*0,lambda2.y*1,lambda2.z*1},
            {lambda2.x*0,lambda2.y*0,lambda2.z*1},
            {lambda2.x*1,lambda2.y*1,lambda2.z*1}
        });
        vector<vector<double>> M2Inv = matrixInverse(M2);

        //Compute general projective transformation
        vector<vector<double>> M = matrixProduct(M2,M1Inv);

        Vect realA = matrixProductVector(M,ap);
        Vect realB = matrixProductVector(M,bp);
        Vect realC = matrixProductVector(M,cp);
        Vect realD = matrixProductVector(M,dp);

        realA.normalize();
        realB.normalize();
        realC.normalize();
        realD.normalize();

        //Computing Lea's height
        Vect lea = {ex,ey,1};
        Vect clock = {fx,fy,1};

        Vect realLea = matrixProductVector(M,lea);
        Vect realClock = matrixProductVector(M,clock);

        realLea.normalize();
        realClock.normalize();

        printf("Case #%d: %lf\n", testcase, realLea.y/realClock.y);

    }

    return 0;
}