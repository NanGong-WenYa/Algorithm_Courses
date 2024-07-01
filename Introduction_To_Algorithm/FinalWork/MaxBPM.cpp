#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 1000;

vector<int> adj[MAXN];
int match[MAXN];
bool visited[MAXN];
int n, m;

bool findMatch(int u) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || findMatch(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> m >> n;
    int u, v;
    while (cin >> u >> v && (u != -1 || v != -1)) {
        adj[u].push_back(v);
    }

    memset(match, -1, sizeof(match));
    int maxMatches = 0;

    for (int i = 1; i <= m; i++) {
        memset(visited, 0, sizeof(visited));
        if (findMatch(i)) {
            maxMatches++;
        }
    }

    cout << maxMatches << endl;
    for (int i = m + 1; i <= n; i++) {
        if (match[i] != -1) {
            cout << match[i] << " " << i << endl;
        }
    }

    return 0;
}
