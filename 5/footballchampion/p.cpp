#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <climits>
#include <cfloat>

using namespace std;

#define SI(x) scanf("%d",&x)
#define SII(x,y) scanf("%d %d",&x,&y)
#define SIII(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define SIIII(x,y,z,w) scanf("%d %d %d %d",&x,&y,&z,&w)
#define SL(x) scanf("%lld",&x)
#define SD(x) scanf("%lf",&x)
#define SC(x) scanf("%c",&x)
#define SS(x) scanf("%s",x)
#define FOR(i, s, k, p) for(int i=s; i<k; i+=p)
#define REP(i, n) FOR(i, 0, n, 1)
#define INF INT_MAX
#define EPS 1e-9
#define PI acos(-1)

typedef long long int lint;
typedef unsigned long long int ulint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<lint> vl;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef list<int> li;
typedef list<double> ld;
typedef list<bool> lb;
typedef vector<vector<int>> vvi;
typedef vector<vector<lint>> vvl;
typedef vector<vector<double>> vvd;
typedef vector<pair<int, int>> vii;
typedef list<pair<int, int>> lii;
typedef vector<list<int>> vli;
typedef vector<list<pair<int, int>>> vlii;
typedef vector<list<pair<double,int>>> vldi;


/* Source: https://www.geeksforgeeks.org/push-relabel-algorithm-set-2-implementation/ */

// C++ program to implement push-relabel algorithm for
// getting maximum flow of graph
#include <bits/stdc++.h>
  
struct Edge
{
    // To store current flow and capacity of edge
    int flow, capacity;
  
    // An edge u--->v has start vertex as u and end
    // vertex as v.
    int u, v;
  
    Edge(int flow, int capacity, int u, int v)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->u = u;
        this->v = v;
    }
};
  
// Represent a Vertex
struct Vertex
{
    int h, e_flow;
  
    Vertex(int h, int e_flow)
    {
        this->h = h;
        this->e_flow = e_flow;
    }
};
  
// To represent a flow network
class Graph
{
public:
    int V;    // No. of vertices
    vector<Vertex> ver;
    vector<Edge> edge;
  
    // Function to push excess flow from u
    bool push(int u);
  
    // Function to relabel a vertex u
    void relabel(int u);
  
    // This function is called to initialize
    // preflow
    void preflow(int s);
  
    // Function to reverse edge
    void updateReverseEdgeFlow(int i, int flow);
  

    Graph(int V);  // Constructor
  
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
  
    // returns maximum flow from s to t
    int getMaxFlow(int s, int t);
};
  
Graph::Graph(int V)
{
    this->V = V;
  
    // all vertices are initialized with 0 height
    // and 0 excess flow
    for (int i = 0; i < V; i++)
        ver.push_back(Vertex(0, 0));
}
  
void Graph::addEdge(int u, int v, int capacity)
{
    // flow is initialized with 0 for all edge
    edge.push_back(Edge(0, capacity, u, v));
}
  
void Graph::preflow(int s)
{
    // Making h of source Vertex equal to no. of vertices
    // Height of other vertices is 0.
    ver[s].h = ver.size();
  
    //
    for (int i = 0; i < edge.size(); i++)
    {
        // If current edge goes from source
        if (edge[i].u == s)
        {
            // Flow is equal to capacity
            edge[i].flow = edge[i].capacity;
  
            // Initialize excess flow for adjacent v
            ver[edge[i].v].e_flow += edge[i].flow;
  
            // Add an edge from v to s in residual graph with
            // capacity equal to 0
            edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
        }
    }
}
  
// returns index of overflowing Vertex
int overFlowVertex(vector<Vertex>& ver)
{
    for (int i = 1; i < ver.size() - 1; i++)
       if (ver[i].e_flow > 0)
            return i;
  
    // -1 if no overflowing Vertex
    return -1;
}
  
