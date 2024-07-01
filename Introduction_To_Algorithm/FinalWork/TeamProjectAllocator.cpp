#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 定义团队和项目的数量
int TEAM_COUNT;
int PROJECT_COUNT;

// 团队和项目的详细信息
unordered_map<int, string> teamNames;
unordered_map<int, string> projectNames;

// 团队对项目的偏好
vector<vector<int>> teamPreferences;
vector<vector<int>> projectPreferences;

// 项目之间的依赖关系（拓扑排序）
vector<vector<int>> adj;
vector<int> inDegree;

// 项目优先级权重
vector<int> projectWeights;

// 获取用户输入
void getInput() {
    cout << "请输入团队数量: ";
    cin >> TEAM_COUNT;
    cout << "请输入项目数量: ";
    cin >> PROJECT_COUNT;

    teamPreferences.resize(TEAM_COUNT, vector<int>(PROJECT_COUNT));
    projectPreferences.resize(PROJECT_COUNT, vector<int>(TEAM_COUNT));
    adj.resize(PROJECT_COUNT);
    inDegree.resize(PROJECT_COUNT, 0);
    projectWeights.resize(PROJECT_COUNT);

    cout << "请输入每个团队的名称:" << endl;
    for (int i = 0; i < TEAM_COUNT; i++) {
        cout << "团队 " << i << " 名称: ";
        string name;
        cin >> name;
        teamNames[i] = name;
    }

    cout << "请输入每个项目的名称:" << endl;
    for (int i = 0; i < PROJECT_COUNT; i++) {
        cout << "项目 " << i << " 名称: ";
        string name;
        cin >> name;
        projectNames[i] = name;
    }

    cout << "请输入团队对项目的偏好（每行输入一个团队对所有项目的偏好，按优先级从高到低排列）:" << endl;
    for (int i = 0; i < TEAM_COUNT; i++) {
        for (int j = 0; j < PROJECT_COUNT; j++) {
            cin >> teamPreferences[i][j];
        }
    }

    cout << "请输入项目对团队的偏好（每行输入一个项目对所有团队的偏好，按优先级从高到低排列）:" << endl;
    for (int i = 0; i < PROJECT_COUNT; i++) {
        for (int j = 0; j < TEAM_COUNT; j++) {
            cin >> projectPreferences[i][j];
        }
    }

    cout << "请输入项目之间的依赖关系（格式：项目A 项目B 表示项目A依赖于项目B，输入-1 -1结束）:" << endl;
    while (true) {
        int a, b;
        cin >> a >> b;
        if (a == -1 && b == -1) break;
        if (a < 0 || a >= PROJECT_COUNT || b < 0 || b >= PROJECT_COUNT) {
            cerr << "无效的项目编号！" << endl;
            continue;
        }
        adj[b].push_back(a);
        inDegree[a]++;
    }

    cout << "请输入每个项目的优先级权重（按项目编号顺序）:" << endl;
    for (int i = 0; i < PROJECT_COUNT; i++) {
        cin >> projectWeights[i];
    }
}


void allocateProjects(vector<int>& teamMatch, vector<int>& projectMatch) {
    vector<bool> teamFree(TEAM_COUNT, true);
    int freeCount = TEAM_COUNT;

    while (freeCount > 0) {
        int team;
        for (team = 0; team < TEAM_COUNT; team++) {
            if (teamFree[team]) break;
        }

        for (int i = 0; i < PROJECT_COUNT && teamFree[team]; i++) {
            int project = teamPreferences[team][i];

            if (projectMatch[project] == -1) {
                projectMatch[project] = team;
                teamMatch[team] = project;
                teamFree[team] = false;
                freeCount--;
            }
            else {
                int currentTeam = projectMatch[project];
                bool preferNewTeam = false;
                for (int j = 0; j < TEAM_COUNT; j++) {
                    if (projectPreferences[project][j] == team) {
                        preferNewTeam = true;
                        break;
                    }
                    if (projectPreferences[project][j] == currentTeam) break;
                }

                if (preferNewTeam) {
                    projectMatch[project] = team;
                    teamMatch[team] = project;
                    teamFree[team] = false;
                    teamFree[currentTeam] = true;
                }
            }
        }
    }
}


vector<int> sortProjects() {
    vector<int> order;
    queue<int> q;

    for (int i = 0; i < PROJECT_COUNT; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (order.size() != PROJECT_COUNT) {
        cerr << "Error: 依赖关系中存在循环！" << endl;
        exit(1);
    }

    return order;
}

// 输出结果到文件
void outputToFile(const vector<int>& teamMatch, const vector<int>& order) {
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "无法打开输出文件！" << endl;
        return;
    }

    outFile << "团队分配结果:" << endl;
    for (int i = 0; i < TEAM_COUNT; i++) {
        outFile << "团队 " << teamNames[i] << " -> 项目 " << projectNames[teamMatch[i]] << endl;
    }

    outFile << "项目优先级顺序:" << endl;
    for (int i : order) {
        outFile << "项目 " << projectNames[i] << " ";
    }
    outFile << endl;

    outFile.close();
}

// 显示菜单
void showMenu() {
    cout << "请选择操作:" << endl;
    cout << "1. 输入数据" << endl;
    cout << "2. 执行匹配并输出结果" << endl;
    cout << "3. 退出" << endl;
}

int main() {
    while (true) {
        showMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            getInput();
        }
        else if (choice == 2) {
            // 执行拓扑排序
            vector<int> order = sortProjects();

            // 初始化匹配数组
            vector<int> teamMatch(TEAM_COUNT, -1);
            vector<int> projectMatch(PROJECT_COUNT, -1);

            // 按项目优先级权重排序
            sort(order.begin(), order.end(), [&](int a, int b) {
                return projectWeights[a] > projectWeights[b];
                });

            // 执行稳定匹配
            allocateProjects(teamMatch, projectMatch);

            // 输出结果到文件
            outputToFile(teamMatch, order);

            // 输出到控制台
            cout << "团队分配结果:" << endl;
            for (int i = 0; i < TEAM_COUNT; i++) {
                cout << "团队 " << teamNames[i] << " -> 项目 " << projectNames[teamMatch[i]] << endl;
            }

            cout << "项目优先级顺序:" << endl;
            for (int i : order) {
                cout << "项目 " << projectNames[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "无效的选择，请重新输入。" << endl;
        }
    }

    return 0;
}