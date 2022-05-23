// ** Framework v0.6.1
#include "Headers.h"




// ** ������.	
int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);


	// ** ��� �ʱ�ȭ.
	DrawTextInfo BackGround[30];

	for (int i = 0; i < 30; ++i)
	{
		// ** �������� �ʱ�ȭ ����. ū ���� ���ü� �ֵ��� Time������ ������ ��������, 
		// ** for���� ������ ���ԵǸ� Time�� ���������� ������ �ֱ⶧����,
		// ** �������̶�� �ϴ��� �������� ���� ���� ���ü� ����.
		// ** i�� ���� ���ϰ� ���������ν� ���� ���� ������ �ʵ��� ����.
		srand((GetTickCount() + i * i) * GetTickCount());


		// ** ���� ��� ������� ������ �ʾ�����, ���� ���� �Ѿ��� �������� �÷��̾ ���� �پ��������� �浹���� �ʰ�,
		// ** �Ѿ˰� �پ��� ������ �浹������ �ǵ��� �������� ����.
		BackGround[i].Info.Option = 0;

		// ** ��ǥ�� �������� ������.
		BackGround[i].TransInfo.Position.x = float(rand() % 100 + 10);
		BackGround[i].TransInfo.Position.y = float(rand() % 26 + 1);

		// ** ������� ���� �ؽ�ó�� ����.
		BackGround[i].Info.Texture = (char*)"*";

		// ** ������� ���� �ؽ�ó�� ������ �������� ����.
		BackGround[i].Info.Color = rand() % 8 + 1;
	}


	// ** �÷��̾� ���� �� �����Ҵ�.
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"��/", 30, 10);

	// ** Enemy���� �� �����Ҵ�.
	Object* Enemy[32]; //= new Object;

	// ** Enemy �ʱ�ȭ
	for (int i = 0; i < 32; ++i)
		Enemy[i] = nullptr;
		

	// ** ���� �ð����� �ʱ�ȭ.
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





	// ** ���
	while (true)
	{
		// ** �ʱ�ȭ�� �ð����κ��� +50 ��ŭ �����ϸ�...
		// ** (�����Ӱ� �����ӻ����� �ð� ������ 0.5�ʷ� ����)
		if (Time + 80 < GetTickCount64())
		{
			// ** ������ ����ŭ �ٽ� �ʱ�ȭ.
			Time = GetTickCount64();

			// ** �ܼ�â ���� ��ü ����
			system("cls");

			// ** ��� ���
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** ������� ���� �ؽ�ó�� ������ �������� ����.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}

			/*
			// ** Enemy ����.
			if (EnemyTime + 1500 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();

				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						
						// ** �������� �ʱ�ȭ ����. ū ���� ���ü� �ֵ��� Time������ ������ ��������, 
						// ** for���� ������ ���ԵǸ� Time�� ���������� ������ �ֱ⶧����,
						// ** �������̶�� �ϴ��� �������� ���� ���� ���ü� ����.
						// ** i�� ���� ���ϰ� ���������ν� ���� ���� ������ �ʵ��� ����.
						 
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy(115, rand()%30);
						break;
					}
				}
			}
			*/

			// ** ���� : Bullet & Enemy �浹 ����.
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

			// ** Ű �Է�
			UpdateInput(Player);





			

			// ** ��ư�� ��������
			if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				Temp = new Object;

				Temp->TransInfo.Position.x = float(rand() % 120);
				Temp->TransInfo.Position.y = float(rand() % 30);

				Temp->Info.Texture = (char*)"��";

				Temp->Speed = 0;

				Check = true;
			}

			// ** ��ư�� ������ ������
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if(Temp->Speed < 10)
					Temp->Speed++;

				//OnDrawText((char*)"|", 1.0f + Temp->Speed, 28.0f);
			}

			// ** ��ư�� ������ ���� ����.
			if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				// ** Temp�� Player�� �̵��ϱ� ���� ������ �޾ƿ�.
				Direction = GetDirection(Player, Temp);

				Check = false;
			}


			/*
			// ** [Space] Ű�� �Է¹���.
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

			// ** Player ���
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			// ** Temp ���
			if (Temp)
			{
				OnDrawText(Temp->Info.Texture,
					Temp->TransInfo.Position.x,
					Temp->TransInfo.Position.y,
					12);

				// ** �ش� �������� �̵���.
				Temp->TransInfo.Position.x += 1 * Temp->Speed;
				//Temp->TransInfo.Position.y += Direction.y * Temp->Speed;

				// ** �Ÿ��� ���.
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
					// ** Enemy �̵�
					Enemy[i]->TransInfo.Position.x--;

					// **Enemy ���
					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);

					// ** Enemy ��ũ�� �浹
					if (Enemy[i]->TransInfo.Position.x <= 0)
					{
						// ** �浹�ϸ� ����
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
			}

			// ** Bullet ���
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					// ** Bullet �̵�
					Bullet[i]->TransInfo.Position.x += 2;

					// ** Bullet ���
					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}

			// ** Score ���
			OnDrawText((char*)"Score : ",float( 60 - strlen("Score : ")), 1.0f);
			OnDrawText(++Score, 60.0f, 1.0f);

			OnDrawText((char*)"[          ]", 1.0f, 28.0f);
		}
	}
	
	return 0;
}



// ** ������ (������ : ����)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]