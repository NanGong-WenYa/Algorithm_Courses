#include <iostream>
#include <vector>
#include <limits>
#include <iomanip> // 包含<iomanip>头文件

using namespace std;

const int MAX_N = 1000;
const double INF = numeric_limits<double>::infinity();

struct Point {
    int x, y;
};

double calculateError(const vector<Point>& points, int start, int end) {
    int n = end - start + 1;
    if (n <= 1) return 0.0;

    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;
    for (int i = start; i <= end; ++i) {
        sum_x += points[i].x;
        sum_y += points[i].y;
        sum_x2 += points[i].x * points[i].x;
        sum_xy += points[i].x * points[i].y;
    }

    double denom = n * sum_x2 - sum_x * sum_x;
    if (denom == 0) return 0.0;

    double a = (n * sum_xy - sum_x * sum_y) / denom;
    double b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;

    double error = 0.0;
    for (int i = start; i <= end; ++i) {
        double y_pred = a * points[i].x + b;
        error += (points[i].y - y_pred) * (points[i].y - y_pred);
    }
    return error;
}

int main() {
    int n;
    double C;
    cin >> n >> C;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<double> dp(n + 1, INF);
    dp[0] = 0.0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            double error = calculateError(points, j, i - 1);
            dp[i] = min(dp[i], dp[j] + error + C);
        }
    }

    cout << fixed << setprecision(2) << dp[n] << endl;

    return 0;
}