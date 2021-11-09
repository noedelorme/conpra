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

#define SCD(t) scanf("%d",&t)
#define SCLD(t) scanf("%ld",&t)
#define SCLLD(t) scanf("%lld",&t)
#define SCC(t) scanf("%c",&t)
#define SCS(t) scanf("%s",t)
#define SCF(t) scanf("%f",&t)
#define SCLF(t) scanf("%lf",&t)
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

int main(){

    int t; SCD(t);
    int64 m;
    int64 c = 299792458;

    REP(i, t){
        SCLLD(m);
        int64 E = m*c*c;
        printf("Case #%d: %lld\n", i+1, E);
    }

    return 0;
}