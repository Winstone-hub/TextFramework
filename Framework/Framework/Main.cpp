// ** Framework v0.6.1
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
		BackGround[i].TransInfo.Position.x = float(rand() % 100 + 10);
		BackGround[i].TransInfo.Position.y = float(rand() % 26 + 1);

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
	Object* Enemy[32]; //= new Object;

	// ** Enemy 초기화
	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;
		

	// ** 현재 시간으로 초기화.
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();

	int Score = 0;

	// ** Bullet
	Object* Bullet[128] = { nullptr };

	int BulletCount = 0;



	// ** Test
	Object* Temp = nullptr;
	Vector3 Direction;


	bool Check = false;





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

			/*
			// ** Enemy 생성.
			if (EnemyTime + 1500 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();

				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						
						// ** 랜덤값을 초기화 해줌. 큰 값이 나올수 있도록 Time값끼리 곱해줄 것이지만, 
						// ** for문이 빠르게 돌게되면 Time의 증가값보다 빠를수 있기때문에,
						// ** 랜덤값이라고 하더라도 연속으로 같은 값이 나올수 있음.
						// ** i의 값을 곱하고 더해줌으로써 같은 값이 나오지 않도록 해줌.
						 
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy(115, rand()%30);
						break;
					}
				}
			}
			*/

			// ** 숙제 : Bullet & Enemy 충돌 구현.
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					for (int j = 0; j < 32; ++j)
					{
						if (Enemy[j] != nullptr)
						{
							if (Collision(Enemy[j], Bullet[i]))
							{
								delete Enemy[j];
								Enemy[j] = nullptr;

								delete Bullet[i];
								Bullet[i] = nullptr;
								break;
							}
						}
					}

					if (Bullet[i] != nullptr)
						if ((Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x) >= 120)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;
						}
				}
			}

			// ** 키 입력
			UpdateInput(Player);





			

			// ** 버튼을 눌럿을때
			if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				Temp = new Object;

				Temp->TransInfo.Position.x = float(rand() % 120);
				Temp->TransInfo.Position.y = float(rand() % 30);

				Temp->Info.Texture = (char*)"★";

				Temp->Speed = 0;

				Check = true;
			}

			// ** 버튼을 누르고 있을때
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if(Temp->Speed < 10)
					Temp->Speed++;

				//OnDrawText((char*)"|", 1.0f + Temp->Speed, 28.0f);
			}

			// ** 버튼을 누르지 않은 상태.
			if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				// ** Temp가 Player로 이동하기 위해 방향을 받아옴.
				Direction = GetDirection(Player, Temp);

				Check = false;
			}


			/*
			// ** [Space] 키를 입력받음.
			if (GetAsyncKeyState(VK_SPACE))
				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreateBullet(
							Player->TransInfo.Position.x,
							Player->TransInfo.Position.y);
						++BulletCount;
						break;
					}
				}
			*/

			// ** Player 출력
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			// ** Temp 출력
			if (Temp)
			{
				OnDrawText(Temp->Info.Texture,
					Temp->TransInfo.Position.x,
					Temp->TransInfo.Position.y,
					12);

				// ** 해당 방향으로 이동함.
				Temp->TransInfo.Position.x += 1 * Temp->Speed;
				//Temp->TransInfo.Position.y += Direction.y * Temp->Speed;

				// ** 거리를 출력.
				OnDrawText((char*)"Length : ", float(60 - strlen("Score : ")), 2.0f);
				OnDrawText((int)GetDistance(Player, Temp), 60.0f, 2.0f);

				if (Temp->TransInfo.Position.x >= 118)
				{
					delete Temp;
					Temp = nullptr;
				}
			}

			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i])
				{
					// ** Enemy 이동
					Enemy[i]->TransInfo.Position.x--;

					// **Enemy 출력
					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);

					// ** Enemy 스크린 충돌
					if (Enemy[i]->TransInfo.Position.x <= 0)
					{
						// ** 충돌하면 삭제
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
			}

			// ** Bullet 출력
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					// ** Bullet 이동
					Bullet[i]->TransInfo.Position.x += 2;

					// ** Bullet 출력
					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}

			// ** Score 출력
			OnDrawText((char*)"Score : ",float( 60 - strlen("Score : ")), 1.0f);
			OnDrawText(++Score, 60.0f, 1.0f);

			OnDrawText((char*)"[          ]", 1.0f, 28.0f);
		}
	}
	
	return 0;
}



// ** 게이지 (월요일 : 예정)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]