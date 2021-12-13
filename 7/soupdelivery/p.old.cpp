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

pair<bool,int> localSearch(vvi &deli, vi &rents, vb &used, vi &userLoc, vi &nUsers, int cost){
    int N = deli.size(); int M = userLoc.size();

    int newCost=cost;

    //Search the best location to add if there is one
    int bestLoc = 0;
    int maxGain = -1;
    REP(i, N){
        if(!used[i]){
            int gain = -rents[i];
            
            REP(j,M){
                if(deli[i][j]<deli[userLoc[j]-1][j]){
                    gain += deli[userLoc[j]-1][j]-deli[i][j];
                    if(nUsers[userLoc[j]-1]==1){
                        gain += rents[userLoc[j]-1];
                    }
                }
            }
            if(gain>maxGain){
                maxGain=gain;
                bestLoc=i+1;
            }
        }
    }

    //if we found a location that improve the solution
    if(bestLoc!=0 && maxGain>0){
        used[bestLoc-1] = true;
        newCost += rents[bestLoc-1];
        REP(i,M){ //update userLoc, used, nUsers and newCost
            if(deli[bestLoc-1][i]<deli[userLoc[i]-1][i]){
                int previousLoc = userLoc[i];
                userLoc[i] = bestLoc;
                newCost -= deli[previousLoc-1][i];
                newCost += deli[bestLoc-1][i];
                
                if(nUsers[previousLoc-1]==1){
                    nUsers[previousLoc-1]=0;
                    used[previousLoc-1]=false;
                    newCost -= rents[previousLoc-1];
                }else{
                    nUsers[previousLoc-1]--;
                }
            }
        }
        return make_pair(true, newCost);
        
    }else{
        return make_pair(false, -1); //will end the while loop in main
    }

    
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int N,M; SII(N,M);
        vi rents(N); //rents[i] monthly cost of the rent of location i
        REP(i,N){ SI(rents[i]); }
        vvi deli(N, vi(M)); //deli[i][j] delivery cost from location i to userLoc[i] j
        REP(i,N){ REP(j,M){ SI(deli[i][j]); } }

        //Compute an initial solution
        //(Starting from only one location that deliver every users)
        vb used(N,false); //used[i] true if location i used
        vi userLoc(M); //userLoc[i] location delivering userLoc[i] i
        vi nUsers(N,0); //nUsers[i] nb of users that location i deliver
        int initCost = 0;

        int bestLoc = 1;
        int minSum = INF;
        REP(i,N){
            int sum=0;
            REP(j,M){ sum+=deli[i][j]; }
            if(sum<minSum){ minSum=sum; bestLoc=i+1; }
        }

        initCost = minSum + rents[bestLoc-1];
        used[bestLoc-1] = true;
        nUsers[bestLoc-1] = M;
        REP(i,M){ userLoc[i] = bestLoc; }

        //improving solution until it's not possible
        int previousCost = initCost;
        int newCost = initCost;
        int cost = initCost;
        bool flag = true;

        do{
            previousCost = newCost;
            cost = newCost;
            pair<bool,int> result = localSearch(deli, rents, used, userLoc, nUsers, cost);
            flag = result.first;
            newCost = result.second;
        }while(flag);

        printf("Case #%d: %d\n", testcase, previousCost);

        vli sol(M);
        REP(i,M){ sol[userLoc[i]-1].push_back(i+1); }
		
		REP(i,N){
            if(sol[i].size()){
                printf("%d ", i+1);
                for(int u : sol[i]){ printf("%d ", u); }
                printf("\n");
            }
        }
		
    }

    return 0;
}
