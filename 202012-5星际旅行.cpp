#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<int> allans;
typedef long long ll;
const int N = 10e5 + 10;
struct power
{
	ll x;
	ll y;
	ll z;
}po[N+1];
class segment_tree
{
public:
	struct node
	{
		ll l, r;
		power num,lazy;
	}tr[4 * N];//线段树的左右孩子位置和本身的和
	void build(ll p, ll l, ll r)
	{
		tr[p] = { l,r,0 };//先赋孩子值
		if (l == r) { tr[p].num = po[l]; return; }//当为叶子节点，直接赋值为初始值
		build(2 * p, l, (l + r) / 2);
		build(2 * p + 1, (l + r) / 2 + 1, r);//创建左右子树
		tr[p].num.x = tr[2 * p].num.x + tr[2 * p + 1].num.x;
		tr[p].num.y = tr[2 * p].num.y + tr[2 * p + 1].num.y;
		tr[p].num.z = tr[2 * p].num.z + tr[2 * p + 1].num.z;
	}
	void push_down(ll i)
	{
		//把自身的lazy归零，给自己的儿子加上，并且把自己的儿子的值加上k*长度
		if (tr[i].lazy.x|| tr[i].lazy.y|| tr[i].lazy.z)//有懒标记
		{
			tr[i * 2].lazy.x += tr[i].lazy.x;
			tr[i * 2].lazy.y += tr[i].lazy.y;
			tr[i * 2].lazy.z += tr[i].lazy.z;
			tr[i * 2+1].lazy.x += tr[i].lazy.x;
			tr[i * 2+1].lazy.y += tr[i].lazy.y;
			tr[i * 2+1].lazy.z += tr[i].lazy.z;
			ll mid = (tr[i].l + tr[i].r) / 2;
			tr[i * 2].num.x += tr[i].lazy.x * (tr[i * 2].r - tr[i * 2].l + 1);
			tr[i * 2].num.y += tr[i].lazy.y * (tr[i * 2].r - tr[i * 2].l + 1);
			tr[i * 2].num.z += tr[i].lazy.z * (tr[i * 2].r - tr[i * 2].l + 1);

			tr[i * 2 + 1].num.x += tr[i].lazy.x * (tr[i * 2 + 1].r - tr[i * 2 + 1].l + 1);
			tr[i * 2 + 1].num.y += tr[i].lazy.y * (tr[i * 2 + 1].r - tr[i * 2 + 1].l + 1);
			tr[i * 2 + 1].num.z += tr[i].lazy.z * (tr[i * 2 + 1].r - tr[i * 2 + 1].l + 1);
			tr[i].lazy = {0,0,0};
		}
		return;
	}
	void add(ll i, ll l, ll r, power k)
	{
		if (tr[i].r <= r && tr[i].l >= l)//全部覆盖
		{
			tr[i].num.x += k.x* (tr[i].r - tr[i].l + 1);//和乘以长度
			tr[i].num.y += k.y * (tr[i].r - tr[i].l + 1);
			tr[i].num.z += k.z * (tr[i].r - tr[i].l + 1);
			tr[i].lazy.x += k.x;
			tr[i].lazy.y += k.y;
			tr[i].lazy.z += k.z;
			return;
		}
		push_down(i);//完成覆盖后把自身归零
		if (tr[2 * i].r >= l)//左孩子的右侧在目标范围内
		{
			add(i * 2, l, r, k);
		}
		if (tr[2 * i + 1].l <= r)//右孩子的右侧在目标范围内
		{
			add(i * 2 + 1, l, r, k);
		}
		tr[i].num.x = tr[i * 2].num.x + tr[i * 2 + 1].num.x;
		tr[i].num.y = tr[i * 2].num.y + tr[i * 2 + 1].num.y;
		tr[i].num.z = tr[i * 2].num.z+ tr[i * 2 + 1].num.z;
		return;
	}
	inline power search(ll i, ll l, ll r)
	{
		if (tr[i].l >= l && tr[i].r <= r) return tr[i].num;//直接返回值
		if (tr[i].r<l || tr[i].l>r) return {0,0,0};
		push_down(i);
		power s = { 0 ,0,0};
		if (tr[i * 2].r >= l)
		{
			s.x += search(i * 2, l, r).x;
			s.y += search(i * 2, l, r).y;
			s.z += search(i * 2, l, r).z;
		}
		if (tr[i * 2 + 1].l <= r)
		{
			s.x+= search(i * 2 + 1, l, r).x;
			s.y += search(i * 2 + 1, l, r).y;
			s.z += search(i * 2 + 1, l, r).z;
		}
		return s;
	}
}ST;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= N; i++)
	{
		po[i].x = 0;
		po[i].y = 0;
		po[i].z = 0;
	}
	if (n <= 1000)
	{
		for (int ii = 0; ii < m; ii++)
		{
			int type;
			cin >> type;
			int l, r;
			cin >> l >> r;
			if (type == 1)
			{
				//动力增加
				int xx, yy, zz;
				cin >> xx >> yy >> zz;
				for (int i = l; i <= r; i++)
				{
					po[i].x = xx;
					po[i].y = yy;
					po[i].z = zz;

				}
			}
			else if (type == 2)
			{
				//动力增强

				int t;
				cin >> t;
				for (int i = l; i <= r; i++)
				{
					po[i].x *= t;
					po[i].y *= t;
					po[i].z *= t;

				}

			}
			else if (type == 3)
			{
				//动力转向
				for (int i = l; i <= r; i++)
				{
					ll x_to_z = po[i].x;
					po[i].x = po[i].y;
					po[i].y = po[i].z;
					po[i].z = x_to_z;

				}
			}
			else if (type == 4)
			{
				long long xx = 0, yy = 0, zz = 0;
				for (int i = l; i <= r; i++)
				{
					xx += po[i].x % 1000000007;
					yy += po[i].y % 1000000007;
					zz += po[i].z % 1000000007;
				}
				long long ans = (xx * xx % 1000000007 + yy * yy % 1000000007 + zz * zz % 1000000007)% 1000000007;
				cout << ans << endl;
			}
		}
	}
	else
	{
		ST.build(1,1,n);
		for (int ii = 0; ii < m; ii++)
		{
			int type;
			cin >> type;
			if (type == 1)
			{
				ll l, r;
				power k;
				cin >> l >> r >> k.x >> k.y >> k.z;
				ST.add(1, l, r, k);
			}
			else if(type==4)
			{
				ll l, r;
				cin >> l>>r;
				power k = ST.search(1,l, r);
				ll ans = (k.x % 1000000007) * (k.x % 1000000007) + (k.y % 1000000007) * (k.y % 1000000007) + (k.z % 1000000007) * (k.z % 1000000007);
				cout << ans<<endl;
			}
		}
	}
	return 0;
}