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

int main(){

    int t; SCD(t);
    REP(nb, t){
        int d,p,u,v; scanf("%d %d %d %d\n", &d, &p, &u, &v);

		double base = (double)d/(p-1);
		int uModBase = floor(u/base);
		int vModBase; if(abs(v-floor(v/base)*base)<=1e-4){vModBase=floor(v/base)-1;}else{vModBase=floor(v/base);}
		int k = vModBase-uModBase;

		if(k==0 || v-u==0){
			printf("Case #%d: %.10f\n", nb+1, base);
		}else if(k==1){
			int d1 = u; int d2 = d-v;
			if(d1==0){
				if(d2==0){
					printf("Case #%d: %.10f\n", nb+1, .0);
				}else{
					printf("Case #%d: %.10f\n", nb+1, (double)d2/(p-1-1));
				}
			}else if(d2==0){
				printf("Case #%d: %.10f\n", nb+1, (double)d1/(p-1-1));
			}else{
				double m1 = (double)d1/(floor(u/base)+1);
				double m2 = (double)d2/(p-1-1-floor(u/base));
				double b = max(m1,m2);

				printf("Case #%d: %.10f\n", nb+1, b);
			}
		}else{
			int d1 = u; int d2 = d-v;
			if(d1==0){
				if(d2==0){
					printf("Case #%d: %.10f\n", nb+1, .0);
				}else{
					printf("Case #%d: %.10f\n", nb+1, (double)d2/(p-1-1));
				}
			}else if(d2==0){
				printf("Case #%d: %.10f\n", nb+1, (double)d1/(p-1-1));
			}else{
				int n1a = ceil((double)d1/(d1+d2)*(p-1-1));
				int n2a = p-1-1-n1a;
				double ba = min((double)d1/n1a,(double)d2/n2a);

				int n1b = floor((double)d1/(d1+d2)*(p-1-1));
				int n2b = p-1-1-n1b;
				double bb = min((double)d1/n1b,(double)d2/n2b);

				printf("Case #%d: %.10f\n", nb+1, max(ba,bb));
			}
		}
    }

    return 0;
}