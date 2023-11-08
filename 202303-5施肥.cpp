#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
typedef pair<int, int> P;
typedef long long ll;
const int N = 2e5 + 10;
int n, m, c, mx;
vector<int>f[N], st[N];
set<int>cur;
map<P, bool>vis;
ll ans, now[N];
struct node {
	int l, r;
}e[N], x;
bool operator<(node a, node b) {
	return a.r < b.r;
}



void special()
{
	//要做的是检测分成了几段
	long long len = 1;
	for (int i = 2; i <= m; i++)
	{
		if (e[i - 1].r > e[i].l)//包含在内
		{
			len++;
		}
		else
		{
			//len++;
			ans += 1ll * len * (len + 1) / 2;
			//cout <<"区间长度为" << len << endl;
			len = 1;
		}
	}
	//len++;
	//cout << "区间长度为" << len << endl;
	ans += len * (len + 1) / 2;
}

int main() {
	cin>>n>>m;
	for (int i = 1; i <= m; ++i) {
		cin>>x.l>>x.r;
		//e[++c]=x;
		if (!vis[P(x.l, x.r)])e[++c] = x;
		vis[P(x.l, x.r)] = 1;
	}
	m = c;
	sort(e + 1, e + m + 1);
	if (n > 3000) 
	{
		special();
		printf("%lld\n", ans);
	}
	else {
		for (int i = 1; i <= m; ++i) {
			st[e[i].l].push_back(e[i].r);
		}
		for (int i = 1; i <= n; ++i) {
			if (st[i].empty())continue;
			cur.clear();
			for (auto& v : st[i])cur.insert(v);
			for (int j = 1; j <= m; ++j) {
				if (e[j].l < i)continue;
				if (cur.lower_bound(e[j].l - 1) != cur.end()) {
					int x = *cur.lower_bound(e[j].l - 1);
					if (x <= e[j].r)cur.insert(e[j].r);
				}
			}
			ans += cur.size();
		}
		printf("%lld\n", ans);
	}
	return 0;
}



/*
5 3
3 4
1 2
2 3

7 5
1 2
2 3
3 4
5 6
6 7


*/

