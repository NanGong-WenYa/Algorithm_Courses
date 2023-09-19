#include<iostream>
#include<queue>
#include<stack>
#include<string>
using namespace std;
int main() {
	stack<int> pushed;
	queue<int>poped, pushedArr;
	queue<string>ans;
	int a, q;
	int n;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> a;
			pushedArr.push(a);
		}
		for (int j = 0; j < n; j++) {
			cin >> a;
			poped.push(a);
		}
		while (!pushedArr.empty())
		{
			pushed.push(pushedArr.front());
			pushedArr.pop();
			while (!pushed.empty()) {
				if (pushed.top() == poped.front())
				{
					pushed.pop();
					poped.pop();
				}
				else break;
			}
		}
		if (pushed.empty())
			ans.push("Yes");
		else ans.push("No");
		while (!pushed.empty())pushed.pop();
		while (!poped.empty())poped.pop();
	}
	while (!ans.empty()) {
		cout << ans.front() << endl;
		ans.pop();
	}
	return 0;
}