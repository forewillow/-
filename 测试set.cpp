#include<iostream>
#include<vector>
#include<map>
#include<set>
#include <unordered_map>
using namespace std;
struct point
{
	int x, y;
};
struct CompareByY //根据y值大小排序
{
	bool operator()(const point& p1, const point& p2) const
	{
		return p1.y < p2.y;
	}
};
unordered_map<int, set<point, CompareByY>> x_map;//x为坐标轴的映射
int main()
{
	for (int i = 199; i >=0; i -= 2)
	{
		x_map[1].insert({ i/2,i });
	}
	//现在找55
	auto it = x_map[1].upper_bound({0,200});
	cout << (--it)->y;
}
/*10
1 3 0 5 2 0.5
1 2 0 5 3 0.5
1 1 0 4 3 0.5
1 2 2 0 0 0.5
1 0 4 2 2 0.5

2 3
3 3 4 3 100 5
1 1 0 4 3 0.5
3 4 4 3 100 7
3 1 2 2 10 10
*/