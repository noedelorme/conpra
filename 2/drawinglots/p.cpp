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

double payoff(vector<int> prices, double p, int n, int b){
	double sum=0;
	REP(i, n){ sum += prices[i]*pow(p, i+1); }
	return sum-b;
}

int main(){

    int t; SCD(t);
    REP(nb, t){
        int n,b; SCD(n); SCD(b);
		int sumprices = 0;
		vector<int> prices(n); REP(j, n){ SCD(prices[j]); sumprices+=prices[j]; }

		if(sumprices>=b){
			double p=0.5;
			double a=0;
			double c=1;
			while(abs(payoff(prices, p, n, b))>1e-10){
				p = (c+a)/2;
				if(payoff(prices, p, n, b)>0){ c = p; }else{ a = p; }
			}
			printf("Case #%d: %.10f\n", nb+1, p);
		}else{
			double p=1;
			printf("Case #%d: %.10f\n", nb+1, p);
		}
		
    }

    return 0;
}