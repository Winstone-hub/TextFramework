#pragma once

// ** �ʱ�ȭ �Լ� (����Ʈ �Ű����� : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

// ** �̸��� �����ϴ� �Լ�
char* SetName();

// ** Ŀ���� ��ġ�� ����
void SetCursorPosition(const float _x, const float _y);

// ** Text�� ���� ������.
void SetTextColor(const int _Color);

// ** ����� Text�� ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

// ** ����� ������ ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

// ** Ŀ���� ���̰ų�(true) / �Ⱥ��̰�(false) �������.
void HideCursor(const bool _Visible);

// ** �浹ó���� ��.
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

// ** Bullet�� ������.
Object* CreateBullet(const float _x, const float _y);

// ** Enemy�� ������.
Object* CreateEnemy(const float _x, const float _y);

// ** Ű�Է� 
void UpdateInput(Object* _Object);






// ** �Լ� ���Ǻ�


void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ)
{
	// ** 3�� ������. 
	// ** _Name �� ���� nullptr �̶��  SetName() �Լ��� �����ϰ� �ƴ϶��,
	// ** _Name�� ���� �״�� �����Ѵ�.
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	// ** �̵��ӵ� 
	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ������ ����.)
	_Object->TransInfo.Rotation = Vector3(0.0f, 0.0f, 0.0f);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector3(
		(float)strlen(_Object->Info.Texture), 1.0f, 0.0f);
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

void SetCursorPosition(const float _x, const float _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);
	cout << _Value;
}

void HideCursor(const bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

bool Collision(const Object* _ObjectA, const Object* _ObjectB)
{
	// ** (_Object->TransInfo.Position.x + _Object->TransInfo.Scale.x)   : ����
	// ** _Object->TransInfo.Position.x   : ����
	// ** Rect �浹�� �������� �׻� ũ��.
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
		return true;
	return false;
}

Object* CreateBullet(const float _x, const float _y)
{
	// ** Bullet�� ���� �� �����Ҵ�.
	Object* _Object = new Object;

	// ** �ʱ�ȭ �� _x �� _y �� const ������ �޾ƿ���, �Լ� ���ο��� �ٸ� ������ ���� ���� �ʱ⶧���� �����ϴ�.
	Initialize(_Object, (char*)"��ǳ!", _x + 2, _y);

	return _Object;
}

Object* CreateEnemy(const float _x, const float _y)
{
	// ** Bullet�� ���� �� �����Ҵ�.
	Object* _Object = new Object;

	// ** �ʱ�ȭ �� _x �� _y �� const ������ �޾ƿ���, �Լ� ���ο��� �ٸ� ������ ���� ���� �ʱ⶧���� �����ϴ�.
	Initialize(_Object, (char*)"Ȫ", _x, _y);

	return _Object;
}

void UpdateInput(Object* _Object)
{
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_RIGHT))
		_Object->TransInfo.Position.x += 1;
}
