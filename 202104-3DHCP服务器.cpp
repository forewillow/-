#include<iostream>
using namespace std;
struct IP
{
	int time;
	int state;//1:未分配 2:待分配 3:占用 4:过期
	string name;
}ip[10005];//

int n, tdef, tmax, tmin;
string host;
//报文格式：<发送主机> <接收主机> <报文类型> <IP 地址> <过期时刻>
//地址状态有未分配，待分配，占用，过期4种
//待分配和占用状态的IP地址有一个大于0的过期时刻。
//到达过期时刻时，若地址状态是待分配，变为未分配，占用着清空
int main()
{
	cin >> n >> tdef >> tmax >> tmin;
	cin >> host;
	for (int i = 1; i <= n; i++)
	{
		ip[i].state = 1;//全部初始化为未分配状态
	}
	int m;
	cin >> m;
	for (int ii = 1; ii <= m; ii++)
	{
		string shost, rhost, type;
		int seq, ip2, time;
		cin >> seq >> shost >> rhost >> type >> ip2 >> time;
		for (int i = 1; i <= n; i++)
		{
			if (ip[i].state == 2 && ip[i].time <= seq)
			{
				//过期，待分配的状态变为未分配 占有者清空，过期时刻清空
				ip[i].state = 1;
				ip[i].name = "";
				ip[i].time = 0;
			}
			else if (ip[i].state == 3 && ip[i].time <= seq)
			{
				//否则该地址的状态会由占用自动变为过期，且过期时刻清零
				ip[i].state = 4;
				ip[i].time = 0;
			}

            if (rhost == host || rhost == "*" || type == "REQ")
            {
                if (type != "DIS" && type != "REQ") continue;
                if ((rhost == "*" && type != "DIS") || (rhost == host && type == "DIS")) continue;
                if (type == "DIS")
                {
                    int select = -1;
                    for (int i = 1; i <= n; i++)
                        if (ip[i].state != 1 && ip[i].name == shost)
                        {
                            select = i;
                            break;
                        }
                    if (select == -1)
                    {
                        for (int i = 1; i <= n; i++)
                            if (ip[i].state == 1)
                            {
                                select = i;
                                break;
                            }
                    }
                    if (select == -1)
                    {
                        for (int i = 1; i <= n; i++)
                            if (ip[i].state == 4)
                            {
                                select = i;
                                break;
                            }
                    }
                    if (select != -1)
                    {
                        ip[select].state = 2;
                        ip[select].name = shost;

                        if (time == 0) ip[select].time = seq + tdef;
                        else if (tmin <= time - seq && time - seq <= tmax) ip[select].time = time;
                        else if (time - seq < tmin) ip[select].time = seq + tmin;
                        else if (time - seq > tmax) ip[select].time = seq + tmax;
                        cout << host << " " << shost << " OFR " << select << " " << ip[select].time << endl;
                    }
                }
            }
            else if (type == "REQ") 
            {
                if (rhost != host) {
                    for (int i = 1; i <= n; i++)
                        if (ip[i].name == shost && ip[i].state == 2) {
                            ip[i].state = 1;
                            ip[i].name = "";
                            ip[i].time = 0;
                        }
                }
                else 
                {
                    if (1 <= ip2 && ip2 <= n && ip[ip2].name == shost) 
                    {
                        ip[ip2].state = 3;
                        if (time == 0) ip[ip2].time = seq + tdef;
                        else if (tmin <= time - seq && time - seq <= tmax) ip[ip2].time = time;
                        else if (time - seq < tmin) ip[ip2].time = seq + tmin;
                        else if (time - seq > tmax) ip[ip2].time = seq + tmax;
                        cout << host << " " << shost << " ACK " << ip2 << " " << ip[ip2].time << endl;
                    }
                    else
                        cout << host << " " << shost << " NAK " << ip2 << " 0" << endl;
                }
            }
		}
	}
    return 0;
}
