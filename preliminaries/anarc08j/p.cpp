#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct Driver{
	string name;
    int score = 0;
	int ranks[8] = {0,0,0,0,0,0,0,0};
    Driver(){};
	Driver(string _f, int _s): name(_f), score(_s) {};
} Driver;

typedef struct Team{
	string name;
    int score = 0;
    Team(){};
	Team(string _f, int _s): name(_f), score(_s) {};
} Team;

bool cmpDriver(Driver x, Driver y){
    if (x.score != y.score){
        return x.score > y.score;
    }else if(x.ranks[0] != y.ranks[0]){
        return x.ranks[0] > y.ranks[0];
    }else if(x.ranks[1] != y.ranks[1]){
        return x.ranks[1] > y.ranks[1];
    }else if(x.ranks[2] != y.ranks[2]){
        return x.ranks[2] > y.ranks[2];
    }else if(x.ranks[3] != y.ranks[3]){
        return x.ranks[3] > y.ranks[3];
    }else if(x.ranks[4] != y.ranks[4]){
        return x.ranks[4] > y.ranks[4];
    }else if(x.ranks[5] != y.ranks[5]){
        return x.ranks[5] > y.ranks[5];
    }else if(x.ranks[6] != y.ranks[6]){
        return x.ranks[6] > y.ranks[6];
    }else if(x.ranks[7] != y.ranks[7]){
        return x.ranks[7] > y.ranks[7];
    }else{
        string Xfirstname = x.name.substr(0, x.name.find(" "));
        string Xlastname = x.name.substr(x.name.find(" ")+1, x.name.size());

        string Yfirstname = y.name.substr(0, y.name.find(" "));
        string Ylastname = y.name.substr(y.name.find(" ")+1, y.name.size());

        if(string(Xlastname) != string(Ylastname)){
            return string(Xlastname) < string(Ylastname);
        }else{
            return string(Xfirstname) < string(Yfirstname);
        }
    }
}

bool cmpTeam(Team x, Team y){
    if (x.score != y.score){
        return x.score > y.score;
    }else{
        return string(x.name) < string(y.name);
    }
}

int main(){



    int N;
    string s;
    int points[8] = {10,8,6,5,4,3,2,1};
    int k = 1;

    while(scanf("%i\n", &N)==1 && N!=0){

    

    unordered_map<string, Driver> drivers;
    unordered_map<string, Team> teams;


	while(N--){
        getline(cin, s); // NAME
        getline(cin, s); // Pos Driver Team

        for(int i=0; i<8; i++){
            getline(cin, s);
            s = s.substr(5, s.size());
            string fullname = s.substr(0, 25);

            if(drivers.find(fullname) == drivers.end()){
                drivers[fullname] = Driver(fullname, points[i]);
                drivers[fullname].ranks[i]++;
            }else{
                drivers[fullname].score += points[i];
                drivers[fullname].ranks[i]++;
            }

            string team = s.substr(26, s.size());
            team = team.substr(0, team.find("."));

            if(teams.find(team) == teams.end()){
                teams[team] = Team(team, points[i]);
            }else{
                teams[team].score += points[i];
            }
        }
        
        getline(cin, s); // ---
	}

//cout<<"*****"<<drivers["a a                      "].ranks[0]<<endl;
//cout<<"*****"<<drivers["b b                      "].ranks[0]<<endl;

    vector<Driver> vecdrivers;
    for(auto d : drivers){
        vecdrivers.push_back(d.second);
    }
    sort(vecdrivers.begin(), vecdrivers.end(), cmpDriver);
    cout<<"Season "<<k<<":"<<endl;
    k++;
    cout<<"Drivers Standing:"<<endl;
    for(auto d : vecdrivers){
        cout<<d.name<<" "<<d.score<<endl;
    }
    cout<<endl;
    cout<<"Teams Standing:"<<endl;
    vector<Team> vecteams;
    for(auto d : teams){
        vecteams.push_back(d.second);
    }
    sort(vecteams.begin(), vecteams.end(), cmpTeam);

    for(auto d : vecteams){
        cout<<d.name;
        for(int i=0; i<25-int(d.name.size()); i++){
            cout<<" ";
        }
        cout<<" "<<d.score<<endl;
    }
    cout<<endl;


    }

	return 0;
}

/*

Output:
Season 1:
Drivers Standing:
Fernando Alonso          20
Michael Schumacher       12
Giancarlo Fisichella     9
Jaun-Pablo Montoya       8
Rubens Barrichello       7
David Coulthard          6
Felipe Massa             5
Kimi Raikkonen           4
Jenson Button            3
Nick Heidfeld            3
Ralf Schumacher          1

Teams Standing:
Renault                  29
Ferrari                  17
McLaren-Mercedes         12
Honda                    10
RBR-Ferrari              6
Sauber-BMW               3
Toyota                   1

*/