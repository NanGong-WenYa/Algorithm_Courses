#include<iostream>
#include<queue>
using namespace std;
int hcForEachNation[100005];
struct node {
	int t, nation;
}h;
queue<node>crew;
queue<int>ans;
int n, newT, newN,hc,  numOfN = 0;
int main()
{
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> newT >> hc;
		while (!crew.empty())
		{
			h = crew.front();
			if (h.t + 86400 <= newT) {
				crew.pop();
				hcForEachNation[h.nation]--;
				if (hcForEachNation[h.nation] == 0)numOfN--;
			}
			else break;
		}
		for (int j = 0; j < hc; j++) {
			cin >> newN;
			h.t = newT;
			h.nation = newN;
			crew.push(h);
			hcForEachNation[newN]++;
			if (hcForEachNation[newN] == 1)numOfN++;
		}
		ans.push(numOfN);
	}
	while (!ans.empty())
	{
		cout << ans.front()<<endl;
		ans.pop();
	}
}


