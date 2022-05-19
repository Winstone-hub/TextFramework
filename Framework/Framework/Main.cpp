// ** Framework v0.4.2
#include "Headers.h"


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

	Object* Bullet = nullptr;

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
				if(Bullet == nullptr)
					Bullet = CreateBullet(Player->TransInfo.Position.x, Player->TransInfo.Position.y);


			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			if(Bullet)
				OnDrawText(Bullet->Info.Texture,
					Bullet->TransInfo.Position.x++,
					Bullet->TransInfo.Position.y);


			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);
		}
	}
	
	return 0;
}
