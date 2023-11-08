
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const int N = 500005;
double points[N][2] = { 0 };
int main()
{
    int n, p;
    cin >> n >> p;

    for (int i = 1; i <= n; i++)
    {
        cin >> points[i][0] >> points[i][1];
    }
    for (int ii = 0; ii < p; ii++)
    {
        int type;
        cin >> type;
        int l, r;
        cin >> l >> r;
        if (type == 1)
        {
            double a, b;
            cin >> a >> b;
            for (int i = l; i <= r; i++)
            {
                points[i][0] += a;
                points[i][1] += b;
            }
        }
        else if (type == 2)
        {
            double a, b, s;
            cin >> a >> b >> s;
            for (int i = l; i <= r; i++)
            {
                double x = points[i][0] - a, y = points[i][1] - b;
                double d = sqrt(x * x + y * y);//¾àÀë
                double r = atan2(y, x) + s;
                points[i][0] = d * cos(r) + a;
                points[i][1] = d * sin(r) + b;
            }
        }
        else if (type == 3)
        {
            double a, b, s;
            cin >> a >> b >> s;
            for (int i = l; i <= r; i++)
            {
                double x = points[i][0] - a, y = points[i][1] - b;
                x *= s; y *= s;
                points[i][0] = x + a; points[i][1] = y + b;
            }
        }
        else if (type == 4)
        {
            double r1, y0;
            cin >> r1 >> y0;
            for (int i = l; i <= r; i++)
            {
                double x = points[i][0];
                double y = points[i][1] - y0;
                double d = sqrt(x * x + y * y);
                double rr = 2 * r1 - atan2(y, x);
                points[i][0] = d * cos(rr);
                points[i][1] = d * sin(rr) + y0;
            }
        }
        else if (type == 5)
        {
            double r1, y0;
            cin >> r1 >> y0;
            for (int i = l; i <= r; i++)
            {
                double x = points[i][0];
                double y = points[i][1] - y0;
                double ra = atan2(y, x) - r1;
                double d = sqrt(x * x + y * y) * cos(ra);
                points[i][0] = d * cos(r1);
                points[i][0] = d * sin(r1) + y0;
            }

        }
        else if (type == 6)
        {
            double x = 0, y = 0;
            for (int i = l; i <= r; i++)
            {
                x += points[i][0];
                y += points[i][1];
            }
            x /= (r - l + 1);
            y /= (r - l + 1);
            printf("%.6llf %.6llf\n", x, y);
        }
        else if (type == 7)
        {
            double a, b;
            cin >> a >> b;
            double ans = 0;
            for (int i = l; i <= r; i++)
            {
                ans += (points[i][0] - a) * (points[i][0] - a) + (points[i][1] - b) * (points[i][1] - b);
            }
            printf("%.6llf\n", ans);
        }
    }
    return 0;
}