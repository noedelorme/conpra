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


double base(int d, int n){
	if(n==0){
		return 1e6+1;
	}else{
		return (double)d/(double)n;
	}	
}

int main(){

    int t; SCD(t);
    REP(nb, t){
        int d,p,u,v; scanf("%d %d %d %d\n", &d, &p, &u, &v);

		p-=2; int uv=v-u; double d1=u; double d2=d-v;
		double b = base(d,p+2-1);
		if(p==0){
			printf("Case #%d: %.10f\n", nb+1, (double)d);
		}
		else if(uv<=b){
			if(floor(u/b) == floor(v/b) || abs(v/b-floor(v/b+0.5))<1e-7){
				printf("Case #%d: %.10f\n", nb+1, b);
			}else{
				double m1 = base(u,floor(u/b)+1);
				double m2 = base(d-v,p-floor(u/b));
				double m=m1; if(m2>m1){m=m2;}
				printf("Case #%d: %.10f\n", nb+1, m);
				
			}
		}else{
			int n1a = ceil(d1/(d1+d2)*(p));
			int n2a = p-n1a;
			double m1a = base(d1,n1a);
			double m2a = base(d2,n2a);
			double ma = m1a; if(m2a<m1a){ma=m2a;}
			//cout<<n1a<<" "<<n2a<<" "<<m1a<<" "<<m2a<<" "<<ma<<endl;

			int n1b = floor(d1/(d1+d2)*(p ));
			int n2b = p+1-n1b;
			double m1b = base(d1,n1b);
			double m2b = base(d2,n2b);
			double mb = m1b; if(m2b<m1b){mb=m2b;}
			//cout<<n1b<<" "<<n2b<<" "<<m1b<<" "<<m2b<<" "<<mb<<endl;

			double m = abs(ma); if(mb>ma){m=abs(mb);}

			printf("Case #%d: %.10f\n", nb+1, m);
		}

    }

    return 0;
}