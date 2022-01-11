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


/* Compute GCD */
ulint gcd(ulint a, ulint b){
	if(b==0){
		return a;
	}else{
		return gcd(b, a%b);
	}
}

/* Compite LCM */
ulint lcm(ulint a, ulint b){
	return a*b/gcd(a,b);
}

/* Compute positive modulo */
lint modulo(lint a,lint b){ return (a%b+b)%b; }

void solve(vector<ulint> &friends, vl &candies, int n, int i, ulint sum){
    if(i==n-1){
        friends.push_back(sum); //last friend doesn't come
        friends.push_back(sum+(ulint)candies[i]); //last friend come
    }else{
        solve(friends, candies, n, i+1, sum);  //friend i doesn't come
        solve(friends, candies, n, i+1, sum+(ulint)candies[i]); //friend i come
    }
    return;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
        vl candies(n); REP(i,n){ SL(candies[i]); }

        vector<ulint> friends; solve(friends, candies, n, 0, 1);

        ulint x = 1;
        REP(i,friends.size()){
            x = lcm(x,friends[i]);
        }

        printf("Case #%d: %lld\n", testcase, x);
    }

    return 0;
}