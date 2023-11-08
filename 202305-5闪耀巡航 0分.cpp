#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const int N = 100009;
ll n;
string aimline;//Ŀ��,�����10���ص�
//��Ҫ�洢��ͷ��ĸ�ͽ�β��ĸ
//��Ҫ�����ڽӱ�
//��������Ҫ�����ַ�������
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
vector<group> map[27];//��ͷ��a��z
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
			return false;//˵��û�ҵ�
		}
	}
	return true;
}
void dfs(string arr,ll sum,char target,char linkchar,string link)//�ֱ��ʾ ��·�ܳ��ȣ�Ŀ�ĵأ����ӵ���ĸ
{
	//cout << "��ǰΪ" << arr << " ";
	//cout << "������" << link << " "<<"����Ϊ"<<sum<<endl;
	int id = linkchar - 'a' + 1;
	if (linkchar == target)//�������
	{
		if (allValuesAreZero(link))//�ɹ���
		{
			ll val = arr.length();
			ans = min(ans, sum);
			return;
		}
	}
	for (auto &str :map[id])//�������еĿ��Խ������ַ���
	{
		
		if (vis[str.index] > 0)
		{
			vis[str.index]--;
			dfs(str.line, sum + str.line.length() - 1, target, str.line.back(), link+ str.line);
			vis[str.index]++;
		}
			
	}
}
void find_circle(int i)//�Ե�i������Ϊ��㿪ʼ�ң������������
{
	ans = 0x3f3f3f3f;//���ô�
	//���������жϵı�
	for (int i = 1; i <= n; i++)
	{
		vis[i] = 1;
	}
	char beginandend = lines[i].begin;//�յ�
	char tar = lines[i].end;
	ll sum = lines[i].whole.size()-1;//����

	dfs(lines[i].whole,sum,beginandend,tar, lines[i].whole);//���һλ���ڲ�ȡ�������ж�
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
		cin >> lines[i].whole ;//������
		lines[i].begin = lines[i].whole[0];//��һλ
		lines[i].end = lines[i].whole.back();//���һλ
		//�����������ڽӱ�,���Ǵ�1��ʼ,
		int id = lines[i].begin - 'a' + 1;
		group a;
		a.line = lines[i].whole;
		a.index = i;
		map[id].push_back(a);
	}
	//�������Ǹ����ĺ�����ʵ����Ҫע�͵�
	//check_input();
	//������Ҫ���ݾ�����ַ���������dij�㷨�����·,���������������
	for (int i = 1; i <= n; i++)
	{
		find_circle(i);
	}
}