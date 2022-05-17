// ** Framework v0.2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;


struct Vector3
{
	int x = 0, y = 0, z = 0;

	// ** 기본 생성자
	Vector3() {};

	// ** 복사 생성자
	Vector3(int _x, int _y)
		: x(_x), y(_y), z(0) { };

	// ** 복사 생성자
	Vector3(int _x, int _y, int _z)
		: x(_x), y(_y), z(_z) { };
};

struct Trasnsform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
};

struct Object
{
	char* Name;
	int Speed;
	Trasnsform TransInfo;
};



// ** 초기화 함수
void Initialize(Object* _Object, char* _Name, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// ** 이름을 셋팅하는 함수
char* SetName();

// ** 출력 함수
void Output(Object* _Object);



// ** 진입점.
int main(void)
{
	// ** 플레이어 선언 및 동적할당.
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, nullptr, 10, 20, 30);

	// ** Enemy선언 및 동적할당.
	Object* Enemy = new Object;

	// ** Enemy 초기화
	Initialize(Enemy, (char*)"Enemy", 100, 200, 300);


	// ** 출력
	Output(Player);
	Output(Enemy);

	return 0;
}
// ** 함수 정의부


void Initialize(Object* _Object, char* _Name, int _PosX, int _PosY, int _PosZ)
{
	// ** 3항 연상자. 
	// ** _Name 의 값이 nullptr 이라면  SetName() 함수를 실행하고 아니라면,
	// ** _Name의 값을 그대로 대입한다.
	_Object->Name = (_Name == nullptr) ? SetName() : _Name;

	// ** 이동속도 
	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용되지 않음.)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** 크기값
	_Object->TransInfo.Scale = Vector3(0, 0, 0);
}

char* SetName()
{
	// ** 문자열을 입력 받을 임시 변수를 배열로 생성한다. (포인터 변수에는 바로 입력받을수 없음.)
	char Buffer[128] = "";

	// ** 이름 입력
	cout << "입력 : "; cin >> Buffer;

	// ** 포인터 변수을 선언하여 입력받은 문자열의 길이만큼 크기를 할당함.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** 입력받은 문자열의 내용을 복사함.
	strcpy(pName, Buffer);

	// ** 반환
	return pName;
}

void Output(Object* _Object)
{
	if (_Object->Name != nullptr)
		cout << "Name : " << _Object->Name << endl;

	cout << "Speed : " << _Object->Speed << endl;

	cout << "X : " << _Object->TransInfo.Position.x <<
		",  Y : " << _Object->TransInfo.Position.y <<
		",  Z : " << _Object->TransInfo.Position.z << endl;
}