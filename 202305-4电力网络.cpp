#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
//输入的第一行三个正整数
//N个城镇，共需要M条输电线路，每个城镇都提供K个变电站地址
//每个城镇的不同供电站造价不同
//对于城镇间的输电线路，其造价也会随着两端变电站的候选地址的变化而变化
//求总价最低

//子任务1  N<=6,K<=10
//枚举所有选址方案：O（K^N）~10^6
//树型动态规划+多出来的单独节点枚举
//子任务5 ：
//枚举度大于2的节点，不超过6个，
//对度数小于等于2的，延伸出一条链或者环

//对度数为1的节点，可将其代价直接转嫁到相连的顶点上，这样通过K^2的时间复杂度可以实现 
//对度数为2的节点，可将其与前后两个点的代价比较得出最优选址
//可通过此方法删除迭代的度数为1和2的点，实现对子任务5的解决

//对其他子任务，也同样适用，可以将点都删完
//规约算法
//更多可见CCSP2018第二题 最大点独立集

int n, m, k;
int u[20007], v[20007], cst[10007][10];
//u和v表示二元组，在最后的输入时记录连接的两个城镇的编号
vector<int> e[10007];
int ty[10007];
long long ans = 1000000000000000000;

int w[20007][10][10];//用于记录第i行和

void tranverse(int nw)//遍历
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
		ty[nw] = i;//记录nw城市所选的站点的位置
		tranverse(nw + 1);
	}
}
long long f[10007][10];
int sp, lim[10007];
void dfs(int nw, int fa)
//nw表示当前城市编号,fa表示
//实际上是动态规划
{
	for (int i = 0; i < k; i++)
	{
		f[nw][i] = cst[nw][i];//将存储的数据拷贝，存储nw城市的k个站点的建造费用
	}
	for (auto eid : e[nw])//eid遍历整个e中第nw个vector
	{
		int son;//选出与nw相连接的城市son
		if (u[eid] == nw) son = v[eid];
		else son = u[eid];//若第eid行的起点为当前城市，son=v[eid]
		if (son == fa) continue;//剪枝

		//接下来，把孩子节点当成新一轮的城市，父亲节点更新为当前旧城市
		dfs(son, nw);//递归，下面是回溯
		for (int i = 0; i < k; i++)
		{
			long long mn= 1000000000000000000;
			for (int j = 0; j < k; j++)
			{
				int we;
				if (u[eid] == nw) we = w[eid][i][j];//找到nw为u[eid]的eid，路线造价
				else we = w[eid][j][i];
				mn = min(mn, f[son][j] + we);
				//找出将son和nw连接起来的最小的造价
				//包括：尾城市son选第j个站点的费用+，
			}
			f[nw][i] += mn;//nw->i城市的造价加上去
		}
	}
}
void dfs1(int nw, int fa)
{
	for (int i = 0; i < k; i++)
	{
		f[nw][i] = cst[nw][i];
	}
	//上面是拷贝一份
	//下面开始遍历所有vector后接的行号
	for (auto eid : e[nw])//当前城镇节点对应的存储的有关的行号
	{
		int son;
		if (u[eid] == nw) son = v[eid];//若该行对应的起始城市为当前回合的城市，将下一个访问的子城市赋值为终点城市
		else son = u[eid];

		//子节点找完了。接下来判断找的情况
		if (son == fa) continue;//重新找
		if (eid == sp)
		{
			//当前行号正好和特殊点所在行一致，不需要考虑，直接确定情况
			if (lim[nw] >= 0) continue;//记录过该特殊点的情况

			for (int i = 0; i < k; i++)
			{
				f[nw][i] += w[sp][lim[son]][i];
			}
			continue;
		}

		dfs1(son, nw);

		//回溯
		for (int i = 0; i < k; i++)
		{
			long long mn = 1e18;
			for (int j = 0; j < k; j++)
			{
				int we;
				if (u[eid] == nw) we = w[eid][i][j];//找到nw为u[eid]的eid，路线造价
				else we = w[eid][j][i];
				mn = min(mn, f[son][j] + we);
				//找出将son和nw连接起来的最小的造价
				//包括：尾城市son选第j个站点的费用+，
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
	int f[10007];//并查集 记录父节点
	void init()
	{
		for (int i = 0; i <= n; i++) f[i] = i;//初始化 每个节点的父元素为自身
	}

	int find(int x)//递归实现并查集功能，进行路径压缩
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
		//此处找过根节点
		if (u == v) return false;
		else
		{
			f[u] = v;//当u和v的根节点不联通，将v设为u的父亲节点，从而串起来
			return true;
		}
	}
}dsu;

int main()
{
	cin >> n >> m >> k;
	//接下来cst数组存储N行K列的数据，
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			cin >> cst[i][j];
		}
	}
	//注意，在cst中i从0开始
	//将lim数组全初始化为-1
	memset(lim, -1, sizeof(lim));
	//接下来M行，由于要修m条路
	//所以每一行都需要有K*K+2条路
	for (int i = 1; i <= m; i++)
	{
		cin >> u[i] >> v[i];
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
		//将i添加到e[u[i]]和e[v[i]]所代表的向量中。
		//这是一个图的表示方法，即将u[i]和v[i]作为两个顶点，
		//之后的操作将与这两个顶点相关。
		//即在e向量数组中（实际上是二位数组）第u[i]和v[i]个城市标记上和第i行有关，在之后的联系中直接调用即可
		for (int j = 0; j < k; j++)
		{
			for (int jj = 0; jj < k; jj++)
				cin >> w[i][j][jj];
		}
	}
	//到此所有输入全部

	if (n <= 6)//子问题1
	{
		//直接暴力遍历
		tranverse(0);
		cout << ans; 
		return 0;
	}
	if (m == n - 1)//子问题2
	{
		dfs(0, 0);//其实是动态规划
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
		for (int i = 1; i <= m; i++)//对所有的边遍历，并进行合并
		{
			if (!dsu.merge(u[i], v[i]))//先合并，再判断u[i]和v[i]是否属于同一个图
			{
				sp = i;
				break;
				//若当前第i行的两个城镇节点原来已经连接，说明出现了环，记录该边的编号sp并跳出循环
			}
		}
		for (int i = 0; i < k; i++)
		{
			lim[u[sp]] = i;//枚举特殊边对应的起始点的限制条件，即该点设定为有K种可能，在此基础上枚举
			//在设定特殊城市确定选择第i个点建设的时候，以这种情况为前提，深搜
			dfs1(0, 0);//最后始终回到第0个节点，所以要看第0个节点的选取每一个站点需要花费的数量
			for (int t = 0; t < k; t++)
			{
				ans = min(ans, f[0][t]);//
			}
		}
		cout << ans;
		return 0;
	}
}
