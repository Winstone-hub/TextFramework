// ** Framework v0.4.3
// ** ���� : Bullet & Enemy �浹 ����.
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
	Object* Enemy = new Object;

	// ** Enemy �ʱ�ȭ
	Initialize(Enemy, (char*)"Ȫ", 80, 10);

	// ** ���� �ð����� �ʱ�ȭ.
	ULONGLONG Time = GetTickCount64();

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

			

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					if ((Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x) >= 120)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;

						--BulletCount;
					}
				}
			}

			Collision(Player, Enemy);

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

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

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



// ** ������ (�� : ����)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]