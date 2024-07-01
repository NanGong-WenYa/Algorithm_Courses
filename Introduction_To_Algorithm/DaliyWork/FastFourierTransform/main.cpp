#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> Complex;

const double PI = acos(-1.0);

// 快速傅里叶变换
void fft(vector<Complex>& a, bool inverse) {
    int n = a.size();
    if (n == 1) return;

    vector<Complex> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, j++) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft(a0, inverse);
    fft(a1, inverse);

    double ang = 2 * PI / n * (inverse ? -1 : 1);
    Complex w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (inverse) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// 多项式乘法
vector<int> multiply(vector<int>& a, vector<int>& b) {
    int n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;

    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1);
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }
    for (int i = m; i >= 0; i--) {
        cin >> b[i];
    }

    vector<int> result = multiply(a, b);

    for (int i = n + m; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}