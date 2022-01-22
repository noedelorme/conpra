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

Vect vectorAddition(Vect u, Vect v){
    return {u.x+v.x, u.y+v.y, 1};
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
        int n,d,a; SIII(n,d,a);
        string s; cin>>s;
        double arad = a*(2*PI)/360;

        unordered_map<char,string> prods;
        REP(i,n){
            string prod; cin>>prod;
            char x = prod[0];
            string y = prod.substr(3,prod.length());
            prods[x] = y;
        }
        prods['+'] = "+";
        prods['-'] = "-";

        string instructions = s;
        REP(i,d){
            string temp;
            for(char c : instructions){
                temp += prods[c];
            }
            instructions = temp;
        }

        Vect pos = {0,0,1};
        Vect dir = {1,0,1};

        vector<vector<double>> rotPos({
            {cos(arad), -sin(arad),0},
            {sin(arad), cos(arad),0},
            {0,0,1}
        });

        vector<vector<double>> rotNeg({
            {cos(-arad), -sin(-arad),0},
            {sin(-arad), cos(-arad),0},
            {0,0,1}
        });

        printf("Case #%d:\n", testcase);
        printf("%lf %lf\n", pos.x, pos.y);

        int m = instructions.length();
        REP(i,m){
            char currentChar = instructions[i];
            if(currentChar == '+'){
                dir = matrixProductVector(rotPos, dir);
            }else if(currentChar == '-'){
                dir = matrixProductVector(rotNeg, dir);
            }else{
                dir.normalize();
                pos = vectorAddition(pos, dir);
                pos.normalize();
                printf("%lf %lf\n", pos.x, pos.y);
            }
        }
    }

    return 0;
}