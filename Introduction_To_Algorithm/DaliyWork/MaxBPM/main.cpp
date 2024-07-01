#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1000;

vector<int> adj[MAXN];
int match[MAXN];
bool visited[MAXN];
int n, m;

bool bpm(int u) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || bpm(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBPM() {
    memset(match, -1, sizeof(match));
    int result = 0;
    for (int u = 1; u <= m; u++) {
        memset(visited, 0, sizeof(visited));
        if (bpm(u)) {
            result++;
        }
    }
    return result;
}

int main() {
    cin >> m >> n;
    int u, v;
    while (cin >> u >> v && (u != -1 || v != -1)) {
        adj[u].push_back(v);
    }

    int maxMatches = maxBPM();
    cout << maxMatches << endl;
    for (int v = m + 1; v <= n; v++) {
        if (match[v] != -1) {
            cout << match[v] << " " << v << endl;
        }
    }

    return 0;
}