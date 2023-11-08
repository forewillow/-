#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int n;
int a[1005];
long long dp[1005];
bool vis[100005];//判断这个数的约数是否使用过
vector<int>q[100005];//q[i]的所有元素表示i的约数
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	//初始化约束
	for (int j = 1; j < 100005; j++)
	{
		for (int i = 2 * j; i < 100005; i += j)
		{
			q[i].push_back(j);//j的所有倍数的因数都包含j
		}
	}
	dp[0] = 1;//当没有点时，全都不选，只有一种
	for (int i = 1; i < n; i++)//枚举所有状态
	{
		memset(vis, 0, sizeof(vis));//初始化为0
		for (int j = i-1; j >=0; j--)
		{
			int d = a[i] - a[j];//d为区间长度
			int cnt = 0;
			for (int k : q[d])//用k遍历当前区间长度的所有因数
			{
				if (!vis[k])
				{
					cnt++;
					vis[k] = 1;//已经使用过
				}
			}
			vis[d] = 1;//有障碍的地方不能种树
			//求和
			dp[i] = (dp[i] + dp[j] * cnt) % 1000000007;
		}
	}
	cout << dp[n - 1] << endl;
}
