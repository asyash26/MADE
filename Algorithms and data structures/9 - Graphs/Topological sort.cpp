#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool hasLoop(int vertex, int color[], vector<int> graph[]) {
    color[vertex] = 1;
    for (int i = 0; i < graph[vertex].size(); i++) {
        int newVertex = graph[vertex][i];
        if (color[newVertex] == 0)
            hasLoop(newVertex, color, graph);
        if (color[newVertex] == 1) {
            return true;
        }
    }
    color[vertex] = 2;
    return false;
}

bool checkLoops(vector<int> graph[], int vertexCount) {
    int color[vertexCount];
    for (int i = 0; i < vertexCount; i++)
        color[i] = 0;
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (color[vertex] == 0) {
            if (hasLoop(vertex, color, graph))
                return true;
        }
    }
    return false;
}

void dfs(int vertex, bool visited[], vector<int> graph[], vector<int> &ans) {
    visited[vertex] = true;
    for (int i = 0; i < graph[vertex].size(); i++) {
        int newVertex = graph[vertex][i];
        if (!visited[newVertex])
            dfs(newVertex, visited, graph, ans);
    }
    ans.push_back(vertex + 1);
}

vector<int> topSort(int vertexCount, vector<int> graph[]) {
    vector<int> ans;
    bool visited[vertexCount];
    for (int i = 0; i < vertexCount; i++)
        visited[i] = false;
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (!visited[vertex]) {
            dfs(vertex, visited, graph, ans);
        }
    }
    reverse(begin(ans), end(ans));
    return ans;
}

void buildGraph(int edgesCount, vector<int> graph[]) {
    int vertex1, vertex2;
    for (int i = 0; i < edgesCount; i++) {
        cin >> vertex1 >> vertex2;
        vertex1--, vertex2--;
        graph[vertex1].push_back(vertex2);
    }
}

int main() {
    int vertexCount, edgesCount;
    cin >> vertexCount >> edgesCount;
    vector<int> graph[vertexCount];
    buildGraph(edgesCount, graph);
    bool hasLoops = checkLoops(graph, vertexCount);
    if (!hasLoops) {
        vector<int> ans = topSort(vertexCount, graph);
        for (int i = 0; i < vertexCount; i++)
            cout << ans[i] << " ";
    } else
        cout << -1;
    return 0;
}

