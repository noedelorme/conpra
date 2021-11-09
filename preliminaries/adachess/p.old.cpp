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

int main(){


    /*for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            for(int k=0; k<2; k++){
                for(int l=0; l<2; l++){
                    cout << i << " "<<j<<" "<<k<<" "<<l<<" "<<endl;
                }
            }
        }
    }
    cout<<"============"<<endl;*/

    vector<vector<int>> ta = {
        {0,3,2,3,2,3,4,5},
        {3,2,1,2,3,4,3,4},
        {2,1,4,3,2,3,4,5},
        {3,2,3,2,3,4,3,4},
        {2,3,2,3,4,3,4,5},
        {3,4,3,4,3,4,5,4},
        {4,3,4,3,4,5,4,5},
        {5,4,5,4,5,4,5,6}
    };

    int T,f,x,y,F,X,Y; scanf("%i\n", &T);
    for(int t=0; t<T; t++){
        scanf("%i %i %i %i %i %i\n", &f, &x, &y, &F, &X, &Y);

        bool ps[5] = {false,false,false,false,false};
        ps[f]=true; ps[F]=true;
        int dx=abs(x-X); int dy=abs(y-Y);

        if(dx==0 && dy==0){ cout << 0 << endl; }

        else if(ps[1]){
            if(ps[0]){
                list<int> poses;
                poses.push_back(ta[dx][dy]);
                if(dx+1<8){ poses.push_back(ta[dx+1][dy]+1); }
                if(dx-1>=0){ poses.push_back(ta[dx-1][dy]+1); }
                if(dy+1<8){ poses.push_back(ta[dx][dy+1]+1); }
                if(dy-1>=0){ poses.push_back(ta[dx][dy-1]+1); }
                if(dx+1<8 and dy+1<8){ poses.push_back(ta[dx+1][dy+1]+1); }
                if(dx+1<8 and dy-1>=0){ poses.push_back(ta[dx+1][dy-1]+1); }
                if(dx-1>=0 and dy+1<8){ poses.push_back(ta[dx-1][dy+1]+1); }
                if(dx-1>=0 and dy-1>=0){ poses.push_back(ta[dx-1][dy-1]+1); }
                int min=1000;
                for(auto p : poses){
                    if(p<min){ min=p; }
                }
                cout << min <<endl;
            }else if(ps[2]){
                if((dx==1 && dy==2) || (dx==2 && dy==1) || dx==0 || dy==0 || dx==dy){ cout << 1 <<endl; }else{ cout << 2 <<endl; }
            }else if(ps[3]){
                if((dx==1 && dy==2) || (dx==2 && dy==1) || dx==0 || dy==0){ cout << 1 <<endl; }else{ cout << 2 <<endl; }
            }else if(ps[4]){
                if((dx==1 && dy==2) || (dx==2 && dy==1) || dx==dy){ cout << 1 <<endl; }else if((dx+dy)%2==0){ cout << 2 <<endl; }
                else{
                    int xK,yK,xA,yA; if(f==4){ xK=X; yK=Y; xA=x; yA=y; }else{ xK=x; yK=y; xA=X; yA=Y; }

                    list<pair<int,int>> poses;
                    if(xK+2<8 and yK+1<8){ poses.push_back({xK+2,yK+1}); }
                    if(xK+1<8 and yK+2<8){ poses.push_back({xK+1,yK+2}); }
                    if(xK-1>=0 and yK+2<8){ poses.push_back({xK-1,yK+2}); }
                    if(xK-2>=0 and yK+1<8){ poses.push_back({xK-2,yK+1}); }
                    if(xK-2>=0 and yK-1>=0){ poses.push_back({xK-2,yK-1}); }
                    if(xK-1>=0 and yK-2>=0){ poses.push_back({xK-1,yK-2}); }
                    if(xK+1<8 and yK-2>=0){ poses.push_back({xK+1,yK-2}); }
                    if(xK+2<8 and yK-1>=0){ poses.push_back({xK+2,yK-1}); }

                    bool flag = false;

                    for(auto p : poses){
                        int ndx = abs(p.first-xA); int ndy = abs(p.second-yA);
                        if(ndx==ndy){ cout << 2 << endl; flag=true; break; }
                    }

                    if(!flag){ cout << 3 << endl; }
                }
            }
            else{
                if(dx==1 && dy==1 && ((x%7==0 && y%7==0) || (X%7==0 && Y%7==0))){ cout << 4 << endl; }else{ cout << ta[dx][dy] << endl; }
            }
        }

        else if(ps[2]){
            if(dx==0 || dy==0 || dx==dy){ cout << 1 << endl; }else{ cout << 2 <<endl; }
        }

        else if(ps[0]){
            if(ps[4]){
                if((dx==1 && dy==0) || (dx==0 && dy==1) || dx==dy){ cout << 1<< endl; }
                else if((dx+dy)%2==0){ cout << 2 << endl; }
                else{
                    int xK,yK,xA,yA; if(f==4){ xK=X; yK=Y; xA=x; yA=y; }else{ xK=x; yK=y; xA=X; yA=Y; }

                    list<pair<int,int>> poses;
                    if(xK+1<8){ poses.push_back({xK+1,yK}); }
                    if(xK-1>=0){ poses.push_back({xK-1,yK}); }
                    if(yK+1<8){ poses.push_back({xK,yK+1}); }
                    if(yK-1>=0){ poses.push_back({xK,yK-1}); }

                    bool flag = false;

                    for(auto p : poses){
                        int ndx = abs(p.first-xA); int ndy = abs(p.second-yA);
                        if(ndx==ndy){ cout << 2 << endl; flag=true; break; }
                    }

                    if(!flag){ cout << 3 << endl; }
                }
            }else if(ps[3]){
                if((dx==1 && dy==1) || dx==0 || dy==0){ cout << 1 << endl; }else{ cout << 2 << endl; }
            }else{
                cout << max(dx,dy) << endl;
            }
        }

        else if(ps[4]){
            if(ps[3]){
                if(dx==0 || dy==0 || dx==dy){ cout << 1 << endl; }else{ cout << 2<< endl; }
            }else{
                if((dx+dy)%2==1){ cout << "INF" << endl; }else if(dx==dy){ cout << 1 << endl; }else{ cout << 2 << endl; }
            }
        }
        
        else if(ps[3]){
            if(dx==0 || dy==0){ cout << 1 << endl; }else{ cout << 2<< endl; }
        }


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

10
2 3 6 1 6 2
3 3 6 3 6 7
4 4 6 4 2 4
3 6 0 4 1 0
3 7 1 3 5 2
0 0 6 1 5 4
0 5 7 3 3 5
0 4 1 4 5 3
3 2 1 3 4 2
0 5 2 0 2 7

2
2
1
1
2
3
2
2
2
5

*/