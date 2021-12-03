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
typedef vector<vector<bool>> vvb;
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
typedef vector<char> vc;
typedef vector<vector<char>> vvc;

typedef struct Dep{ int c,p,d,q; } Dep;

bool statisfyDeps(vi &chapters, vi &person, vector<Dep> &deps){
    int n=chapters.size();
    int m=deps.size();
    int k=person.size();

    for(Dep d : deps){
        int cChaps=0; int dChaps=0;
        REP(i,k){
            int currentPerson=person[i];
            if(d.c==currentPerson){ cChaps++; }
            if(d.d==currentPerson){ dChaps++; }
            if(d.p==cChaps){ break; }
        }
        if(d.p==cChaps && d.q<=dChaps){ return false; }
    }

    return true;
}

int orderings(vi &chapters, vi &person, vector<Dep> &deps, int c){
    int n=chapters.size();
    int k=person.size();
    int sum = 0;

    if(c==k){
        if(statisfyDeps(chapters, person, deps)){ return 1; }
        else{ return 0; }
    }

    REP(i,n){
        if(c>0 && i+1==person[c-1]){ continue; }
        else if(chapters[i]==0){ continue; }
        else{
            chapters[i]--;
            person[c]=i+1;
            sum += orderings(chapters, person, deps, c+1);
            chapters[i]++;
        }
    }

    return sum;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

        int n,m; SII(n,m);
        vi chapters(n); //chapters[i] is amount of chapters centered on i
        int k=0; //number of chapters
        REP(i,n){
            SI(chapters[i]);
            k+=chapters[i];
        }
        vector<Dep> deps(m);
        REP(i,m){
            SIIII(deps[i].c,deps[i].p,deps[i].d,deps[i].q);
        }
        vi person(k); //character[i] is character of chapter i


        int sum = orderings(chapters, person, deps, 0);
        printf("Case #%d: %d\n", testcase, sum);

    }

    return 0;
}
