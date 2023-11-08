#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
//����ĵ�һ������������
//N�����򣬹���ҪM�������·��ÿ�������ṩK�����վ��ַ
//ÿ������Ĳ�ͬ����վ��۲�ͬ
//���ڳ����������·�������Ҳ���������˱��վ�ĺ�ѡ��ַ�ı仯���仯
//���ܼ����

//������1  N<=6,K<=10
//ö������ѡַ������O��K^N��~10^6
//���Ͷ�̬�滮+������ĵ����ڵ�ö��
//������5 ��
//ö�ٶȴ���2�Ľڵ㣬������6����
//�Զ���С�ڵ���2�ģ������һ�������߻�

//�Զ���Ϊ1�Ľڵ㣬�ɽ������ֱ��ת�޵������Ķ����ϣ�����ͨ��K^2��ʱ�临�Ӷȿ���ʵ�� 
//�Զ���Ϊ2�Ľڵ㣬�ɽ�����ǰ��������Ĵ��۱Ƚϵó�����ѡַ
//��ͨ���˷���ɾ�������Ķ���Ϊ1��2�ĵ㣬ʵ�ֶ�������5�Ľ��

//������������Ҳͬ�����ã����Խ��㶼ɾ��
//��Լ�㷨
//����ɼ�CCSP2018�ڶ��� ���������

int n, m, k;
int u[20007], v[20007], cst[10007][10];
//u��v��ʾ��Ԫ�飬����������ʱ��¼���ӵ���������ı��
vector<int> e[10007];
int ty[10007];
long long ans = 1000000000000000000;

int w[20007][10][10];//���ڼ�¼��i�к�

void tranverse(int nw)//����
{
	if (nw == n)
	{
		long long val = 0;
		for (int i = 0; i < n; i++) val += cst[i][ty[i]];
		for (int i = 1; i <= m; i++) val += w[i][ty[u[i]]][ty[v[i]]];
		ans = min(ans, val);
		return;
	}
	for (int i = 0; i < k; i++)
	{
		ty[nw] = i;//��¼nw������ѡ��վ���λ��
		tranverse(nw + 1);
	}
}
long long f[10007][10];
int sp, lim[10007];
void dfs(int nw, int fa)
//nw��ʾ��ǰ���б��,fa��ʾ
//ʵ�����Ƕ�̬�滮
{
	for (int i = 0; i < k; i++)
	{
		f[nw][i] = cst[nw][i];//���洢�����ݿ������洢nw���е�k��վ��Ľ������
	}
	for (auto eid : e[nw])//eid��������e�е�nw��vector
	{
		int son;//ѡ����nw�����ӵĳ���son
		if (u[eid] == nw) son = v[eid];
		else son = u[eid];//����eid�е����Ϊ��ǰ���У�son=v[eid]
		if (son == fa) continue;//��֦

		//���������Ѻ��ӽڵ㵱����һ�ֵĳ��У����׽ڵ����Ϊ��ǰ�ɳ���
		dfs(son, nw);//�ݹ飬�����ǻ���
		for (int i = 0; i < k; i++)
		{
			long long mn= 1000000000000000000;
			for (int j = 0; j < k; j++)
			{
				int we;
				if (u[eid] == nw) we = w[eid][i][j];//�ҵ�nwΪu[eid]��eid��·�����
				else we = w[eid][j][i];
				mn = min(mn, f[son][j] + we);
				//�ҳ���son��nw������������С�����
				//������β����sonѡ��j��վ��ķ���+��
			}
			f[nw][i] += mn;//nw->i���е���ۼ���ȥ
		}
	}
}
void dfs1(int nw, int fa)
{
	for (int i = 0; i < k; i++)
	{
		f[nw][i] = cst[nw][i];
	}
	//�����ǿ���һ��
	//���濪ʼ��������vector��ӵ��к�
	for (auto eid : e[nw])//��ǰ����ڵ��Ӧ�Ĵ洢���йص��к�
	{
		int son;
		if (u[eid] == nw) son = v[eid];//�����ж�Ӧ����ʼ����Ϊ��ǰ�غϵĳ��У�����һ�����ʵ��ӳ��и�ֵΪ�յ����
		else son = u[eid];

		//�ӽڵ������ˡ��������ж��ҵ����
		if (son == fa) continue;//������
		if (eid == sp)
		{
			//��ǰ�к����ú������������һ�£�����Ҫ���ǣ�ֱ��ȷ�����
			if (lim[nw] >= 0) continue;//��¼�������������

			for (int i = 0; i < k; i++)
			{
				f[nw][i] += w[sp][lim[son]][i];
			}
			continue;
		}

		dfs1(son, nw);

		//����
		for (int i = 0; i < k; i++)
		{
			long long mn = 1e18;
			for (int j = 0; j < k; j++)
			{
				int we;
				if (u[eid] == nw) we = w[eid][i][j];//�ҵ�nwΪu[eid]��eid��·�����
				else we = w[eid][j][i];
				mn = min(mn, f[son][j] + we);
				//�ҳ���son��nw������������С�����
				//������β����sonѡ��j��վ��ķ���+��
			}
			f[nw][i] += mn;
		}
	}
	if (lim[nw] >= 0)
		for (int i = 0; i < k; ++i)
			if (i != lim[nw]) f[nw][i] = 1e18;
}
struct Dsu 
{
	int f[10007];//���鼯 ��¼���ڵ�
	void init()
	{
		for (int i = 0; i <= n; i++) f[i] = i;//��ʼ�� ÿ���ڵ�ĸ�Ԫ��Ϊ����
	}

