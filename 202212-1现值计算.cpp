#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n;
	double i;
	double sum = 0;
	double val;
	scanf("%d %lf", &n, &i);
	for (int j = 0; j <= n; j++)
	{
		sum *= (1+i);
		scanf("%lf", &val);
		sum += val;
	}
	sum /= powl(1 + i, n);
	printf("%.3f", sum);
}