// Update reverse flow for flow added on ith Edge
void Graph::updateReverseEdgeFlow(int i, int flow)
{
    int u = edge[i].v, v = edge[i].u;
  
    for (int j = 0; j < edge.size(); j++)
    {
        if (edge[j].v == v && edge[j].u == u)
        {
            edge[j].flow -= flow;
            return;
        }
    }
  
    // adding reverse Edge in residual graph
    Edge e = Edge(0, flow, u, v);
    edge.push_back(e);
}
  
// To push flow from overflowing vertex u
bool Graph::push(int u)
{
    // Traverse through all edges to find an adjacent (of u)
    // to which flow can be pushed
    for (int i = 0; i < edge.size(); i++)
    {
        // Checks u of current edge is same as given
        // overflowing vertex
        if (edge[i].u == u)
        {
            // if flow is equal to capacity then no push
            // is possible
            if (edge[i].flow == edge[i].capacity)
                continue;
  
            // Push is only possible if height of adjacent
            // is smaller than height of overflowing vertex
            if (ver[u].h > ver[edge[i].v].h)
            {
                // Flow to be pushed is equal to minimum of
                // remaining flow on edge and excess flow.
                int flow = min(edge[i].capacity - edge[i].flow,
                               ver[u].e_flow);
  
                // Reduce excess flow for overflowing vertex
                ver[u].e_flow -= flow;
  
                // Increase excess flow for adjacent
                ver[edge[i].v].e_flow += flow;
  
                // Add residual flow (With capacity 0 and negative
                // flow)
                edge[i].flow += flow;
  
                updateReverseEdgeFlow(i, flow);
  
                return true;
            }
        }
    }
    return false;
}
  
// function to relabel vertex u
void Graph::relabel(int u)
{
    // Initialize minimum height of an adjacent
    int mh = INT_MAX;
  
    // Find the adjacent with minimum height
    for (int i = 0; i < edge.size(); i++)
    {
        if (edge[i].u == u)
        {
            // if flow is equal to capacity then no
            // relabeling
            if (edge[i].flow == edge[i].capacity)
                continue;
  
            // Update minimum height
            if (ver[edge[i].v].h < mh)
            {
                mh = ver[edge[i].v].h;
  
                // updating height of u
                ver[u].h = mh + 1;
            }
        }
    }
}
  
// main function for printing maximum flow of graph
int Graph::getMaxFlow(int s, int t)
{
    preflow(s);
  
    // loop untill none of the Vertex is in overflow
    while (overFlowVertex(ver) != -1)
    {
        int u = overFlowVertex(ver);
        if (!push(u))
            relabel(u);
    }
  
    // ver.back() returns last Vertex, whose
    // e_flow will be final maximum flow
    return ver.back().e_flow;
}



int main(){

	int t; SI(t); FOR(testcase, 1, t+1, 1){
		int n,m; SII(n,m);
        int s=0; int t=n+1; int N=n+2;

		vi wins(n);
        vb canWin(N, false);
        vii games(m);

        REP(i,n){ int w; SI(w); wins[i]=w; }

        REP(i,m){
            int a,b; SII(a,b);
            games[i] = make_pair(min(a,b),max(a,b));
        }

        FOR(i,1,N-1,1){
            Graph* graph = new Graph(N);

            int maxWins = wins[i-1];
            for(pii p : games){ if(p.first==i || p.second==i){ maxWins++; } }

            vi possibleWins(n);
            for(pii p : games){
                if (p.first!=i && p.second!=i) {
                    possibleWins[p.first-1] += 1;
                    graph->addEdge(p.first, p.second, 1);
                }
            }

            REP(j,N-2){
                if(j+1 != i){
                    graph->addEdge(s, j+1, wins[j] + possibleWins[j]);
                    graph->addEdge(j+1, t, maxWins);
                }
            }

            graph->getMaxFlow(s, t);

            bool flag=true;
            REP(j,N-1){
                if(graph->ver[j].e_flow != 0){ flag=false; break; }
            }
            canWin[i-1]=flag;
        }

		printf("Case #%d: ", testcase);
        REP(i,n){ if(canWin[i]){ printf("yes "); }else{ printf("no "); } }
        printf("\n");
    }

    return 0;
}