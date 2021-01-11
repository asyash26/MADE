#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int INF = 10000001;

struct Edge {
    int to;
    int capacity;
    int flow;
    int pairedRib;
    int number;

    Edge(int to, int capacity, int flow, int pairedRib, int number) : to(to), capacity(capacity), flow(flow),
                                                                      pairedRib(pairedRib), number(number) {}
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
        graph[vertex1].push_back(Edge(vertex2, capacity, 0, graph[vertex2].size(), i + 1));
        graph[vertex2].push_back(Edge(vertex1, 0, 0, graph[vertex1].size() - 1, i + 1));
        graph[vertex2].push_back(Edge(vertex1, capacity, 0, graph[vertex1].size(), i + 1));
        graph[vertex1].push_back(Edge(vertex2, 0, 0, graph[vertex2].size() - 1, i + 1));
    }
}

void getSPart(int vertex, bool partS[], vector<Edge> graph[]) {
    partS[vertex] = true;
    for (int i = 0; i < graph[vertex].size(); i++) {
        Edge edge = graph[vertex][i];
        if (not partS[edge.to]  && (edge.capacity - edge.flow > 0))
            getSPart(edge.to, partS, graph);
    }
}

void getCuttingRibs(int vertex, bool visited[], bool partS[], vector<Edge> graph[], vector<int> &answer) {
    visited[vertex] = true;
    for (int i = 0; i < graph[vertex].size(); i++) {
        Edge edge = graph[vertex][i];
        if (partS[vertex] && !partS[edge.to])
            answer.push_back(edge.number);
        if (not visited[edge.to])
            getCuttingRibs(edge.to, visited, partS, graph, answer);
    }
}

int main() {
    int vertexCount, edgesCount, delta, maxFlow = 0;
    vector<int> answer;
    cin >> vertexCount >> edgesCount;
    vector<Edge> graph[vertexCount];
    buildGraph(edgesCount, graph);
    bool visited[vertexCount], partS[vertexCount];
    while (true) {
        for (int i = 0; i < vertexCount; i++)
            visited[i] = false;
        delta = pushFlow(0, vertexCount - 1, visited, INF, graph);
        if (delta > 0)
            maxFlow += delta;
        else
            break;
    }
    for (int i = 0; i < vertexCount; i++)
        partS[i] = false;
    getSPart(0, partS, graph);
    for (int i = 0; i < vertexCount; i++)
        visited[i] = false;
    getCuttingRibs(0, visited, partS, graph, answer);
    set<int> s(answer.begin(), answer.end());
    cout << s.size() << " " << maxFlow << endl;
    for (auto it = s.begin(); it !=s.end(); ++it)
        cout << *it << " ";
    return 0;
}