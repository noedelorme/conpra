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
    int N,K;
    while(scanf("%i %i\n", &N, &K) && N!=0){

        if(K==0){
            cout<<N-1<<endl;
            continue;
        }
        
        long int lessK = 1;
        long int asK = 0;
        long int weight = 0;

        list<long int> data(K-1,0);
        data.push_front(1);

        //for(auto i : data){ cout<<i<<" "; } cout<<"  ("<<weight<<")"<<endl;

        for(int y=0; y<N-1; y++){
            weight += lessK + asK;
            data.push_front(lessK);
            long int asKm1 = data.back(); asK += asKm1; data.pop_back();
            lessK = lessK + lessK - asKm1;
            if(weight>=1234567890){break;}
        }
        cout<<weight<<endl;
    }

    return 0;
}


/*

Input:
10000 0
101 1
10 2
1221 128
0 0


Output:
9999
5050
221
2147483647

*/