	int find(int x)//�ݹ�ʵ�ֲ��鼯���ܣ�����·��ѹ��
	{
		if (x == f[x]) 
		{
			return x;

		}
		else 
		{
			f[x] = find(f[x]);
			return f[x];
		}
	}
	bool merge(int u, int v)
	{
		u = find(u);
		v = find(v);
		//�˴��ҹ����ڵ�
		if (u == v) return false;
		else
		{
			f[u] = v;//��u��v�ĸ��ڵ㲻��ͨ����v��Ϊu�ĸ��׽ڵ㣬�Ӷ�������
			return true;
		}
	}
}dsu;

int main()
{
	cin >> n >> m >> k;
	//������cst����洢N��K�е����ݣ�
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			cin >> cst[i][j];
		}
	}
	//ע�⣬��cst��i��0��ʼ
	//��lim����ȫ��ʼ��Ϊ-1
	memset(lim, -1, sizeof(lim));
	//������M�У�����Ҫ��m��·
	//����ÿһ�ж���Ҫ��K*K+2��·
	for (int i = 1; i <= m; i++)
	{
		cin >> u[i] >> v[i];
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
		//��i��ӵ�e[u[i]]��e[v[i]]������������С�
		//����һ��ͼ�ı�ʾ����������u[i]��v[i]��Ϊ�������㣬
		//֮��Ĳ�������������������ء�
		//����e���������У�ʵ�����Ƕ�λ���飩��u[i]��v[i]�����б���Ϻ͵�i���йأ���֮�����ϵ��ֱ�ӵ��ü���
		for (int j = 0; j < k; j++)
		{
			for (int jj = 0; jj < k; jj++)
				cin >> w[i][j][jj];
		}
	}
	//������������ȫ��

	if (n <= 6)//������1
	{
		//ֱ�ӱ�������
		tranverse(0);
		cout << ans; 
		return 0;
	}
	if (m == n - 1)//������2
	{
		dfs(0, 0);//��ʵ�Ƕ�̬�滮
		for (int i = 0; i < k; i++)
		{
			ans = min(ans, f[0][i]);
		}
		cout << ans;
		return 0;
	}
	if (m == n)//
	{
		dsu.init();
		for (int i = 1; i <= m; i++)//�����еı߱����������кϲ�
		{
			if (!dsu.merge(u[i], v[i]))//�Ⱥϲ������ж�u[i]��v[i]�Ƿ�����ͬһ��ͼ
			{
				sp = i;
				break;
				//����ǰ��i�е���������ڵ�ԭ���Ѿ����ӣ�˵�������˻�����¼�ñߵı��sp������ѭ��
			}
		}
		for (int i = 0; i < k; i++)
		{
			lim[u[sp]] = i;//ö������߶�Ӧ����ʼ����������������õ��趨Ϊ��K�ֿ��ܣ��ڴ˻�����ö��
			//���趨�������ȷ��ѡ���i���㽨���ʱ�����������Ϊǰ�ᣬ����
			dfs1(0, 0);//���ʼ�ջص���0���ڵ㣬����Ҫ����0���ڵ��ѡȡÿһ��վ����Ҫ���ѵ�����
			for (int t = 0; t < k; t++)
			{
				ans = min(ans, f[0][t]);//
			}
		}
		cout << ans;
		return 0;
	}
}
