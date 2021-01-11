#include <iostream>
#include <vector>

using namespace std;

const int INF = 21;

struct Edge {
    int to;
    int capacity;
    int flow;
    int pairedRib;

    Edge(int to, int capacity, int flow, int pairedRib) : to(to), capacity(capacity), flow(flow),
                                                          pairedRib(pairedRib) {}
};

int pushFlow(int vertex, int target, bool visited[], int curFlow, vector<Edge> graph[]) {
    if (vertex == target)
        return curFlow;
    visited[vertex] = true;
    for (int i = 0; i < graph[vertex].size(); i++) {
        Edge edge = graph[vertex][i];
        if (not visited[edge.to] && (edge.flow < edge.capacity)) {
            int nextFlow = min(curFlow, edge.capacity - edge.flow);
            int delta = pushFlow(edge.to, target, visited, nextFlow, graph);
            if (delta > 0) {
                graph[vertex][i].flow += delta;
                graph[edge.to][edge.pairedRib].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

void buildGraph(int edgesCount, vector<Edge> graph[]) {
    int vertex1, vertex2, capacity;
    for (int i = 0; i < edgesCount; i++) {
        cin >> vertex1 >> vertex2 >> capacity;
        vertex1--, vertex2--;
        graph[vertex1].push_back(Edge(vertex2, capacity, 0, graph[vertex2].size()));
        graph[vertex2].push_back(Edge(vertex1, 0, 0, graph[vertex1].size() - 1));
        graph[vertex2].push_back(Edge(vertex1, capacity, 0, graph[vertex1].size()));
        graph[vertex1].push_back(Edge(vertex2, 0, 0, graph[vertex2].size() - 1));
    }
}

int main() {
    int vertexCount, edgesCount, delta, ans = 0;
    cin >> vertexCount >> edgesCount;
    vector<Edge> graph[vertexCount];
    buildGraph(edgesCount, graph);
    bool visited[vertexCount];
    while (true) {
        for (int i = 0; i < vertexCount; i++)
            visited[i] = false;
        delta = pushFlow(0, vertexCount - 1, visited, INF, graph);
        if (delta > 0)
            ans += delta;
        else
            break;
    }
    cout << ans;
    return 0;
}