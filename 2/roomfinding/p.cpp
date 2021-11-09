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


bool compare(pair<long long int,long long int> a, pair<long long int,long long int> b){
    if(a.first != b.first){ return a.first < b.first; }
	else{ return a.second <= b.second; }
}

long long int solve(vector<pair<long long int,long long int>> stations, long long int line, long long int a, long long int b){
	while(a != b){
		long long int m = (a+b)/2;
		long long int c = 0;
		for(pair<long long int,long long int> s : stations){
			if(s.first<=m){ c += min(m,s.second)-s.first+1; }
		}
		if(c==line){ return m; }else if(c < line){ a = m+1; }else{ b = m; }
	}
	
	return a;
}

int main(){

    int t; SCD(t);
    REP(nb, t){
        int s,f; scanf("%d %d\n", &s, &f);
		vector<pair<long long int,long long int>> stations(s);
		long long int b = 0;
		REP(i, s){
			long long int u,v; scanf("%lld %lld\n", &u, &v);
			stations[i] = {u,v};
			b = max(b,v);
		}
		sort(stations.begin(), stations.end(), compare);
		long long int a = stations[0].first;

		printf("Case #%d:\n", nb+1);
		REP(i, f){
			long long int line; SCLLD(line);
			printf("%lld\n", solve(stations, line, a, b));
		}
		
    }

    return 0;
}