#include <iostream>
#include <vector>

using namespace std;

void dfs(int vertex, int color[], int currentColor, vector<int> graph[]) {
    color[vertex] = currentColor;
    for (int i = 0; i < graph[vertex].size(); i++) {
        int newVertex = graph[vertex][i];
        if (color[newVertex] == 0)
            dfs(newVertex, color, currentColor, graph);
    }
}

void buildGraph(int edgesCount, vector<int> graph[]) {
    int vertex1, vertex2;
    for (int i = 0; i < edgesCount; i++) {
        cin >> vertex1 >> vertex2;
        vertex1--, vertex2--;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }
}

int main() {
    int vertexCount, edgesCount;
    cin >> vertexCount >> edgesCount;
    vector<int> graph[vertexCount];
    buildGraph(edgesCount, graph);
    
    int color[vertexCount];
    for (int i= 0; i < vertexCount; i++)
        color[i] = 0;
    
    int count  = 0;
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (color[vertex] == 0) {
            count++;
            dfs(vertex, color, count, graph);
        }
    }

    cout << count << endl;
    for (int i = 0; i < vertexCount; i++)
        cout << color[i] << " ";
    return 0;
}