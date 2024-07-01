#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> topologicalSort(vector<vector<int>>& graph, vector<int>& indegree) {
    int n = graph.size();
    vector<int> result;
    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        result.push_back(curr + 1); // 加1以符合题目中的顶点编号从1开始的要求

        for (int neighbor : graph[curr]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return result;
}

bool dfs(vector<vector<int>>& graph, int node, vector<int>& visited, vector<int>& parent, vector<int>& cycle) {
    visited[node] = 1; // 标记为正在访问

    for (int neighbor : graph[node]) {
        if (visited[neighbor] == 0) {
            parent[neighbor] = node;
            if (dfs(graph, neighbor, visited, parent, cycle))
                return true;
        }
        else if (visited[neighbor] == 1) {
            // 找到环
            cycle.push_back(neighbor);
            for (int p = node; p != neighbor; p = parent[p]) {
                cycle.push_back(p);
            }
            cycle.push_back(neighbor);
            return true;
        }
    }

    visited[node] = 2; // 标记为已访问
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        indegree[y - 1]++;
    }

    vector<int> visited(n, 0); // 0表示未访问，1表示正在访问，2表示已访问
    vector<int> parent(n, -1);
    vector<int> cycle;

    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            if (dfs(graph, i, visited, parent, cycle)) {
                cout << "NO" << endl;
                for (int j = 0; j < cycle.size(); ++j) {
                    cout << cycle[j] + 1;
                    if (j < cycle.size() - 1)
                        cout << ",";
                }
                cout << endl;
                return 0;
            }
        }
    }

    auto topoResult = topologicalSort(graph, indegree);
    cout << "YES" << endl;
    for (int v : topoResult) {
        cout << v << ",";
    }
    cout << endl;

    return 0;
}