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

/* UNION FIND INTEGER MODIFIED */
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
    REP(nb, t){
        int n,m; scanf("%d %d\n", &n, &m);
		vector<int> enemies[n];
		REP(i, n){ AddSet(i+1); }

		vector<pair<int, int>> Fs;
		vector<pair<int, int>> As;

		REP(i, m){
			char c; int x,y; scanf("%c %d %d\n", &c, &x, &y);
			if(c=='F'){ 
				Fs.push_back({x,y});
			}
			else{
				As.push_back({x,y});
			}
		}

		REP(i, Fs.size()){
			Union(Fs[i].first,Fs[i].second); 
		}
		REP(i, As.size()){
			enemies[Find(As[i].first)-1].push_back(Find(As[i].second));
			enemies[Find(As[i].second)-1].push_back(Find(As[i].first));
		}

		REP(i, n){
			if(enemies[i].size()>1){
				int fe = enemies[i][0];
				for(int j=1; j<enemies[i].size(); j++){
					Union(fe, enemies[i][j]);
				}
			}
		}


		if((double)Size(1)>n/2.0){
			printf("Case #%d: yes\n", nb+1);
		}else{
			printf("Case #%d: no\n", nb+1);
		}
		Reset();
    }

    return 0;
}