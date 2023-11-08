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
	int k;//k��ʾб��
	double a;//����ϵ��
	int m;//��Ӧ�ĵ�m�β���������ɾ��
};
struct line
{
	int x1, x2, y1, y2;
	int k;
	double a;
	int m;
}del_line[N];
map<int, set<int>> x_map;//xΪ�������ӳ��
map<int, set<int>> y_map;//yΪ�������ӳ��
map<pair<int, int>, point> point_map;//���������ӳ��
void reflect(int x, int y, int d, double I, int t)
{
	if (d == _right)//���ң��ҵ���ͬy�ı�x�����С����
	{
		//���ҳ�Y��ӳ��
		auto it = y_map[y].upper_bound(x);
		if (it != y_map[y].end() && t >= *it - x)//˵���ҵ���
		{
			point tt = point_map[make_pair(*it, y)];
			if (tt.k == 1) d = _up;
			else if (tt.k == -1) d = _down;
			//��������֮�󣬽�����һ���ж�
			I *= tt.a;//�������
			t -= tt.x - x;
			x = tt.x;
			reflect(x, y, d, I, t);
			return;
		}
		else//û���ҵ�,ֱ�������ǰ������t��Ľ��
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x + t << " " << y << " " << final_I << endl;
			return;
		}
	}
	else if (d == _left)//�����ҵ���ͬy�ı�x�����С����
	{
		//���ҳ�Y��ӳ��
		auto it = y_map[y].lower_bound(x);
		if (it != y_map[y].begin())//˵������
		{
			it--;
			if (t >= x - *it)
			{
				point tt = point_map[make_pair(*it, y)];
				if (tt.k == -1) d = _up;
				else if (tt.k == 1) d = _down;
				//��������֮�󣬽�����һ���ж�
				I *= tt.a;//�������
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
		else//û���ҵ�,ֱ�������ǰ������t��Ľ��
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x - t << " " << y << " " << final_I << endl;
			return;
		}
	}
	else if (d == _up)//���ϣ��ҵ���ͬx�ı�y�����С����
	{
		//���ҳ�x��ӳ��
		auto it = x_map[x].lower_bound(y);
		if (it != x_map[x].end() && t >= *it - y)//˵���ҵ���
		{
			point tt = point_map[make_pair(x, *it)];
			if (tt.k == 1) d = _right;
			else if (tt.k == -1) d = _left;
			//��������֮�󣬽�����һ���ж�
			I *= tt.a;//�������
			t -= tt.y - y;
			y = tt.y;
			reflect(x, y, d, I, t);
			return;
		}
		else//û���ҵ�,ֱ�������ǰ������t��Ľ��
		{
			int final_I = int(I);
			if (final_I == 0) cout << "0" << " " << "0" << " " << "0" << endl;
			else cout << x << " " << y + t << " " << final_I << endl;
			return;
		}
	}
	else if (d == _down)//����
	{
		//���ҳ�x��ӳ��
		auto it = x_map[x].lower_bound(y);
		if (it != x_map[x].begin())//˵���ҵ���
		{
			it--;
			point tt = point_map[make_pair(x, *it)];
			if (t >= y - *it)
			{
				if (tt.k == -1) d = _right;
				else if (tt.k == 1) d = _left;
				//��������֮�󣬽�����һ���ж�
				I *= tt.a;//�������
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
		else//û���ҵ�,ֱ�������ǰ������t��Ľ��
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
	printf("��x_map��˵��\n");
	for (const auto& kv : x_map) {
		int x = kv.first; // ��ȡ��ֵ
		const std::set<int>& pointSet = kv.second; // ��ȡmultiset
		cout << "  xֵΪ" << x << endl;
		// ����multiset�е�����Ԫ��
		for (const int& ip : pointSet) {
			point p = point_map[make_pair(x, ip)];
			std::cout << "	x=" << p.x << ", y=" << p.y << ", k=" << p.k << ", a=" << p.a << ", m=" << p.m << std::endl;
		}
	}
	cout << endl;
	printf("��y_map��˵��\n");
	for (const auto& kv : y_map) {
		int y = kv.first; // ��ȡ��ֵ
		const std::set<int>& pointSet = kv.second; // ��ȡmultiset
		cout << "  yֵΪ" << y << endl;
		// ����multiset�е�����Ԫ��
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
			del_line[i] = ll;//�����ɾ����line
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
					x_map[x].insert(y);//����
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
					x_map[x].insert(y);//����
					y_map[y].insert(x);
					point_map[make_pair(x, y)] = ty;
				}
			}

		}
		else if (type == 2)
		{
			//������Ҫ�Ż���ɾ�����е�K
			int del;
			cin >> del;
			//Ҫ�ҵ�������Kƥ��ģ����ҵ���ǰ��line
			line tl = del_line[del];
			//ɾ��tl����x_map,y_map��
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
					x_map[x].erase(y);//ɾ��
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
					x_map[x].erase(y);//ɾ��
					y_map[y].erase(x);
				}
			}
		}
		else//���λ��
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