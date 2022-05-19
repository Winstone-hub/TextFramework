// ** Framework v0.4.1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
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

struct Information
{
	char* Texture;
	int Color;
	int Option;
};

struct Object
{
	char* Name;
	int Speed;

	Information Info;
	Trasnsform TransInfo;
};


struct DrawTextInfo
{
	Information Info;
	Trasnsform TransInfo;
};


// ** 초기화 함수 (디폴트 매개변수 : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// ** 이름을 셋팅하는 함수
char* SetName();

// ** 커서의 위치를 변경
void SetCursorPosition(int _x, int _y);

// ** Text의 색을 변경함.
void SetTextColor(int _Color);

// ** 출력할 Text의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(char* _str, int _x, int _y, int _Color = 15);

// ** 출력할 숫자의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(int _Value, int _x, int _y, int _Color = 15);

// ** 커서를 보이거나(true) / 안보이게(false) 만들어줌.
void HideCursor(bool _Visible);

// ** 충돌처리를 함.
void Collision(Object* _ObjectA, Object* _ObjectB);

// ** 진입점.	
int main(void)
{
	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);


	// ** 배경 초기화.

	DrawTextInfo BackGround[30];

	
	for (int i = 0; i < 30; ++i)
	{
		// ** 랜덤값을 초기화 해줌. 큰 값이 나올수 있도록 Time값끼리 곱해줄 것이지만, 
		// ** for문이 빠르게 돌게되면 Time의 증가값보다 빠를수 있기때문에,
		// ** 랜덤값이라고 하더라도 연속으로 같은 값이 나올수 있음.
		// ** i의 값을 곱하고 더해줌으로써 같은 값이 나오지 않도록 해줌.
		srand((GetTickCount() + i * i) * GetTickCount());


		// ** 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 다았을때에는 충돌하지 않고,
		// ** 총알과 다았을 때에만 충돌판정이 되도록 설정해줄 것임.
		BackGround[i].Info.Option = 0;

		// ** 좌표를 랜덤으로 설정함.
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		// ** 배경으로 사용될 텍스처를 설정.
		BackGround[i].Info.Texture = (char*)"*";

		// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
		BackGround[i].Info.Color = rand() % 8 + 1;
	}


	// ** 플레이어 선언 및 동적할당.
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"옷/", 30, 10);

	// ** Enemy선언 및 동적할당.
	Object* Enemy = new Object;

	// ** Enemy 초기화
	Initialize(Enemy, (char*)"홋", 80, 10);

	// ** 현재 시간으로 초기화.
	ULONGLONG Time = GetTickCount64();

	int Score = 0;

	// ** 출력
	while (true)
	{
		// ** 초기화된 시간으로부터 +50 만큼 증가하면...
		// ** (프레임과 프레임사이의 시간 간격을 0.5초로 셋팅)
		if (Time + 80 < GetTickCount64())
		{
			// ** 증가된 값만큼 다시 초기화.
			Time = GetTickCount64();

			// ** 콘솔창 버퍼 전체 삭제
			system("cls");

			// ** 배경 출력
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}

			// ** [상] 키를 입력받음.
			if (GetAsyncKeyState(VK_UP))
				Player->TransInfo.Position.y -= 1;

			// ** [하] 키를 입력받음.
			if (GetAsyncKeyState(VK_DOWN))
				Player->TransInfo.Position.y += 1;

			// ** [좌] 키를 입력받음.
			if (GetAsyncKeyState(VK_LEFT))
				Player->TransInfo.Position.x -= 1;

			// ** [우] 키를 입력받음.
			if (GetAsyncKeyState(VK_RIGHT))
				Player->TransInfo.Position.x += 1;


			Collision(Player, Enemy);





			// ** [Space] 키를 입력받음.
			if (GetAsyncKeyState(VK_SPACE))
				Player->Info.Texture = (char*)"옷ㅡ";
			else 
				Player->Info.Texture = (char*)"옷/";

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);
		}
	}
	
	return 0;
}
// ** 함수 정의부


void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY, int _PosZ)
{
	// ** 3항 연상자. 
	// ** _Name 의 값이 nullptr 이라면  SetName() 함수를 실행하고 아니라면,
	// ** _Name의 값을 그대로 대입한다.
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	// ** 이동속도 
	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용되지 않음.)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** 크기값
	_Object->TransInfo.Scale = Vector3(
		strlen(_Object->Info.Texture), 1, 0);
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

void HideCursor(bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

void Collision(Object* _ObjectA, Object* _ObjectB)
{
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
		OnDrawText((char*)"충돌 입니다.", 55, 0, 14);
}