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

typedef struct T{
    int id;
	int e1,e2,e3;
    bool used;

    void rotate(int e){
        while(e2!=e){
            int temp = e1;
            e1 = e3; e3 = e2; e2 = temp;
        }
    }

    T(): id(-1),e1(-1),e2(-1),e3(-1) {};
} T;

char c;
T Ts[6];
list<T*> nums[100];

int compute(T* t){
    //cout<<"="<<t->id<<" "<<t->used<<endl;
    if(Ts[0].used && Ts[1].used && Ts[2].used && Ts[3].used && Ts[4].used && Ts[5].used){
        if(t->e1==Ts[0].e2){
            return Ts[0].e3 + Ts[1].e3 + Ts[2].e3 + Ts[3].e3 + Ts[4].e3 + Ts[5].e3;
        }
        else{
            return -1;
        }
    }

    int max = -1;
    for(T* o : nums[t->e1]){
        if(!o->used){
            o->rotate(t->e1);
            o->used = true;
            if(Ts[0].used && Ts[1].used && Ts[2].used && Ts[3].used && Ts[4].used && Ts[5].used){
                if(o->e1==Ts[0].e2){
                    return Ts[0].e3 + Ts[1].e3 + Ts[2].e3 + Ts[3].e3 + Ts[4].e3 + Ts[5].e3;
                }
                else{
                    return -1;
                }
            }
            int comp = compute(o);
            if(comp>max){ max=comp; }
            o->used = false;
        }
    }

    return max;
}

int main(){


    while(true){

        for(int i=0; i<6; i++){
            Ts[i].id = i;
            scanf("%i %i %i\n", &Ts[i].e1, &Ts[i].e2, &Ts[i].e3);
            nums[Ts[i].e1].push_back(&Ts[i]);
            nums[Ts[i].e2].push_back(&Ts[i]);
            nums[Ts[i].e3].push_back(&Ts[i]);
        }
        Ts[0].used = true;
        int f1=Ts[0].e1; int f2=Ts[0].e2; int f3=Ts[0].e3;

        Ts[0].rotate(f1);
        int r1 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }

        Ts[0].rotate(f2);
        int r2 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }

        Ts[0].rotate(f3);
        int r3 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }

        for(int i=0; i<100; i++){
            nums[i].clear();
        }

        int mtn = max(max(r1,r2),r3);
        if(mtn>=0){ cout<<mtn<<endl; }else{ cout<< "none"<<endl; }
        

        scanf("%c\n", &c);
        if(c=='$'){ break; }

    }

    return 0;
}


/*

Sample Input

1 4 20 
3 1 5 
50 2 3 
5 2 7 
7 5 20 
4 7 50 
* 
10 1 20 
20 2 30 
30 3 40 
40 4 50 
50 5 60 
60 6 10 
* 
10 1 20 
20 2 30 
30 3 40 
40 4 50 
50 5 60 
10 6 60 
$

Sample Output

152 
21 
none

*/