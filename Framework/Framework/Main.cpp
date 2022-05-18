// ** Framework v0.3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;


struct Vector3
{
	int x = 0, y = 0, z = 0;

	// ** �⺻ ������
	Vector3() {};

	// ** ���� ������
	Vector3(int _x, int _y)
		: x(_x), y(_y), z(0) { };

	// ** ���� ������
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



// ** �ʱ�ȭ �Լ� (����Ʈ �Ű����� : int _Value = 0)
void Initialize(Object* _Object, char* _Name, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// ** �̸��� �����ϴ� �Լ�
char* SetName();

// ** Ŀ���� ��ġ�� ����
void SetCursorPosition(int _x, int _y);

// ** Text�� ���� ������.
void SetTextColor(int _Color);

// ** ����� Text�� ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(char* _str, int _x, int _y, int _Color = 15);

// ** ����� ������ ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(int _Value, int _x, int _y, int _Color = 15);

// ** ��� �Լ�
void Output(Object* _Object);



// ** ������.
int main(void)
{
	// ** �÷��̾� ���� �� �����Ҵ�.
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, nullptr, 50, 10, 30);

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy = new Object;

	// ** Enemy �ʱ�ȭ
	Initialize(Enemy, (char*)"Enemy", 100, 200, 300);

	// ** �ܼ�â ���� ��ü ����
	system("cls"); 

	// ** ���
	while(true)
		Output(Player);
	//Output(Enemy);

	return 0;
}
// ** �Լ� ���Ǻ�


void Initialize(Object* _Object, char* _Name, int _PosX, int _PosY, int _PosZ)
{
	// ** 3�� ������. 
	// ** _Name �� ���� nullptr �̶��  SetName() �Լ��� �����ϰ� �ƴ϶��,
	// ** _Name�� ���� �״�� �����Ѵ�.
	_Object->Name = (_Name == nullptr) ? SetName() : _Name;

	// ** �̵��ӵ� 
	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ������ ����.)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector3(0, 0, 0);
}

char* SetName()
{
	// ** ���ڿ��� �Է� ���� �ӽ� ������ �迭�� �����Ѵ�. (������ �������� �ٷ� �Է¹����� ����.)
	char Buffer[128] = "";

	// ** �̸� �Է�
	cout << "�Է� : "; cin >> Buffer;

	// ** ������ ������ �����Ͽ� �Է¹��� ���ڿ��� ���̸�ŭ ũ�⸦ �Ҵ���.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** �Է¹��� ���ڿ��� ������ ������.
	strcpy(pName, Buffer);

	// ** ��ȯ
	return pName;
}


void SetCursorPosition(int _x, int _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(char* _str, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(int _Value, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);
	cout << _Value;
}


void Output(Object* _Object)
{
	OnDrawText(_Object->Name,
		_Object->TransInfo.Position.x,
		_Object->TransInfo.Position.y);
}