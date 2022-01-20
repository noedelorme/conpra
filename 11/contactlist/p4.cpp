// DO NOT WORK


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

/* Trie implementation using unordered_map */
int myhash(int node, int letter){ return node*100 + letter; }

void insert(unordered_map<int,int> &trie, unordered_map<int,bool> &isLeaf, unordered_map<int,bool> &intermediateFinalNode, int &lastNodeId, string str){
    int current = 0;
    int flag=false;
    REP(i,str.size()){
        int currentChar = (char)str[i] - 'a';
        //if(trie.find(myhash(current, currentChar)) == trie.end())
        if(!trie[myhash(current, currentChar)]){
            lastNodeId++;
            trie[myhash(current, currentChar)] = lastNodeId;
            isLeaf[lastNodeId] = false;
            flag=true;
        }

        if(isLeaf[current]) intermediateFinalNode[current]=true;

        current = trie[myhash(current, currentChar)];
    }

    if(!flag) intermediateFinalNode[current]=true;

    isLeaf[current] = true;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
		vector<string> names(n);
		REP(i,n){
			cin >> names[i];
			names[i][0] = tolower(names[i][0]);
		}

        unordered_map<int,int> trie; //(source,char) -> target
        unordered_map<int,bool> isLeaf;
        unordered_map<int,bool> intermediateFinalNode;
        int lastNodeId = 0;
		REP(i,n) insert(trie, isLeaf, intermediateFinalNode, lastNodeId, names[i]);

        printf("Case #%d: %d\n", testcase, (int)intermediateFinalNode.size());
    }

    return 0;
}
