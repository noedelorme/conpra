#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

int main(){

    int t; scanf("%i\n", &t);
    int n;
    string s;

    for(int i=0; i<t; i++){
        scanf("%i\n", &n);
        printf("Case #%i:\n", i+1);

        for(int j=0; j<n; j++){
            getline(cin, s);
            int pin = 0;
            while(pin < s.size()){
                if(s[pin]=='e' && s[pin+1]=='n' && s[pin+2]=='t'){
                    if((s[pin+3]=='i' || s[pin+3]=='e') && s[pin+4]=='n'){
                        printf("ierende");
                        pin += 5;
                    }else{
                        printf("ierender");
                        pin += 3;
                    }
                }else{ cout << s[pin]; pin++;}
            }
            printf("\n");
        }
    }

    return 0;
}