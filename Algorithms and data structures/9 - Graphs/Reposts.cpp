#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define START_VERTEX "polycarp"

void dfs(string vertex, map<string, bool> visited, int height, int &max, map<string, vector<string>> graph) {
    visited[vertex] = true;
    if (++height > max)
        max = height;
    for (string newVertex : graph[vertex]) {
        if (!visited[newVertex])
            dfs(newVertex, visited, height, max, graph);
    }
}

map<string, vector<string>> buildGraph() {
    int edgesCount;
    cin >> edgesCount;
    map<string, vector<string>> graph;
    string name1, name2, trash;
    for (int i = 0; i < edgesCount; i++) {
        cin >> name1 >> trash >> name2;
        transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
        transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
        graph[name1].push_back(name2);
        graph[name2].push_back(name1);
    }
    return graph;
}

int main() {
    map<string, vector<string>> graph = buildGraph();
    map<string, bool> visited;
    for (auto const &x : graph)
        visited[x.first] = false;
    int max = 0;
    dfs(START_VERTEX, visited, 0, max, graph);
    cout << max;
    return 0;
}