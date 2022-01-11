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


/* Compute inverse modulo m of a */
//Source: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
lint modularInverse(lint a, lint m){
    lint m0 = m, t, q;
    lint x0 = 0, x1 = 1;

    if(m==1){ return 0; }

    //Extended Euclid Algorithm
    while(a>1){
        q = a/m;
        t = m;
        m = a%m;
        a = t;
        t = x0;
        x0 = x1-q*x0;
        x1 = t;
    }

    if(x1<0){ x1 += m0; } //Make x1 positive

    return x1;
}


/*
Chinese Remainder Theorem
Returns the smallest x s.t.
x = a[i] (mod r[i]) for all i between 0 and n-1
Assumption: a[i]s are pairwise coprime
*/
//Source: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
lint chineseRemainder(vl a, vl r){
    int n = a.size();
    ulint prod=1; REP(i,n){ prod*=a[i]; }
        
    lint result = 0;
    REP(i,n){
        lint pp = prod/a[i];
        result += r[i]*modularInverse(pp, a[i])*pp;
    }

    return result%prod;
}


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
        lint k; SL(k);
        ulint prod = 1;
        vl p(n); vl r(n);

        unordered_map<lint, lint> checkPrimes;
        bool flag = false;

        REP(i,n){
            SL(p[i]); SL(r[i]);
            prod*=p[i];
            if(checkPrimes.find(p[i])!=checkPrimes.end()){
                if(checkPrimes[p[i]]!=r[i]){
                    flag = true;
                }
            }else{
                checkPrimes[p[i]] = r[i];
            }
        }

        if(flag){ printf("Case #%d: impossible\n", testcase); continue; }

        lint x = chineseRemainder(p,r);

        if(x>k){
            printf("Case #%d: impossible\n", testcase);
        }else{
            x += ((k-x)/prod)*prod; //from minimal to maximal lower than k
            printf("Case #%d: %lld\n", testcase, x);
        }

        
    }

    return 0;
}