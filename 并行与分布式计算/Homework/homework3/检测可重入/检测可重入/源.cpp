#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{ //��string.find��ʵ������û��defind\@��
	fstream file("test.ll");
	string line;
	bool reentrant = true;//��־�Ƿ������
	if (file)
	{
		bool inside = false;//�Ƿ���뺯��
		while (getline(file, line))
		{
			if (inside == false)//���ں�����
			{
				if (line.find("define") != line.npos)
					inside = true;
			}
			else//�Ѿ����뺯����
			{
				if (line == "}")//���ﺯ��β��
					inside = false;
				else if(line.find("call")!=line.npos)//������������Щ����
				{
					if (line.find("@printf") != line.npos || line.find("@scanf")!=line.npos ||line.find("@puts") != line.npos || 
						line.find("@gets") != line.npos ||line.find("@malloc") != line.npos || line.find("@new") != line.npos ||
						line.find("@free") != line.npos)
					{
						reentrant = false;
					}
				}
				else//û�е���������������ٿռ�Ⱥ���,���ж�����ȫ�ֱ���
				{
					if (line.find("@")!=line.npos)
						reentrant = false;
				}
			}
		}
		if (reentrant)
			cout << "�����в����ڲ�������ĺ���" << endl;
		else
			cout<< "�����д��ڲ�������ĺ���" << endl;
	}
	else
	{
		cout << "No such file!" << endl;
	}
	system("pause");
	return 0;
}