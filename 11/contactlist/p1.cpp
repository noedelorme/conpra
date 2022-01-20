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
Trie implementation massively inspired from
SOURCE: https://www.geeksforgeeks.org/trie-insert-and-search/
*/
typedef struct Node{
    vector<Node*> children;
    bool end;
	Node(){
		REP(i,26) children.push_back(NULL);
		end = false;
	}
} Node;

void TrieInsert(Node* root, string key){
    Node* current = root;
	REP(i,key.length()){
        int index = key[i] - 'a';
        if(current->children[index]==NULL) current->children[index] = new Node();
        current = current->children[index];
    }
    current->end = true;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n; SI(n);
		vector<string> names(n);
		REP(i,n){
			cin >> names[i];
			names[i][0] = tolower(names[i][0]);
		}

		vector<Node*> nodes;
		Node *root = new Node();
		REP(i,n){ TrieInsert(root, names[i]); }

		//We count the number of intermediate node that are final
		int count = 0;
		stack<Node*> Q;
		Q.push(root);
		while(!Q.empty()){
			Node* node = Q.top(); Q.pop();
			int nonNullChil = 0;
			for(Node* child : node->children){
				if(child!=NULL){
					nonNullChil++;
					Q.push(child);
				}
			}
			if(nonNullChil>0 && node->end) count++;
		}

		printf("Case #%d: %d\n", testcase, count);
    }

    return 0;
}
