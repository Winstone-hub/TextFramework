#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


typedef struct tagInfo
{
	int iNumber;

	tagInfo()
	{
		cout << "�⺻ ������" << endl;
	};

	tagInfo(int _iNumber)
	{
		iNumber = _iNumber;
		cout << "���� ������" << endl;
	};

}INFO;



int main(void)
{
	// ** ���
	//printf_s("���� ���");
	//cout << "���� ���";


	// ** �ٹٲ�
	//printf_s("\\n�� ����ϸ�\n�ٹٲ�");
	//cout << "endl �� ����ϸ�" << endl << "�ٹٲ�";



	/*
	// ** �Է�
	int iNumber = 0;
	
	
	//printf_s("�Է�: ");
	//scanf("%d", &iNumber);

	//printf_s("���: %d", iNumber);
	
	cout << "�Է�: ";
	cin >> iNumber;

	cout << "���: " << iNumber;
	*/



	// ** �����Ҵ�
	//INFO* pInfo = (INFO*)malloc(sizeof(INFO));
	//INFO* pInfo = new INFO(10);
	//cout << pInfo->iNumber << endl

	//free(pInfo);
	//delete pInfo;



	INFO* pInfo[10];

	for (int i = 0; i < 10; ++i)
	{
		pInfo[i] = new INFO(i);
		cout << pInfo[i]->iNumber << endl;
	}

	//for (int i = 0; i < 10; ++i)
		//cout << pInfo[i]->iNumber << endl;


	return 0;
}