#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <bitset>

#define SCD(t) scanf("%d\n",&t)
#define SCLD(t) scanf("%ld\n",&t)
#define SCLLD(t) scanf("%lld\n",&t)
#define SCC(t) scanf("%c\n",&t)
#define SCS(t) scanf("%s\n",t)
#define SCF(t) scanf("%f\n",&t)
#define SCLF(t) scanf("%lf\n",&t)
#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define FOREACH(it, l) for(auto it = l.begin(); it != l.end(); it++)
#define INF (int)1e9
#define EPS 1e-9
#define PI acos(-1)

typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

using namespace std;

/* UNION FIND INTEGER */
map<int, pair<int, unsigned int>> Sets;
void AddSet(int x){
	Sets.insert(make_pair(x, make_pair(x, 1)));
}
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
int Size(int x){
    return Sets[Find(x)].second;
}
void Reset(){ Sets.clear(); }



int main(){

    int t; SCD(t);
    REP(i, t){
        int a, b, c; scanf("%d %d %d\n", &a, &b, &c);
		REP(j, a){ AddSet(j+1); }
		int money[a-1]; REP(j, a-1){ SCD(money[j]); }
		bool maried[a-1]; fill_n(maried, a-1, false);
		REP(j, b){
			int d,e; scanf("%d %d\n", &d, &e);
			Union(d,e);
		}
		REP(j, c){
			int d,e; scanf("%d %d\n", &d, &e);
			Union(d,e);
			maried[d-1] = true; maried[e-1] = true;
		}

		int finda = Find(a);
		int m = -1;
		REP(j, a-1){
			if(Find(j+1)!=finda && !maried[j]){
				if(money[j]>m){ m = money[j]; }
			}
		}

		if(m>=0){ printf("Case #%d: %d\n", i+1, m); }
		else{ printf("Case #%d: impossible\n", i+1); }

		Reset();
    }

    return 0;
}