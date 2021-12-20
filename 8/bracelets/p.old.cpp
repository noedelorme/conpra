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


string reverseString(string str){
	int n=str.size();
	string newStr = str;
    FOR(i,0,n/2,1){ swap(newStr[i], newStr[n-i-1]); }
	return newStr;
}

int lcs(vvi &dp, string a, string b, int m, int n){
	if(m==0 || n==0){
		return 0;
	}else if(dp[m-1][n-1]!=-1){ 
		return dp[m-1][n-1];
	}else if(a[m-1] == b[n-1]){
		dp[m-1][n-1] = lcs(dp,a,b,m-1,n-1)+1;
        return dp[m-1][n-1];
	}else{
		dp[m-1][n-1] = max(lcs(dp,a,b,m,n-1), lcs(dp,a,b,m-1,n));
        return dp[m-1][n-1];
	}
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		string a,b; cin>>a>>b;
		int m = a.size();
    	int n = b.size();

		// a = abcde
		// aCycle = abcdeabcd
		// aTail = abcd

		/* Compute the longest commom subsequence of the cycle */
		string aCycle = a + a.substr(0, a.size()-1);
		string bCycle = b + b.substr(0, b.size()-1);
		int mCycle = aCycle.size();
    	int nCycle = bCycle.size();

		vvi dp_a_b_cycle(mCycle, vi(nCycle,-1)); dp_a_b_cycle[0][0]=0;
		int a_b_cycle = lcs(dp_a_b_cycle,aCycle,bCycle,mCycle,nCycle);// - dp_a_b[m-1][n-1];

		vvi dp_ra_b_cycle(mCycle, vi(nCycle,-1)); dp_ra_b_cycle[0][0]=0;
		int ra_b_cycle = lcs(dp_ra_b_cycle,reverseString(aCycle),bCycle,mCycle,nCycle);// - dp_ra_b[m-1][n-1];

		vvi dp_a_rb_cycle(mCycle, vi(nCycle,-1)); dp_a_rb_cycle[0][0]=0;
		int a_rb_cycle = lcs(dp_a_rb_cycle,aCycle,reverseString(bCycle),mCycle,nCycle);// - dp_a_rb[m-1][n-1];

		vvi dp_ra_rb_cycle(mCycle, vi(nCycle,-1)); dp_ra_rb_cycle[0][0]=0;
		int ra_rb_cycle = lcs(dp_ra_rb_cycle,reverseString(aCycle),reverseString(bCycle),mCycle,nCycle);// - dp_ra_rb[m-1][n-1];

		/* Compute the longest commom subsequence of the tail */
		string aTail = a.substr(0, a.size()-1);
		string bTail = b.substr(0, b.size()-1);
		int mTail = aTail.size();
    	int nTail = bTail.size();

		vvi dp_a_b_tail(mTail, vi(nTail,-1)); dp_a_b_tail[0][0]=0;
		int a_b_tail = lcs(dp_a_b_tail,aTail,bTail,mTail,nTail);

		vvi dp_ra_b_tail(mTail, vi(nTail,-1)); dp_ra_b_tail[0][0]=0;
		int ra_b_tail = lcs(dp_ra_b_tail,reverseString(aTail),bTail,mTail,nTail);

		vvi dp_a_rb_tail(mTail, vi(nTail,-1)); dp_a_rb_tail[0][0]=0;
		int a_rb_tail = lcs(dp_a_rb_tail,aTail,reverseString(bTail),mTail,nTail);

		vvi dp_ra_rb_tail(mTail, vi(nTail,-1)); dp_ra_rb_tail[0][0]=0;
		int ra_rb_tail = lcs(dp_ra_rb_tail,reverseString(aTail),reverseString(bTail),mTail,nTail);


		int a_b = a_b_cycle - a_b_tail;
		int ra_b = ra_b_cycle - ra_b_tail;
		int a_rb = a_rb_cycle - a_rb_tail;
		int ra_rb = ra_rb_cycle - ra_rb_tail;

		int maximum = max(a_b,max(ra_b,max(a_rb,ra_rb)));

		printf("Case #%d: %d\n", testcase, maximum);
    }

    return 0;
}
