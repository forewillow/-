#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int M0[8][8];
int M1[8][8];
double M2[8][8];
int a[8][8];
int n, t;
int q[64]={0};
const double PI = acos(-1);
double A(int u)
{
	if (u == 0) return sqrt(0.5);
	else return 1;
}

int main()
{
	//cout << PI;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cin >> a[i][j];
		}
	}
	cin >> n >> t;
	for (int i = 0; i < n; i++)
	{
		cin >> q[i];
	}
	//ÊäÈëÍê³É
	int k = 0;
	int i=0,j=0;
	for (k = 0; k < 64;)
	{
		if (i + j <= 7  && !(i==7&&j==0))
		{
			if (i == 0)
			{
				M0[i][j] = q[k];
				k++; j++;
				while (j != 0)
				{
					
					M0[i][j] = q[k];
					//cout << i << " " << j << " " << k<<endl;
					j--; i++;
					k++;
				}
			}
			else
			{
				M0[i][j] = q[k];
				k++; i++;
				while (i != 0)
				{
					
					M0[i][j] = q[k];
					//cout << i << " " << j << " " << k << endl;
					j++; i--;
					k++;
				}
			}
		}
		else
		{
			if (i == 7)
			{
				//cout << i << " " << j << " " << k << endl;
				M0[i][j] = q[k];
				k++; j++;

				while (j <7)
				{
					
					M0[i][j] = q[k];
					j++; i--;
					k++;
					//cout << i << " " << j << " " << k<< endl;
				}
			}
			else
			{
				//cout << i << " " << j << " " << k << endl;
				M0[i][j] = q[k];
				k++; i++;
				while (i != 7)
				{
					//cout << i << " " << j << " " << k << endl;
					M0[i][j] = q[k];
					j--; i++;
					k++;
				}
			}
		}
	}
	if (t == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << M0[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			M1[i][j] = M0[i][j] * a[i][j];
		}

	}

	if (t == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << M1[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			double ans = 0;
			for (int u = 0; u <= 7; u++)
			{
				for (int v = 0; v <= 7; v++)
				{
					//cout << double(A(u) * A(v)) << endl;
					ans+=(double)0.25*double(M1[u][v])*double(A(u) * A(v) )* cos(PI * (i + 0.5) * double(u) / 8.0) * cos(PI * (j + 0.5) * v / 8.0);
				}
			}
			ans += 128;
			M2[i][j] = round(ans);
			if (M2[i][j] > 255) M2[i][j] = 255;
			if (M2[i][j] < 0) M2[i][j] = 0;
		}
	}
	if (t == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << M2[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
}