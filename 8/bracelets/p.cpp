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

string rotateString(string str){
	return str[str.size()-1]+str.substr(0,str.size()-1);
}

//longest common subsequence recursive
int lcs(vvi &dp, string a, string b, int m, int n){
	if(m==0 || n==0){
		return 0;
	}else if(dp[m][n]!=-1){ 
		return dp[m][n];
	}else if(a[m-1] == b[n-1]){
		dp[m][n] = lcs(dp,a,b,m-1,n-1)+1;
        return dp[m][n];
	}else{
		dp[m][n] = max(lcs(dp,a,b,m,n-1), lcs(dp,a,b,m-1,n));
        return dp[m][n];
	}
}

//longest common subsequence non recursive
int lcs2(string a, string b){
	int m=a.size();
	int n=b.size();
	vvi memo(m+1,vi(n+1));

    REP(i,m+1){
        REP(j,n+1){
            if(i==0 || j==0){
				memo[i][j]=0;
			}else if(a[i-1] == b[j-1]){
				memo[i][j]=memo[i-1][j-1]+1;
			}else{
				memo[i][j]=max(memo[i-1][j],memo[i][j-1]);
			}
        }
    }
    return memo[m][n];
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		
		string a,b; cin>>a>>b;
		string ra = reverseString(a);
		string rb = reverseString(b);
		int m = a.size();
    	int n = b.size();

		int maximum = 0;

		//a is rotating and b don't change
		REP(i,m){
			vvi dp(m+1, vi(n+1, -1)); dp[0][0]=0;
			int l = lcs2(a,b);
			maximum = max(maximum,l);
			a = rotateString(a);
		}

		//a is reversed and rotating and b don't change
		REP(i,m){
			vvi dp(m+1, vi(n+1, -1)); dp[0][0]=0;
			int l = lcs2(ra,b);
			maximum = max(maximum,l);
			ra = rotateString(ra);
		}

		printf("Case #%d: %d\n", testcase, maximum);
    }

    return 0;
}
