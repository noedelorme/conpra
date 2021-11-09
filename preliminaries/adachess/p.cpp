#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

void printP(vector<vector<int>> p){
    cout<<"**********"<<endl;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            cout<<p[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"**********"<<endl;
}

set<pair<int,int>> posesKing(pair<int,int> pos){
    int x = pos.first; int y = pos.second;
    set<pair<int,int>> poses;
    if(y+1<8){ poses.insert({x,y+1}); }
    if(y-1>=0){ poses.insert({x,y-1}); }
    if(x+1<8){
        poses.insert({x+1,y});
        if(y+1<8){ poses.insert({x+1,y+1}); }
        if(y-1>=0){ poses.insert({x+1,y-1}); }
    }
    if(x-1>=0){
        poses.insert({x-1,y});
        if(y+1<8){ poses.insert({x-1,y+1}); }
        if(y-1>=0){ poses.insert({x-1,y-1}); }
    }

    return poses;
}

set<pair<int,int>> posesKnight(pair<int,int> pos){
    int x = pos.first; int y = pos.second;
    set<pair<int,int>> poses;

    if(x+2<8 and y+1<8){ poses.insert({x+2,y+1}); }
    if(x+1<8 and y+2<8){ poses.insert({x+1,y+2}); }
    if(x-1>=0 and y+2<8){ poses.insert({x-1,y+2}); }
    if(x-2>=0 and y+1<8){ poses.insert({x-2,y+1}); }
    if(x-2>=0 and y-1>=0){ poses.insert({x-2,y-1}); }
    if(x-1>=0 and y-2>=0){ poses.insert({x-1,y-2}); }
    if(x+1<8 and y-2>=0){ poses.insert({x+1,y-2}); }
    if(x+2<8 and y-1>=0){ poses.insert({x+2,y-1}); }

    return poses;
}

set<pair<int,int>> posesQueen(pair<int,int> pos){
    int x = pos.first; int y = pos.second;
    set<pair<int,int>> poses;
    
    int cX, cY;
    cX=x; cY=y;
    while(cX+1<8){ poses.insert({cX+1,y}); cX++; }
    cX=x; cY=y;
    while(cX-1>=0){ poses.insert({cX-1,y}); cX--; }
    cX=x; cY=y;
    while(cY+1<8){ poses.insert({x,cY+1}); cY++;}
    cX=x; cY=y;
    while(cY-1>=0){ poses.insert({x,cY-1}); cY--;}
    cX=x; cY=y;
    while(cX+1<8 and cY+1<8){ poses.insert({cX+1,cY+1}); cX++; cY++; }
    cX=x; cY=y;
    while(cX+1<8 and cY-1>=0){ poses.insert({cX+1,cY-1}); cX++; cY--; }
    cX=x; cY=y;
    while(cX-1>=0 and cY+1<8){ poses.insert({cX-1,cY+1}); cX--; cY++; }
    cX=x; cY=y;
    while(cX-1>=0 and cY-1>=0){ poses.insert({cX-1,cY-1}); cX--; cY--; }

    return poses;
}

set<pair<int,int>> posesTower(pair<int,int> pos){
    int x = pos.first; int y = pos.second;
    set<pair<int,int>> poses;

    int cX, cY;
    cX=x; cY=y;
    while(cX+1<8){ poses.insert({cX+1,y}); cX++; }
    cX=x; cY=y;
    while(cX-1>=0){ poses.insert({cX-1,y}); cX--; }
    cX=x; cY=y;
    while(cY+1<8){ poses.insert({x,cY+1}); cY++;}
    cX=x; cY=y;
    while(cY-1>=0){ poses.insert({x,cY-1}); cY--;}

    return poses;
}

set<pair<int,int>> posesBishop(pair<int,int> pos){
    int x = pos.first; int y = pos.second;
    set<pair<int,int>> poses;
    
    int cX,cY;
    cX=x; cY=y;
    while(cX+1<8 and cY+1<8){ poses.insert({cX+1,cY+1}); cX++; cY++; }
    cX=x; cY=y;
    while(cX+1<8 and cY-1>=0){ poses.insert({cX+1,cY-1}); cX++; cY--; }
    cX=x; cY=y;
    while(cX-1>=0 and cY+1<8){ poses.insert({cX-1,cY+1}); cX--; cY++; }
    cX=x; cY=y;
    while(cX-1>=0 and cY-1>=0){ poses.insert({cX-1,cY-1}); cX--; cY--; }

    return poses;
}

void fillP(vector<vector<int>> &p, int f, int x, int y){
    list<pair<int,int>> poses;
    poses.push_back({x,y});
    while(!poses.empty()){
        pair<int,int> currentPos = poses.front(); poses.pop_front();
        set<pair<int,int>> newPoses;
        if(f == 0){ newPoses = posesKing(currentPos); }
        else if(f == 1){ newPoses = posesKnight(currentPos); }
        else if(f == 2){ newPoses = posesQueen(currentPos); }
        else if(f == 3){ newPoses = posesTower(currentPos); }
        else{ newPoses = posesBishop(currentPos); }
        
        for(auto pos : newPoses){
            if(p[pos.first][pos.second] == 9){
                p[pos.first][pos.second] = p[currentPos.first][currentPos.second]+1;
                poses.push_back(pos);
            }
        }
    }
}

vector<vector<int>> kingPlat(int x, int y){
    vector<vector<int>> p(8, vector<int>(8, 7));
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            p[i][j] = max(abs(x-i),abs(y-j));
        }
    }
    p[x][y] = 0;
    return p;
}

