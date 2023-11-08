#include<iostream>
#include<vector>
#include<map>
#include<set>
#include <unordered_map>
#include <utility> 
using namespace std;
const int N = 500005;
const int _right = 0;
const int _up = 1;
const int _left = 2;
const int _down = 3;
struct point
{
	int x, y;
	int k;//k表示斜率
	double a;//折损系数
	int m;//对应的第m次操作，用于删除
};
struct line
{
	int x1, x2, y1, y2;
	int k;
	double a;
	int m;
}del_line[N];
map<int, set<int>> x_map;//x为坐标轴的映射
map<int, set<int>> y_map;//y为坐标轴的映射
map<pair<int, int>, point> point_map;//整个坐标的映射
void reflect(int x, int y, int d, double I, int t)
{
	if (d == _right)//向右，找到相同y的比x大的最小坐标
	{
		//先找出Y的映射
		auto it = y_map[y].upper_bound(x);
		if (it != y_map[y].end() && t >= *it - x)//说明找到了
		{
			point tt = point_map[make_pair(*it, y)];
			if (tt.k == 1) d = _up;
			else if (tt.k == -1) d = _down;
			//经过反射之后，进行下一步判断
			I *= tt.a;//反射损耗
			t -= tt.x - x;
			x = tt.x;
			reflect(x, y, d, I, t);
			return;
		}
		else//没有找到,直接输出当前方向走t后的结果
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x + t << " " << y << " " << final_I << endl;
			return;
		}
	}
	else if (d == _left)//向左，找到相同y的比x大的最小坐标
	{
		//先找出Y的映射
		auto it = y_map[y].lower_bound(x);
		if (it != y_map[y].begin())//说明可以
		{
			it--;
			if (t >= x - *it)
			{
				point tt = point_map[make_pair(*it, y)];
				if (tt.k == -1) d = _up;
				else if (tt.k == 1) d = _down;
				//经过反射之后，进行下一步判断
				I *= tt.a;//反射损耗
				t -= x - tt.x;
				x = tt.x;
				reflect(x, y, d, I, t);
				return;
			}
			else
			{
				int final_I = int(I);
				if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
				else cout << x - t << " " << y << " " << final_I << endl;
				return;
			}
		}
		else//没有找到,直接输出当前方向走t后的结果
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x - t << " " << y << " " << final_I << endl;
			return;
		}
	}
	else if (d == _up)//向上，找到相同x的比y大的最小坐标
	{
		//先找出x的映射
		auto it = x_map[x].lower_bound(y);
		if (it != x_map[x].end() && t >= *it - y)//说明找到了
		{
			point tt = point_map[make_pair(x, *it)];
			if (tt.k == 1) d = _right;
			else if (tt.k == -1) d = _left;
			//经过反射之后，进行下一步判断
			I *= tt.a;//反射损耗
			t -= tt.y - y;
			y = tt.y;
			reflect(x, y, d, I, t);
			return;
		}
		else//没有找到,直接输出当前方向走t后的结果
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x << " " << y + t << " " << final_I << endl;
			return;
		}
	}
	else if (d == _down)//向下
	{
		//先找出x的映射
		auto it = x_map[x].lower_bound(y);
		if (it != x_map[x].begin())//说明找到了
		{
			it--;
			point tt = point_map[make_pair(x, *it)];
			if (t >= y - *it)
			{
				if (tt.k == -1) d = _right;
				else if (tt.k == 1) d = _left;
				//经过反射之后，进行下一步判断
				I *= tt.a;//反射损耗
				t -= y - tt.y;
				y = tt.y;
				reflect(x, y, d, I, t);
				return;
			}
			else
			{
				int final_I = int(I);
				if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
				else cout << x << " " << y - t << " " << final_I << endl;
				return;
			}
		}
		else//没有找到,直接输出当前方向走t后的结果
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x << " " << y - t << " " << final_I << endl;
			return;
		}
	}
}
void print_map()
{
	printf("对x_map来说：\n");
	for (const auto& kv : x_map) {
		int x = kv.first; // 获取键值
		const std::set<int>& pointSet = kv.second; // 获取multiset
		cout << "  x值为" << x << endl;
		// 遍历multiset中的所有元素
		for (const int& ip : pointSet) {
			point p = point_map[make_pair(x, ip)];
			std::cout << "	x=" << p.x << ", y=" << p.y << ", k=" << p.k << ", a=" << p.a << ", m=" << p.m << std::endl;
		}
	}
	cout << endl;
	printf("对y_map来说：\n");
	for (const auto& kv : y_map) {
		int y = kv.first; // 获取键值
		const std::set<int>& pointSet = kv.second; // 获取multiset
		cout << "  y值为" << y << endl;
		// 遍历multiset中的所有元素
		for (const int& ip : pointSet) {
			point p = point_map[make_pair(ip, y)];
			std::cout << "	x=" << p.x << ", y=" << p.y << ", k=" << p.k << ", a=" << p.a << ", m=" << p.m << std::endl;
		}
	}
	cout << "=========================================" << endl;
}
int main()
{
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			int x1, x2, y1, y2;
			double a;
			cin >> x1 >> y1 >> x2 >> y2 >> a;
			int k = (y2 - y1) / (x2 - x1);
			line ll;
			ll.x1 = x1; ll.x2 = x2; ll.y1 = y1; ll.y2 = y2; ll.k = k; ll.a = a; ll.m = i;
			del_line[i] = ll;//存入待删除的line
			if (x1 < x2)
			{
				for (int x = x1 + 1; x < x2; x++)
				{
					int y = k * (x - x1) + y1;
					point ty;
					ty.x = x;
					ty.a = a;
					ty.k = k;
					ty.m = i;
					ty.y = y;
					x_map[x].insert(y);//插入
					y_map[y].insert(x);
					point_map[make_pair(x, y)] = ty;
				}
			}
			else
			{
				for (int x = x2 + 1; x < x1; x++)
				{
					int y = k * (x - x2) + y2;
					point ty;
					ty.x = x;
					ty.a = a;
					ty.k = k;
					ty.m = i;
					ty.y = y;
					x_map[x].insert(y);//插入
					y_map[y].insert(x);
					point_map[make_pair(x, y)] = ty;
				}
			}

		}
		else if (type == 2)
		{
			//可能需要优化，删除所有的K
			int del;
			cin >> del;
			//要找到所有与K匹配的，先找到当前的line
			line tl = del_line[del];
			//删除tl，在x_map,y_map中
			if (tl.x1 < tl.x2)
			{
				for (int x = tl.x1 + 1; x < tl.x2; x++)
				{
					int y = tl.k * (x - tl.x1) + tl.y1;
					point ty;
					ty.x = x;
					ty.a = tl.a;
					ty.k = tl.k;
					ty.m = i;
					ty.y = y;
					x_map[x].erase(y);//删除
					y_map[y].erase(x);

				}
			}
			else
			{
				for (int x = tl.x2 + 1; x < tl.x1; x++)
				{
					int y = tl.k * (x - tl.x1) + tl.y1;
					point ty;
					ty.x = x;
					ty.a = tl.a;
					ty.k = tl.k;
					ty.m = i;
					ty.y = y;
					x_map[x].erase(y);//删除
					y_map[y].erase(x);
				}
			}
		}
		else//输出位置
		{
			int x, y, t, d;
			double  I;
			cin >> x >> y >> d >> I >> t;
			reflect(x, y, d, I, t);
		}
		//print_map();
	}
}
/*10
1 3 0 5 2 0.5
1 2 0 5 3 0.5
1 1 0 4 3 0.5
1 2 2 0 0 0.5
1 0 4 2 2 0.5

2 3
3 3 4 3 1000 5
1 1 0 4 3 0.5
3 4 4 3 1000 7
3 1 2 2 100 10
*/