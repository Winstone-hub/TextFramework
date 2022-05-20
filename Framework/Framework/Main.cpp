// ** Framework v0.5.1
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
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

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
	Enemy[0] = new Object;
	Initialize(Enemy[0], (char*)"Ȫ", 80, 10);

	for (int i = 1; i < 32; ++i)
		Enemy[i] = nullptr;
		

	// ** ���� �ð����� �ʱ�ȭ.
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();

	int Score = 0;

	// ** Bullet
	Object* Bullet[128] = { nullptr };

	int BulletCount = 0;

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


			// ** Enemy ����.
			if (EnemyTime + 1500 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();

				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						/*
						 * �������� �ʱ�ȭ ����. ū ���� ���ü� �ֵ��� Time������ ������ ��������, 
						 * for���� ������ ���ԵǸ� Time�� ���������� ������ �ֱ⶧����,
						 * �������̶�� �ϴ��� �������� ���� ���� ���ü� ����.
						 * i�� ���� ���ϰ� ���������ν� ���� ���� ������ �ʵ��� ����.
						 */
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy(115, rand()%30);
						break;
					}
				}
			}








			// ** ���� : Bullet & Enemy �浹 ����.
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					/*
					if (Collision(Enemy, Bullet[i]))
					{
						delete Bullet[i];
						Bullet[i] = nullptr;

						--BulletCount;
					}
					*/
					
					
					if ((Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x) >= 120)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;

						--BulletCount;
					}
				}
			}

			UpdateInput(Player);

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

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i])
				{
					Enemy[i]->TransInfo.Position.x--;

					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);

					if (Enemy[i]->TransInfo.Position.x <= 0)
					{
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
					Bullet[i]->TransInfo.Position.x += 2;

					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}
			
			OnDrawText((char*)"Bullet Count : ", 95, 1);
			OnDrawText(BulletCount, 95 + strlen("Bullet Count : "), 1);

			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);
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