#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

class Graph {
public:
    int V; // 顶点数
    vector<list<int>> adj; // 邻接表


    Graph(int V) : V(V), adj(V) {}

    // 添加边
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // 使用广度优先搜索（BFS）找到从源节点到目标节点的路径
    vector<int> findShortestPath(int source, int destination) {
        bool* visited = new bool[V];
        int* parent = new int[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
            parent[i] = -1;
        }

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    parent[*it] = u;
                    q.push(*it);
                }
            }
        }

        vector<int> shortestPath;
        if (!visited[destination]) {
            delete[] visited;
            delete[] parent;
            return shortestPath; // 如果目标节点不可达，返回空路径
        }

        for (int v = destination; v != -1; v = parent[v]) {
            shortestPath.insert(shortestPath.begin(), v);
        }

        delete[] visited;
        delete[] parent;

        return shortestPath;
    }

    vector<vector<int>> transitiveClosure() {
        vector<vector<int>> tc(V, vector<int>(V, 0)); // 初始化传递闭包矩阵为全0

        for (int i = 0; i < V; ++i) {
            // 标记当前节点已访问，用于避免自身到自身的循环路径
            vector<bool> visited(V, false);
            list<int> queue;

            visited[i] = true;
            
            for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
                queue.push_back(*it);
            }

            while (!queue.empty()) {
                int u = queue.front();
                queue.pop_front();

                for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                    if (!visited[*it]) {
						
						visited[*it] = true;
                        tc[i][*it] = 1; // 路径存在，标记为1
                        
                        queue.push_back(*it);
                    }
                }
            }
        }

        return tc;
    }

};

int main() {
    int V = 6; // 假设有6个顶点
    Graph g(V);
    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    int source = 0;
    int destination = 5;

    vector<int> shortestPath = g.findShortestPath(source, destination);

    if (shortestPath.empty()) {
        cout << "Path from " << source << " to " << destination << " doesn't exist.";
    }
    else {
        cout << "Shortest Path from " << source << " to " << destination << " is: ";
        for (int i = 0; i < shortestPath.size(); ++i) {
            cout << shortestPath[i] << " ";
        }
    }
    cout << endl;


    cout << "graph:" << endl;
    for (int i = 0; i < g.adj.size(); i++) {
        cout << "ADJ List of Vertex " << i << ":";
        for (auto it = g.adj[i].begin(); it != g.adj[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "TC:" << endl;
    vector<vector<int>>TC = g.transitiveClosure();
    for (int i = 0; i < TC.size(); i++) {
        for (int j = 0; j < TC[i].size(); j++) {
            cout << TC[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