vector<vector<int>> towerPlat(int x, int y){
    vector<vector<int>> p(8, vector<int>(8, 2));
    for(int i=0; i<8; i++){
        p[x][i] = p[i][y] = 1;
    }
    p[x][y] = 0;
    return p;
}

vector<vector<int>> bishopPlat(int x, int y){
    vector<vector<int>> p(8, vector<int>(8, 9));
    for(int i=0; i<8; i++){
        int mod = (x+y)%2;
        for(int j=(x+y+i)%2; j<8; j+=2){
            p[i][j] = 2;
        }
    }
    int cX,cY;
    cX=x; cY=y;
    while(cX+1<8 and cY+1<8){ p[cX+1][cY+1]=1; cX++; cY++; }
    cX=x; cY=y;
    while(cX+1<8 and cY-1>=0){ p[cX+1][cY-1]=1; cX++; cY--; }
    cX=x; cY=y;
    while(cX-1>=0 and cY+1<8){ p[cX-1][cY+1]=1; cX--; cY++; }
    cX=x; cY=y;
    while(cX-1>=0 and cY-1>=0){ p[cX-1][cY-1]=1; cX--; cY--; }
    p[x][y] = 0;
    return p;
}

vector<vector<int>> queenPlat(int x, int y){
    vector<vector<int>> p(8, vector<int>(8, 2));
    int cX,cY;
    cX=x; cY=y;
    while(cX+1<8 and cY+1<8){ p[cX+1][cY+1]=1; cX++; cY++; }
    cX=x; cY=y;
    while(cX+1<8 and cY-1>=0){ p[cX+1][cY-1]=1; cX++; cY--; }
    cX=x; cY=y;
    while(cX-1>=0 and cY+1<8){ p[cX-1][cY+1]=1; cX--; cY++; }
    cX=x; cY=y;
    while(cX-1>=0 and cY-1>=0){ p[cX-1][cY-1]=1; cX--; cY--; }
    cX=x; cY=y;
    while(cX+1<8){ p[cX+1][y]=1; cX++; }
    cX=x; cY=y;
    while(cX-1>=0){ p[cX-1][y]=1; cX--; }
    cX=x; cY=y;
    while(cY+1<8){ p[x][cY+1]=1; cY++;}
    cX=x; cY=y;
    while(cY-1>=0){ p[x][cY-1]=1; cY--;}
    p[x][y] = 0;
    return p;
}



int main(){
    int T,f,x,y,F,X,Y; scanf("%i\n", &T);
    for(int t=0; t<T; t++){

        //printP(kingPlat(0,7));


        scanf("%i %i %i %i %i %i\n", &f, &x, &y, &F, &X, &Y);
        vector<vector<int>> p(8, vector<int>(8, 9)); p[x][y] = 0;
        vector<vector<int>> P(8, vector<int>(8, 9)); P[X][Y] = 0;

        fillP(p, f, x, y);
        fillP(P, F, X, Y);

        //printP(p);
        //printP(P);

        int min = 9;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(p[i][j]+P[i][j]<min){ min = p[i][j]+P[i][j]; }
            }
        }

        cout<<min<<endl;


    }
    return 0;
}


/*

5
1 0 0 1 7 7
2 1 3 3 2 5 
0 1 0 4 5 5
3 1 1 4 3 3
0 1 2 0 3 4

6
2
2
1
2

*/