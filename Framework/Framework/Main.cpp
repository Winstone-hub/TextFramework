#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


typedef struct tagInfo
{
	int iNumber;

	tagInfo()
	{
		cout << "기본 생성자" << endl;
	};

	tagInfo(int _iNumber)
	{
		iNumber = _iNumber;
		cout << "복사 생성자" << endl;
	};

}INFO;



int main(void)
{
	// ** 출력
	//printf_s("문자 출력");
	//cout << "문자 출력";


	// ** 줄바꿈
	//printf_s("\\n을 사용하면\n줄바꿈");
	//cout << "endl 을 사용하면" << endl << "줄바꿈";



	/*
	// ** 입력
	int iNumber = 0;
	
	
	//printf_s("입력: ");
	//scanf("%d", &iNumber);

	//printf_s("출력: %d", iNumber);
	
	cout << "입력: ";
	cin >> iNumber;

	cout << "출력: " << iNumber;
	*/



	// ** 동적할당
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