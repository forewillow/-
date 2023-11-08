#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const int N = 100009;
ll n;
string aimline;//目标,最多有10个地点
//需要存储开头字母和结尾字母
//需要做成邻接表
//数据现需要存入字符串数组
struct line
{
	char begin;
	char end;
	string whole;
};
line lines[N];
struct group
{
	string line;
	int index;
};
vector<group> map[27];//开头从a到z
ll ans = 0x3f3f3f3f;
void check_input()
{
	for (int i = 1; i <= n; i++)
	{
		cout << lines[i].whole<<endl;
	}
	cout <<endl;
	for (int i = 1; i <= 26; i++)
	{
		
	}
}
int vis[N] = { 0 };
bool allValuesAreZero(string link) 
{
	for (int i = 0; i < aimline.length(); ++i)
	{
		if (link.find(aimline[i]) == std::string::npos)
		{
			return false;//说明没找到
		}
	}
	return true;
}
void dfs(string arr,ll sum,char target,char linkchar,string link)//分别表示 线路总长度，目的地，连接的字母
{
	//cout << "当前为" << arr << " ";
	//cout << "接龙到" << link << " "<<"长度为"<<sum<<endl;
	int id = linkchar - 'a' + 1;
	if (linkchar == target)//遍历完成
	{
		if (allValuesAreZero(link))//成功，
		{
			ll val = arr.length();
			ans = min(ans, sum);
			return;
		}
	}
	for (auto &str :map[id])//遍历所有的可以接龙的字符串
	{
		
		if (vis[str.index] > 0)
		{
			vis[str.index]--;
			dfs(str.line, sum + str.line.length() - 1, target, str.line.back(), link+ str.line);
			vis[str.index]++;
		}
			
	}
}
void find_circle(int i)//以第i个航线为起点开始找，先试深度优先
{
	ans = 0x3f3f3f3f;//重置答案
	//重置用于判断的表
	for (int i = 1; i <= n; i++)
	{
		vis[i] = 1;
	}
	char beginandend = lines[i].begin;//终点
	char tar = lines[i].end;
	ll sum = lines[i].whole.size()-1;//长度

	dfs(lines[i].whole,sum,beginandend,tar, lines[i].whole);//最后一位用于不取消遍历判断
	if (ans != 0x3f3f3f3f)
		cout << ans << endl;
	else
		cout << -1<<endl;
}
int main()
{
	cin >> n;
	cin >> aimline;
	for (int i = 1; i <= n; i++)
	{
		cin >> lines[i].whole ;//输入行
		lines[i].begin = lines[i].whole[0];//第一位
		lines[i].end = lines[i].whole.back();//最后一位
		//接下来存入邻接表,都是从1开始,
		int id = lines[i].begin - 'a' + 1;
		group a;
		a.line = lines[i].whole;
		a.index = i;
		map[id].push_back(a);
	}
	//接下来是个检测的函数，实际上要注释掉
	//check_input();
	//接下来要根据具体的字符串遍历，dij算法找最短路,先试深度优先搜索
	for (int i = 1; i <= n; i++)
	{
		find_circle(i);
	}
}