#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <limits>

using namespace std;
const int SIZE = 8;
struct Edge {
int src, dest, weight;
};
typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type
class Graph {
public:
// a vector of vectors of Pairs to represent an adjacency list
vector<vector<Pair>> adjList;
vector<string> landmarks = {"ARC", "Brandy", "Anteatery", "DBH", "EH", "ELH", "Bio sci lib", "Starbucks"};
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
   // vector<string> landmarks = {"ARC", "Brandy", "Anteatery", "DBH", "EH", "ELH", "Bio sci lib", "Starbucks"};
cout << "UCI navigation system" << endl;
cout << "==========================\n";
for (int i = 0; i < adjList.size(); i++) {
    cout << "Landmark " << i << " (" << landmarks[i] << ") close to:\n";
for (Pair v : adjList[i])
cout << " -> Landmark " << v.first << " (" << landmarks[v.first] << ") - Travel Time: " << v.second << " mins\n ";
cout << endl;
}
}
void DFS(int src){
    vector<bool> visited(SIZE, false);
    //vector<int> res;
    stack<int> s;
    s.push(src);
    visited[src] = true;
    cout << "DFS route starting from " << src << ":\n";
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
    
     cout << "BFS route starting from " << src << ":\n";
     while(!q.empty()){
        int curr = q.front();
        q.pop();
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
void shortestPath(int src){
    int MAX = numeric_limits<int>::max();
    vector<int> dist(SIZE, MAX);
    dist[src] = 0;

    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()){
        int curr = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        for (auto edge : adjList[u]){
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != MAX && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << "Shortest path from node " << src << ":\n";
    for (int i = 0; i < SIZE; i++){
        cout << src << " -> " << i << " : ";
            cout << dist[i] << "\n";
        }
    }
    void tree(int src){
        const int MAX = numeric_limits<int>::max();
        vector<int> key(SIZE, MAX);   
        vector<int> parent(SIZE, -1);
        vector<bool> MST(SIZE, false); 
        key[0] = 0;

        for (int count = 0; count < SIZE - 1; ++count) {
            int u = -1;
            int minKey = MAX;

            for (int v = 0; v < SIZE; ++v) {
                if (!MST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            MST[u] = true;

            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int w = edge.second;

                if (!MST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }


    }
};

int main() {
// Creates a vector of graph edges/weights
vector<Edge> edges = {
// (x, y, w) —> edge from x to y having weight w
{0,1,5},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,7,7},{3,4,9},{5,6,10},{5,7,15},{5,7,5},{6,7,3}
};
// Creates graph
Graph graph(edges);
// Prints adjacency list representation of graph
graph.printGraph();
graph.DFS(0);
graph.BFS(0);
graph.shortestPath(0);
graph.tree(0);
return 0;
}