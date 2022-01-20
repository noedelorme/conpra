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
#define FOR(i, s, k) for(int i=s; i<k; i++)
#define REP(i, n) FOR(i, 0, n)
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


/*****************************************************************************
Trie implementation from https://www.geeksforgeeks.org/trie-insert-and-search/
*****************************************************************************/
const int ALPHABET_SIZE = 26;
 
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 
// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl->isEndOfWord);
}


bool firstHaveStrategyToWin(TrieNode* pos){
    if(pos->isEndOfWord) return true;

    REP(i,26){
        TrieNode* nextPos = pos->children[i];
        if(nextPos != NULL){
            if(!firstHaveStrategyToWin(nextPos)){
                return true;
            }
        }
    }
    return false;
}

bool firstHaveStrategyToLoose(TrieNode* pos){
    if(pos->isEndOfWord) return false;

    REP(i,26){
        TrieNode* nextPos = pos->children[i];
        if(nextPos != NULL){
            if(!firstHaveStrategyToLoose(nextPos)){
                return true;
            }
        }
    }
    return false;
}



int main(){

    int t; SI(t); FOR(testcase, 1, t+1){
		int n,w; SII(n,w);
        vector<string> words(w);
        REP(i,w) cin>>words[i];

        TrieNode* root = getNode();
        REP(i,w) insert(root, words[i]);

        bool leaHaveWinStrategy = firstHaveStrategyToWin(root);
        bool leaHaveLooseStrategy = firstHaveStrategyToLoose(root);

        //Scenario 1 (Lea begin, winner begin)
        bool scenario1;
        if(leaHaveWinStrategy){
            scenario1 = true;
        }else{
            if(leaHaveLooseStrategy){
                scenario1 = n%2==0;
            }else{
                scenario1 = false;
            }
        }

        //Scenario 2 (Lea begin, looser begin)
        bool scenario2;
        if(!leaHaveWinStrategy){
            scenario2 = false;
        }else{
            if(!leaHaveLooseStrategy){
                scenario2 = !(n%2==0);
            }else{
                scenario2 = true;
            }
        }

        //Scenario 3 and 4 are deduced from the symetry of the game
        bool scenario3 = !scenario1;
        bool scenario4 = !scenario2;

		printf("Case #%d:\n", testcase);
        if(scenario1) printf("victory\n");
        else printf("defeat\n");
        if(scenario2) printf("victory\n");
        else printf("defeat\n");
        if(scenario3) printf("victory\n");
        else printf("defeat\n");
        if(scenario4) printf("victory\n");
        else printf("defeat\n");
    }

    return 0;
}
