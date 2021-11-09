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
    bool dual;
    int dualInt;

    void rotate(int e){
        while(e2!=e){
            int temp = e1;
            e1 = e3; e3 = e2; e2 = temp;
        }
    }
    void dualRotate(){
        int temp = e1;
        e1 = e2; e2 = e3; e3 = temp;
    }
    void init(){
        if(e1==e2 && e1!=e3){
            dual = true;
            dualInt = e1;
            e1=e3;
            e3=e2;
        }else if(e1==e3 && e2!=e1){
            dual =true;
            dualInt = e1;
            e1 = e2;
            e2 = e3;
        }else if(e2==e3 && e1!=e2){
            dual = true;
            dualInt = e2;
        }else{
            dual = false;
        }
    }

    T(): id(-1),e1(-1),e2(-1),e3(-1) {};
    T(int _e1,int _e2,int _e3): id(-1),e1(_e1),e2(_e2),e3(_e3) {};
} T;

char c;
T Ts[6];
list<T*> nums[100];

int compute(T* t){
   
    int max = -1;
    for(T* o : nums[t->e1]){
        if(!o->used){
            if(o->dual && t->e1==o->dualInt){
                o->used = true;
                //cout<<"*"<<o->id<<" "<<o->e1<<o->e2<<o->e3<<endl;
                int comp;
                if(Ts[0].used && Ts[1].used && Ts[2].used && Ts[3].used && Ts[4].used && Ts[5].used){
                    if(o->e1==Ts[0].e2 && o->e2==t->e1){
                        comp =  Ts[0].e3 + Ts[1].e3 + Ts[2].e3 + Ts[3].e3 + Ts[4].e3 + Ts[5].e3;
                    }
                    else{
                        comp =  -1;
                    }
                }else{
                    comp = compute(o);
                }
                //cout<<"=="<<comp<<endl;
                if(comp>max){ max=comp; }
                o->used = false;

                o->dualRotate();

                o->used = true;
                //cout<<"*"<<o->id<<" "<<o->e1<<o->e2<<o->e3<<endl;
                int comp2;
                if(Ts[0].used && Ts[1].used && Ts[2].used && Ts[3].used && Ts[4].used && Ts[5].used){
                    if(o->e1==Ts[0].e2 && o->e2==t->e1){
                        comp2= Ts[0].e3 + Ts[1].e3 + Ts[2].e3 + Ts[3].e3 + Ts[4].e3 + Ts[5].e3;
                        //cout<<"fff"<<o->e1<<Ts[0].e2<<endl;
                    }
                    else{
                        comp2= -1;
                    }
                }else{
                    comp2 = compute(o);
                }
                
                //cout<<"=="<<comp2<<endl;
                if(comp2>max){ max=comp2; }
                o->used = false;     
                if(comp>comp2){
                    o->dualRotate();
                    o->dualRotate();
                }
            }else{
                o->rotate(t->e1);
                o->used = true;
                //cout<<"*"<<o->id<<" "<<o->e1<<o->e2<<o->e3<<endl;
                int comp;
                if(Ts[0].used && Ts[1].used && Ts[2].used && Ts[3].used && Ts[4].used && Ts[5].used){
                    if(o->e1==Ts[0].e2){
                        comp =  Ts[0].e3 + Ts[1].e3 + Ts[2].e3 + Ts[3].e3 + Ts[4].e3 + Ts[5].e3;
                    }
                    else{
                        comp =  -1;
                    }
                }else{
                    comp = compute(o);
                }
                if(comp>max){ max=comp; }
                o->used = false;
            }
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
            if(Ts[i].e2!=Ts[i].e1){
                nums[Ts[i].e2].push_back(&Ts[i]);
            }
            if(Ts[i].e3!=Ts[i].e1 && Ts[i].e3!=Ts[i].e2){
                nums[Ts[i].e3].push_back(&Ts[i]);
            }
            Ts[i].init();
        }
        Ts[0].used = true;
        //cout<<"*"<<Ts[0].id<<" "<<Ts[0].e1<<Ts[0].e2<<Ts[0].e3<<endl;



        int r1 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }

        //cout<<"______________"<<r1<<endl;

        Ts[0].dualRotate();
        int r2 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }
        //cout<<"______________"<<r2<<endl;

        Ts[0].dualRotate();
        int r3 = compute(&Ts[0]);
        for(int i=1; i<6; i++){ Ts[i].used = false; }
        //cout<<"______________"<<r3<<endl;

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