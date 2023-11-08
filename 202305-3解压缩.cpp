#include <iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;
string after;
vector<int> before;
long long n;
long long index;//位置
long long all=0;
long long curlen = 0;//当前已经保存的原始数据长度
string readbyte(int num)//按照16进制来读数据
{
	n--;
	string now_byte;
	//char型，实际上要把它转换换成int型
	for (int i = 1; i <= num; i++)
	{

		char now1, now2;
		//scanf_s("%c,%c", &now1, &now2);
		cin >> now1 >> now2;//实际上now1,now2组合成1个字节
		now_byte+=string(1, now1) + string(1, now2);//使用string的构造函数实现
	}
	return now_byte;
}
void back(int o, int l)
{
	int start = after.length() - o * 2;
	int len = o * 2;
	string aim = after.substr(start, len);//重复读取的子串
	l *= 2;//长度*2
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
	string nows;//当前读取的字符串
	//先要判断有没有过引导域
	int k=0;

	while ((nows=readbyte(1)) >= "80")//说明引导域还没结束，一直读取
	{
		//例如，原始数据的长度为 1324，那么Ck依次为：44、10，即 16 进制的 0x2C、0x0A。因此引导区的长度为 2，字节序列为 0xAC 0x0A。
		//接下来需要将字符串转化为数字，将16进制转化为10进制
		int val = stoi(nows, nullptr, 16);
		val -= 128;
		all += val * pow(128, k);
		k++;
	}
	all += stoi(nows, nullptr, 16) * pow(128, k);
	//cout << all;
	//接下来 实现数据区的解压缩
	while (all*2!=after.length())//或者改成再也读不到数据也行？
	{
		int llll = after.length();
		nows = readbyte(1);
		int type= stoi(nows, nullptr, 16)%4;
		if (type == 0)//最低2位为00，表示这是一个字面量，需要判断高6位
		{
			int highval = stoi(nows, nullptr, 16) / 4+1;//注意+1
			if (highval <= 60)//接下来读入highval个字节
			{
				after += readbyte(highval);//加上这么多字节
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
		else if(type == 1)//01,表示表示这是一个回溯引用 ，4<l<11,0<o<2047
		{
			//先顺便把后8位也都进来
			int low = stoi(readbyte(1), nullptr, 16);
			int o = (stoi(nows, nullptr, 16) / 32)*256+low;
			int l = (stoi(nows, nullptr, 16) / 4) % 8+4;
			back(o, l);
		}
		else if (type == 2)
		{
			//o读取后两个字节
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
		// 输出，每16个字符加一个换行
		if ((i + 1) % 16 == 0) cout << endl;
	}
	// 若最后一行不能凑8个，则补一个换行
	if (after.length() % 16) cout << endl;
	return 0;
}
