#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int SIZE = 9;
struct Edge {
int src, dest, weight;
};
typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type
class Graph {
public:
// a vector of vectors of Pairs to represent an adjacency list
vector<vector<Pair>> adjList;
// Graph Constructor
Graph(vector<Edge> const &edges) {
// resize the vector to hold SIZE elements of type vector<Edge>
adjList.resize(SIZE);
// add edges to the directed graph
for (auto &edge: edges) {
int src = edge.src;
int dest = edge.dest;
int weight = edge.weight;
// insert at the end
adjList[src].push_back(make_pair(dest, weight));
// for an undirected graph, add an edge from dest to src also
adjList[dest].push_back(make_pair(src, weight));
}
}
// Print the graph's adjacency list
void printGraph() {
cout << "Graph's adjacency list:" << endl;
for (int i = 0; i < adjList.size(); i++) {
cout << i << " --> ";
for (Pair v : adjList[i])
cout << "(" << v.first << ", " << v.second << ") ";
cout << endl;
}
}
void DFS(int src){
    vector<bool> visited(SIZE, false);
    //vector<int> res;
    stack<int> s;
    s.push(src);
    cout << "DFS starting from vertex " << src << ":\n";
    while(!s.empty()){
        int curr = s.top();
        s.pop();
        //res.push_back(curr);
        visited[curr] = true;
        cout << curr << " ";

        for (auto x : adjList[curr]){
            if(!visited[x.first]){
                visited[x.first] = true;
                s.push(x.first);
            }
        }

     }
     cout << endl;

}
void BFS(int src){
    vector<bool> visited(SIZE, false);
    vector<int> res;
    queue<int> q;
    visited[src] = true;
     q.push(src);
    
     cout << "BFS starting from vertex " << src << ":\n";
     while(!q.empty()){
        int curr = q.front();
        q.pop();
        //visited[src] = true;
        res.push_back(curr);
        cout << curr << " ";

        for (auto x : adjList[curr]){
            if(!visited[x.first]){
                visited[x.first] = true;
                q.push(x.first);
            }
        }

     }
     cout << endl;
}
};

int main() {
// Creates a vector of graph edges/weights
vector<Edge> edges = {
// (x, y, w) —> edge from x to y having weight w
{0,1,8},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,8,8},{3,4,9},{5,6,10},{5,7,15},{5,8,5},{6,7,3},{6,8,7}
};
// Creates graph
Graph graph(edges);
// Prints adjacency list representation of graph
graph.printGraph();
graph.DFS(0);
graph.BFS(0);
return 0;
}