#include <iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;
string after;
vector<int> before;
long long n;
long long index;//λ��
long long all=0;
long long curlen = 0;//��ǰ�Ѿ������ԭʼ���ݳ���
string readbyte(int num)//����16������������
{
	n--;
	string now_byte;
	//char�ͣ�ʵ����Ҫ����ת������int��
	for (int i = 1; i <= num; i++)
	{

		char now1, now2;
		//scanf_s("%c,%c", &now1, &now2);
		cin >> now1 >> now2;//ʵ����now1,now2��ϳ�1���ֽ�
		now_byte+=string(1, now1) + string(1, now2);//ʹ��string�Ĺ��캯��ʵ��
	}
	return now_byte;
}
void back(int o, int l)
{
	int start = after.length() - o * 2;
	int len = o * 2;
	string aim = after.substr(start, len);//�ظ���ȡ���Ӵ�
	l *= 2;//����*2
	int cnt = 0;
	while(cnt<l-l%len)
	{
		after += aim;
		cnt+=len;
	}
	after += aim.substr(0, l % len);
}
int main()
{
	cin >> n;
	string nows;//��ǰ��ȡ���ַ���
	//��Ҫ�ж���û�й�������
	int k=0;

	while ((nows=readbyte(1)) >= "80")//˵��������û������һֱ��ȡ
	{
		//���磬ԭʼ���ݵĳ���Ϊ 1324����ôCk����Ϊ��44��10���� 16 ���Ƶ� 0x2C��0x0A������������ĳ���Ϊ 2���ֽ�����Ϊ 0xAC 0x0A��
		//��������Ҫ���ַ���ת��Ϊ���֣���16����ת��Ϊ10����
		int val = stoi(nows, nullptr, 16);
		val -= 128;
		all += val * pow(128, k);
		k++;
	}
	all += stoi(nows, nullptr, 16) * pow(128, k);
	//cout << all;
	//������ ʵ���������Ľ�ѹ��
	while (all*2!=after.length())//���߸ĳ���Ҳ����������Ҳ�У�
	{
		int llll = after.length();
		nows = readbyte(1);
		int type= stoi(nows, nullptr, 16)%4;
		if (type == 0)//���2λΪ00����ʾ����һ������������Ҫ�жϸ�6λ
		{
			int highval = stoi(nows, nullptr, 16) / 4+1;//ע��+1
			if (highval <= 60)//����������highval���ֽ�
			{
				after += readbyte(highval);//������ô���ֽ�
			}
			else
			{
				highval -= 60;
				int tnum = 0;
				for(int i=0;i<highval;i++)
				{
					tnum += stoi(readbyte(1), nullptr, 16) * pow(256, i);
				}
				after += readbyte(tnum+1);
			}
		}
		else if(type == 1)//01,��ʾ��ʾ����һ���������� ��4<l<11,0<o<2047
		{
			//��˳��Ѻ�8λҲ������
			int low = stoi(readbyte(1), nullptr, 16);
			int o = (stoi(nows, nullptr, 16) / 32)*256+low;
			int l = (stoi(nows, nullptr, 16) / 4) % 8+4;
			back(o, l);
		}
		else if (type == 2)
		{
			//o��ȡ�������ֽ�
			int low = stoi(readbyte(1), nullptr, 16);
			int high = stoi(readbyte(1), nullptr, 16);
			int o = low + 256 * high;
			int l = stoi(nows, nullptr, 16) / 4+1;
			back(o, l);
		}
	}
	for (int i = 0; i < after.length(); i++)
	{
		cout << after[i];
		// �����ÿ16���ַ���һ������
		if ((i + 1) % 16 == 0) cout << endl;
	}
	// �����һ�в��ܴ�8������һ������
	if (after.length() % 16) cout << endl;
	return 0;
}
