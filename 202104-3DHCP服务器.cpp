#include<iostream>
using namespace std;
struct IP
{
	int time;
	int state;//1:δ���� 2:������ 3:ռ�� 4:����
	string name;
}ip[10005];//

int n, tdef, tmax, tmin;
string host;
//���ĸ�ʽ��<��������> <��������> <��������> <IP ��ַ> <����ʱ��>
//��ַ״̬��δ���䣬�����䣬ռ�ã�����4��
//�������ռ��״̬��IP��ַ��һ������0�Ĺ���ʱ�̡�
//�������ʱ��ʱ������ַ״̬�Ǵ����䣬��Ϊδ���䣬ռ�������
int main()
{
	cin >> n >> tdef >> tmax >> tmin;
	cin >> host;
	for (int i = 1; i <= n; i++)
	{
		ip[i].state = 1;//ȫ����ʼ��Ϊδ����״̬
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
				//���ڣ��������״̬��Ϊδ���� ռ������գ�����ʱ�����
				ip[i].state = 1;
				ip[i].name = "";
				ip[i].time = 0;
			}
			else if (ip[i].state == 3 && ip[i].time <= seq)
			{
				//����õ�ַ��״̬����ռ���Զ���Ϊ���ڣ��ҹ���ʱ������
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
