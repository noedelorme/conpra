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

using namespace std;

#define SI(x) scanf("%d",&x)
#define SLLI(x) scanf("%lld",&x)
#define SF(x) scanf("%f",&x)
#define SD(x) scanf("%lf",&x)
#define SC(x) scanf("%c",&x)
#define SS(x) scanf("%s",x)
#define P(x) cout<<"> x:"<<x<<endl
#define FOR(i, s, k, p) for(int i=s; i<k; i+=p)
#define REP(i, n) FOR(i, 0, n, 1)
#define FOREACH(it, l) for(auto it = l.begin(); it != l.end(); it++)
#define INF (int)1e9
#define EPS 1e-9
#define PI acos(-1)

typedef long long int lint;
typedef unsigned long long int ulint;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<vi> vvi;
typedef pair<lint, lint> pll;
typedef vector<lint> vl;
typedef vector<pll> vll;
typedef vector<vl> vvl;

/* UNION FIND INTEGER */
map<int, pair<int, unsigned int>> Sets;
void AddSet(int x){ Sets.insert(make_pair(x, make_pair(x, 1))); }
int Find(int x){
	if(Sets[x].first == x){ return x; }
	else{ return Sets[x].first = Find(Sets[x].first); }
}
void Union(int x, int y) {
	int parentX = Find(x), parentY = Find(y);
	int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
	if (parentX == parentY){ return; }
	else if(rankX < rankY){
		Sets[parentX].first = parentY;
		Sets[parentY].second += Sets[parentX].second;
	}else{
		Sets[parentY].first = parentX;
		Sets[parentX].second += Sets[parentY].second;
	}
}
int Size(int x){ return Sets[Find(x)].second; }
void Reset(){ Sets.clear(); }

int main(){

    int t; SI(t);
    FOR(testcase, 1, t+1, 1){

		int N,K,R,D; SI(N); SI(K); SI(R); SI(D);

		if(K==0 || R==0){
			printf("Case #%d: ok\n", testcase);
		}else{
			REP(i,N){ AddSet(i+1); }

			int firstK; SI(firstK);
			FOR(i,1,K,1){
				int nextK; SI(nextK);
				Union(firstK,nextK);
			}

			int firstR; SI(firstR);
			FOR(i,1,R,1){
				int nextR; SI(nextR);
				Union(firstR,nextR);
			}

			REP(i,D){
				int u,d; SI(u); SI(d);
				if(Find(u)!=Find(firstR)){
					Union(u,d);
				}
			}

			if(Find(firstK)!=Find(firstR)){
				printf("Case #%d: ok\n", testcase);
			}else{
				printf("Case #%d: conflict\n", testcase);
			}

			Reset();
		}

    }

    return 0;
}