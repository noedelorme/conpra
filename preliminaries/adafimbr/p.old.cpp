#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

vector<int> grundy(3000001, -1);
vector<int> fib(32);

int grundize(int i){
    if(i==0){ return 0; }
    else if(grundy[i] != -1){ return grundy[i]; }
    else{
        set<int> states;
        for(int j=0; fib[j]<=i; j++){
            states.insert(grundize(i-fib[j]));
        }
        int mex = 0;
        while(states.count(mex)>0){ mex++; }
        grundy[i] = mex;
        return grundy[i];
    }
}

int main(){
    fib[0] = fib[1] = 1;
    for(int i=2; i<32; i++){ fib[i] = fib[i-1] + fib[i-2]; }

    int h=0;
    for(int i=0; i<150; i++){
        h = grundize(i);
        cout<<h<<endl;
    }


    int N; scanf("%i\n", &N);
    vector<int> stacks(N);
    for(int i=0; i<N; i++){ scanf("%i", &stacks[i]); }
    
    int nimsum=0;
    for(int s : stacks){
        nimsum ^= grundize(s);
    }

    if(nimsum == 0){
        printf("Vinit\n");
    }else{
        printf("Ada\n");
    }
    
    return 0;
}