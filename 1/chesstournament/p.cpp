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

typedef struct Team{
    int p1, p2, p3, p4, p5;
} Team;

bool compare(vector<int> a, vector<int> b){
    if(a[4]==b[4]){
        if(a[3]==b[3]){
            if(a[2]==b[2]){
                if(a[1]==b[1]){
                    if(a[0]==b[0]){
                        return true;
                    }else{
                        return a[0]>b[0];
                    }
                }else{
                    return a[1]>b[1];
                }
            }else{
                return a[2]>b[2];
            }
        }else{
            return a[3]>b[3];
        }
    }else{
        return a[4]>b[4];
    }
}

int main(){

    int t; SCD(t);
    int n;

    REP(i, t){
        SCD(n); printf("Case #%d:\n", i+1);
        vector<vector<int>> teams(n, vector<int>(5));
        REP(j, n){
            scanf("%d %d %d %d %d\n", &teams[j][0], &teams[j][1], &teams[j][2], &teams[j][3], &teams[j][4]);
            sort(teams[j].begin(), teams[j].end());
        }

        sort(teams.begin(), teams.end(), compare);
        REP(j, n){ printf("%d %d %d %d %d\n", teams[j][4], teams[j][3], teams[j][2], teams[j][1], teams[j][0]); }
        
    }

    return 0;
}