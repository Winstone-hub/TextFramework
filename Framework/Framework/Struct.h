#pragma once

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