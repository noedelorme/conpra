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
    if(grundy[i] != -1){ return grundy[i]; }
    else{
        vector<bool> grs(21,false);
        for(int j=0; fib[j]<=i; j++){
            int gr = grundize(i-fib[j]);
            grs[gr] = true;
        }
        int mex = 0;
        while(grs[mex]){ mex++; }
        grundy[i] = mex;
        return grundy[i];
    }
}

int main(){

    

    fib[0] = fib[1] = 1;
    for(int i=2; i<32; i++){ fib[i] = fib[i-1] + fib[i-2]; }
    grundy[0] = 0;




    int i=0;
    while(i<20000){
        i++;
        int g=grundize(i);
        while(g!=0){
            cout<<g<< " ";
            i++;
            g=grundize(i);
        }
        cout<<endl;
    }

    /*int N; scanf("%i\n", &N);
    vector<int> stacks(N);
    for(int i=0; i<N; i++){ scanf("%i", &stacks[i]); }
    
    int nimsum=0;
    
    for(int s : stacks){
        nimsum ^= grundize(s);
    }

    if(nimsum == 0){ printf("Vinit\n"); }else{ printf("Ada\n"); }
    */

    return 0;
}


/*

0 0 *
1 1
2 2
3 3
4 0 *
5 1
6 2
7 3
8 4
9 5
10 0 *
11 1
12 2
13 3
14 0 *
15 1
16 2
17 3
18 4
19 5
20 0 *
21 1
22 2
23 3
24 0 *
25 1
26 2
27 3
28 4
29 5
30 0 *
31 1
32 2
33 3
34 4
35 5
36 0 *
37 1
38 2
39 3
40 0 *
41 1
42 2
43 3
44 4
45 5
46 0 *
47 1
48 2
49 3
50 0 *
51 1
52 2
53 3
54 4
55 5
56 0 *
57 1
58 2
59 3
60 0 *
61 1
62 2
63 3
64 4
65 5
66 0 *
67 1
68 2
69 3
70 4
71 5
72 0 *
73 1
74 2
75 3
76 0 *
77 1
78 2
79 3
80 4
81 5
82 0 *
83 1
84 2
85 3
86 0 *
87 1
88 2
89 3
90 4
91 5
92 0 *
93 1
94 2
95 3
96 0 *
97 1
98 2
99 3
100 4
101 5
102 0 *
103 1
104 2
105 3
106 4
107 5
108 0 *
109 1
110 2
111 3
112 0 *
113 1
114 2
115 3
116 4
117 5
118 0 *
119 1
120 2
121 3
122 0 *
123 1
124 2
125 3
126 4
127 5
128 0 *
129 1
130 2
131 3
132 0 *
133 1
134 2
135 3
136 4
137 5
138 0 *
139 1
140 2
141 3
142 4
143 5
144 6
145 7
146 4
147 5
148 6
149 7
*/