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

#define SCD(t) scanf("%d\n",&t)
#define SCLD(t) scanf("%ld\n",&t)
#define SCLLD(t) scanf("%lld\n",&t)
#define SCC(t) scanf("%c\n",&t)
#define SCS(t) scanf("%s\n",t)
#define SCF(t) scanf("%f\n",&t)
#define SCLF(t) scanf("%lf\n",&t)
#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define FOREACH(it, l) for(auto it = l.begin(); it != l.end(); it++)
#define INF (int)1e9
#define EPS 1e-9
#define PI acos(-1)

typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

using namespace std;

int pin=0;

int readInt(string s){
    int n = s[pin]-'0';
    while(isdigit(s[++pin])){
        n = 10*n+s[pin]-'0';
    }
    return n;
}

int readOper(string s){
    int oldpin = pin;
    while(!isdigit(s[pin])){ pin++; }
    string word = s.substr(oldpin, pin-oldpin);
    if(word == "plus"){ return 0; }
    if(word == "minus"){ return 1; }
    if(word == "times"){ return 2; }
    if(word == "tothepowerof"){ return 3; }
    return -1;
}

int main(){

    int t; SCD(t);
    string s;

    REP(i, t){
        getline(cin, s);

        int32 calc = readInt(s);;
        while(pin<s.length()){
            int op = readOper(s);
            int n2 = readInt(s);
            if(op==0){ calc = calc+n2; }
            if(op==1){ calc = calc-n2; }
            if(op==2){ calc = calc*n2; }
            if(op==3){ calc = pow(calc,n2); }
        }

        pin = 0;

        printf("Case #%d: %ld\n", i+1, calc);
    }

    return 0;
}