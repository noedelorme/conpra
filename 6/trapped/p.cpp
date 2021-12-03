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
typedef vector<vector<bool>> vvb;
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
typedef vector<char> vc;
typedef vector<vector<char>> vvc;


bool isPossibleStep(vvb &walkable, vvb &visited, pii p){
	int i = p.first;
	int j = p.second;
	int h = walkable.size();
	int w = walkable[0].size();
	return i>=0 && i<h && j>=0 && j<w && walkable[i][j] && !visited[i][j];
}

bool paths(vvc &cave, vvb &walkable, vvb &visited, pii pos, int nTools, int tools){
	if(tools==nTools){ return true; }

	pii up = make_pair(pos.first-1,pos.second);
	if(isPossibleStep(walkable, visited, up)){
		visited[up.first][up.second] = true;
		int currentTools = tools + (cave[up.first][up.second]=='T' ? 1 : 0);
		if(paths(cave, walkable, visited, up, nTools, currentTools)){ return true; }
		visited[up.first][up.second] = false;
	}

	pii right = make_pair(pos.first,pos.second+1);
	if(isPossibleStep(walkable, visited, right)){
		visited[right.first][right.second] = true;
		int currentTools = tools + (cave[right.first][right.second]=='T' ? 1 : 0);
		if(paths(cave, walkable, visited, right, nTools, currentTools)){ return true; }
		visited[right.first][right.second] = false;
	}

	pii down = make_pair(pos.first+1,pos.second);
	if(isPossibleStep(walkable, visited, down)){
		visited[down.first][down.second] = true;
		int currentTools = tools + (cave[down.first][down.second]=='T' ? 1 : 0);
		if(paths(cave, walkable, visited, down, nTools, currentTools)){ return true; }
		visited[down.first][down.second] = false;
	}

	pii left = make_pair(pos.first,pos.second-1);
	if(isPossibleStep(walkable, visited, left)){
		visited[left.first][left.second] = true;
		int currentTools = tools + (cave[left.first][left.second]=='T' ? 1 : 0);
		if(paths(cave, walkable, visited, left, nTools, currentTools)){ return true; }
		visited[left.first][left.second] = false;
	}

	return false;

}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

		int w,h; scanf("%d %d\n", &w, &h);
		vvc cave(h, vc(w));
		vvb walkable(h, vb(w, false));
		vvb visited(h, vb(w, false));
		pii lea = make_pair(0,0);
		int nTools = 0;
		REP(i,h){ 
			REP(j,w){ 
				SC(cave[i][j]);
				if(cave[i][j]!='#'){ walkable[i][j]=true; }
				if(cave[i][j]=='L'){ lea = make_pair(i,j); visited[i][j]=true; }
				if(cave[i][j]=='T'){ nTools++; }
			}
			scanf("\n");
		}

		if(paths(cave, walkable, visited, lea, nTools, 0)){
			printf("Case #%d: yes\n", testcase);
		}else{
			printf("Case #%d: no\n", testcase);
		}

    }

    return 0;
}
