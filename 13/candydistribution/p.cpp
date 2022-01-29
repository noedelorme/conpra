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

lint gcd(lint a, lint b){
	if(b==0){
		return a;
	}else{
		return gcd(b, a%b);
	}
}


/*
Chinese Remainder Theorem implementation
SOURCE: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
*/
lint inv(lint a, lint m){
	lint m0 = m, t, q;
	lint x0 = 0, x1 = 1;
	if (m == 1) return 0;
 
	while (a > 1) {
		q = a / m;
		t = m;
		m = a % m, a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	if (x1 < 0) x1 += m0;
	return x1;
}
lint findMinX(lint num[], lint rem[], int k){
	lint prod = 1;
	for (int i = 0; i < k; i++)
	prod *= num[i];
    lint result = 0;
	for (int i = 0; i < k; i++) {
		lint pp = prod / num[i];
		result += rem[i] * inv(pp, num[i]) * pp;
	}
	return result % prod;
}


int main(){

	int t; SI(t); FOR(testcase, 1, t+1){
		lint K,C; SL(K); SL(C);
		lint num[] = {K, C};
		lint rem[] = {1, 0};

		if(gcd(K,C)==1){
			printf("Case #%d: %lld\n", testcase, findMinX(num,rem,2)/C);
		}else{
			printf("Case #%d: impossible\n", testcase);
		}
	}

	return 0;
}