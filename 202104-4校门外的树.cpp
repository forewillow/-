#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int n;
int a[1005];
long long dp[1005];
bool vis[100005];//�ж��������Լ���Ƿ�ʹ�ù�
vector<int>q[100005];//q[i]������Ԫ�ر�ʾi��Լ��
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	//��ʼ��Լ��
	for (int j = 1; j < 100005; j++)
	{
		for (int i = 2 * j; i < 100005; i += j)
		{
			q[i].push_back(j);//j�����б���������������j
		}
	}
	dp[0] = 1;//��û�е�ʱ��ȫ����ѡ��ֻ��һ��
	for (int i = 1; i < n; i++)//ö������״̬
	{
		memset(vis, 0, sizeof(vis));//��ʼ��Ϊ0
		for (int j = i-1; j >=0; j--)
		{
			int d = a[i] - a[j];//dΪ���䳤��
			int cnt = 0;
			for (int k : q[d])//��k������ǰ���䳤�ȵ���������
			{
				if (!vis[k])
				{
					cnt++;
					vis[k] = 1;//�Ѿ�ʹ�ù�
				}
			}
			vis[d] = 1;//���ϰ��ĵط���������
			//���
			dp[i] = (dp[i] + dp[j] * cnt) % 1000000007;
		}
	}
	cout << dp[n - 1] << endl;
}
