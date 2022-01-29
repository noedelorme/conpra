//Do not work

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


int main(){

    lint a,c,s,n; SL(a); SL(c); SL(s); SL(n);
    vector<lint> weatherStrategies(n);
    weatherStrategies[0] = s;
    lint twoPow31 = pow(2,31);
    REP(i,n-1){ 
        weatherStrategies[i+1] = (a*weatherStrategies[i]+c)%twoPow31;
    }

    string solution;
    cout<<"done"<<endl;

    int t; SI(t); FOR(testcase, 1, t+1){
        lint umbrellaStrategy; SL(umbrellaStrategy);
        
        int maxHappiness = 0;
        lint bestStrategy = weatherStrategies[0];
        REP(i,n){
            lint happiness = umbrellaStrategy ^ weatherStrategies[i];
            if(happiness>maxHappiness){
                maxHappiness = happiness;
                bestStrategy = weatherStrategies[i];
            }
        }

        solution += "Case #" + to_string(testcase) + ": " + to_string(bestStrategy) + "\n";
		//printf("Case #%d: %lld\n", testcase, bestStrategy);
    }

    //cout<<solution;

    return 0;
}