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


/*
Trie implementation from
https://www.geeksforgeeks.org/trie-insert-and-search/
*/
struct TrieNode{
    struct TrieNode *children[26];
    bool isEndOfWord;
    bool counted;
    ~TrieNode(){
        delete[] children;
    }
};

struct TrieNode *getNode(void){
    struct TrieNode *pNode =  new TrieNode;
    pNode->isEndOfWord = false;
    pNode->counted = false;
    for (int i = 0; i < 26; i++)pNode->children[i] = NULL;
    return pNode;
}

void insert(struct TrieNode *root, string key, int &count){
    struct TrieNode *pCrawl = root;
    bool flag = false;
    for (int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
            pCrawl->children[index] = getNode();
            flag = true;
        }

        //If during the adding of key we visite a final node that we didn't counter yet
        if(pCrawl->isEndOfWord && !pCrawl->counted){ count++; pCrawl->counted=true; }
        pCrawl = pCrawl->children[index];
    }

    //If a longer name with prefix key as already been added
    if(!flag && !pCrawl->counted){ count++; pCrawl->counted=true; }
    pCrawl->isEndOfWord = true;
}


int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
		vector<string> names(n);
		REP(i,n){
			cin >> names[i];
			names[i][0] = tolower(names[i][0]);
		}

        struct TrieNode *root = getNode();
        int count = 0;
        REP(i,n) insert(root, names[i], count);

		printf("Case #%d: %d\n", testcase, count);
    }

    return 0;
}
