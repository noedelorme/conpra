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

typedef struct Board{
    vvb cells; // has queen
    vb rows; //available rows
    vb cols; //available cols
    lii queens;

    Board(int n){
        cells = vvb(n, vb(n, false));
        rows = vb(n, true);
        cols = vb(n, true);
        queens = lii();
    }
} Board;

void printBoard(Board &board){
    int n=board.cells.size();
    REP(i,n){
        REP(j,n){
            if(board.cells[i][j]){ printf("x"); }
            else{ printf("."); }
        }
        printf("\n");
    }
}

bool isValidPosition(Board &board, int x, int y){
    int n = board.cells.size();

    //if(!board.rows[x]){ return false; }
    //if(!board.cols[y]){ return false; }

    // N
    FOR(i,0,x,1){ if(board.cells[i][y]){ return false; } }
    // NE
    FOR(i,1,min(x+1,n-y),1){ if(board.cells[x-i][y+i]){ return false; } }
    // E
    FOR(i,y+1,n,1){ if(board.cells[x][i]){ return false; } }
    // SE
    FOR(i,1,min(n-x,n-y),1){ if(board.cells[x+i][y+i]){ return false; } }
    // s
    FOR(i,x+1,n,1){ if(board.cells[i][y]){ return false; } }
    // SW
    FOR(i,1,min(n-x,y+1),1){ if(board.cells[x+i][y-i]){ return false; } }
    // w
    FOR(i,0,y,1){ if(board.cells[x][i]){ return false; } }
    // NW
    FOR(i,1,min(x+1,y+1),1){ if(board.cells[x-i][y-i]){ return false; } }

    return true;
}

bool isValidPosition2(Board &board, int x, int y){
    int n = board.cells.size();

    if(!board.rows[x]){ return false; }
    if(!board.cols[y]){ return false; }

    // NE
    FOR(i,1,min(x+1,n-y),1){ if(board.cells[x-i][y+i]){ return false; } }
    // SE
    FOR(i,1,min(n-x,n-y),1){ if(board.cells[x+i][y+i]){ return false; } }
    // SW
    FOR(i,1,min(n-x,y+1),1){ if(board.cells[x+i][y-i]){ return false; } }
    // NW
    FOR(i,1,min(x+1,y+1),1){ if(board.cells[x-i][y-i]){ return false; } }

    return true;
}

bool isValidPosition3(Board &board, int x, int y){
    int n = board.cells.size();
    //cout<<"======"<<x<<" "<<y<<endl;
    for(pii queen : board.queens){
        int qx = queen.first;
        int qy= queen.second;
        //cout<<"***"<<qx<<" "<<qy<<endl;
        if(x==qx && y!=qy){ return false; }
        if(y==qy && x!=qx){ return false; }
        if(abs(x-qx)==abs(y-qy) && abs(x-qx)>0){ return false; }
    }
    if(board.cells[x][y]){ return true; }

    return true;
}

bool isValidBoard(Board &board){
    int n = board.cells.size();
    REP(i,n){
        int queensInRow = 0;
        REP(j,n){
            if(board.cells[i][j]){
                queensInRow++;
                if(!isValidPosition3(board, i, j)){ return false; }
            }
        }
        if(queensInRow>1){ return false; }
    }
    return true;
}

bool solve(Board &board, int queens){
    int n = board.cells.size();
    if(queens==n){ return true; }

    REP(i,n){
        if(board.rows[i]){
            REP(j,n){
                if(board.cols[j] && !board.cells[i][j] && isValidPosition3(board, i, j)){
                    board.cells[i][j] = true;
                    board.rows[i] = false;
                    board.cols[j] = false;
                    board.queens.push_back(make_pair(i,j));
                    if(solve(board, queens+1)){ return true; }
                    board.queens.pop_back();
                    board.cells[i][j] = false;
                    board.rows[i] = true;
                    board.cols[j] = true;
                }
            }
        }
    }

    return false;
}

bool solve2(Board &board, int queens){
    int n = board.cells.size();
    if(queens==n){ return true; }
    Board nextBoard(n);
    

    return false;
}

int main(){

    int t; SI(t); FOR(testcase, 1, t+1, 1){

        int n; SI(n); scanf("\n");
        Board board(n);
        int initQueens = 0;

        REP(i,n){
            REP(j,n){
                char c; SC(c);
                if(c=='x'){
                    board.cells[i][j]=true;
                    board.rows[i]=false;
                    board.cols[j]=false;
                    board.queens.push_back(make_pair(i,j));
                    initQueens++;
                }else{
                    board.cells[i][j]=false;
                }
            }
            scanf("\n");
        }

        /*cout<<isValidPosition3(board,0,2)<<endl;//0
        cout<<isValidPosition3(board,1,3)<<endl;//0
        cout<<isValidPosition3(board,2,3)<<endl;//0
        cout<<isValidPosition3(board,3,3)<<endl;//0
        cout<<isValidPosition3(board,3,2)<<endl;//0
        cout<<isValidPosition3(board,3,1)<<endl;//0
        cout<<isValidPosition3(board,2,1)<<endl;//0
        cout<<isValidPosition3(board,1,1)<<endl;//0
        cout<<isValidPosition3(board,0,0)<<endl;//0
        cout<<isValidPosition3(board,3,1)<<endl;//0
        cout<<isValidPosition3(board,0,1)<<endl;//1
        cout<<isValidPosition3(board,0,3)<<endl;//1
        cout<<isValidPosition3(board,1,0)<<endl;//1
        cout<<isValidPosition3(board,3,0)<<endl;//1
        cout<<isValidPosition3(board,2,2)<<endl;//1*/

        
        /*printf("Case #%d:\n", testcase); //printBoard(board);
        REP(i,n){
            REP(j,n){
                bool a = isValidPosition(board,i,j);
                bool b = isValidPosition3(board,i,j);

                if(a!=b){
                    cout<<i<<" errere "<<j<<' '<<a<<' '<<b<<endl;
                    //cout<<isValidPosition(board,i,j)<<" "<< isValidPosition3(board,i,j)<<endl;
                }
            }
        }*/

        bool flag = isValidBoard(board) && solve(board, initQueens);
        if(flag){
            printf("Case #%d:\n", testcase);
            printBoard(board);
        }else{
            printf("Case #%d:\n", testcase);
            printf("impossible\n");
        }
        
        

    }

    return 0;
}
