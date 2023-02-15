#include "Player.h"
#include "DxLib.h"
#include "PadInput.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Player::Player()
{
	location.x = 0;
	location.y = 420;
	image = 0;
	image_size_x = 40;
	image_size_y = 80;
	bullet_count = 0;
	count = 0;
	jump = 10.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	fuel = 100.0;
	gravity_down = 0.0;
	for (int i = 0; i < 30; i++)
	{
		bullet = new Bullet * [30];
		bullet[i] = nullptr;
	}

	beam = nullptr;

	stage = new Stage();


	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Player::~Player()
{
	for (int i = 0; i < 30; i++)
	{
		//delete bullet[i];
	}
	delete[] bullet;
}

//-----------------------------------
// 描画
//-----------------------------------
void Player::Draw() const
{
	DrawBox(location.x, location.y, location.x + image_size_x, location.y + image_size_y, 0x00ff00, TRUE);

	/*for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}*/

	if (beam != nullptr)
	{
		beam->Draw();
	}
	DrawFormatString(0, 0, 0x00ff00, "%f %f", jump_power,fuel);
}

//-----------------------------------
// 更新
//-----------------------------------
void Player::Update()
{
	count++;
	if (PAD_INPUT::GetLStick().x >= 10000)
	{
		location.x += speed_x;
		if (speed_x < 5.0)
		{
			speed_x = speed_x + 0.2;
		}
	}
	else if (PAD_INPUT::GetLStick().x <= -10000)
	{
		location.x += speed_x;
		if (speed_x > -5.0)
		{
			speed_x = speed_x - 0.2;
		}
	}
	else
	{
		if (speed_x > 0)
		{
			speed_x -= 0.2;
		}

		if (speed_x < 0)
		{
			speed_x += 0.2;
		}

		if (speed_x > -0.2 && speed_x < 0.2)
		{
			speed_x = 0;
		}

		location.x += speed_x;
	}

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		Shoot_Gun();
	}


	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B) && fuel > 0)
	{
		not_jet_count = 0;
		jump_power = jump - GRAVITY;

		gravity_down = 0.0;

		jump += 0.25;
		fuel -= 0.25;


		if (jump_power > 10)
		{
			jump_power = 10.0;
		}

		if (fuel < 0)
		{
			fuel = 0;
		}

		if (location.y > 0)
		{
			location.y -= jump_power;
		}
	}
	else
	{
		if (jump_power > 0)
		{
			jump_power -= 0.5;
			if (location.y > 0)
			{
				location.y -= jump_power;
			}
			else
			{
				jump_power = 0;
			}
		}
		else
		{
			jump_power = 0;
			jump = 10;
			location.y += gravity_down;
			gravity_down += 0.25;

			if (location.y > 400)
			{
				location.y = 400;
			}

			if (not_jet_count++ >= 120)
			{
				if (fuel < 100)
				{
					fuel += 2.5;
				}
				else
				{
					fuel = 100;
				}
			}

			if (not_jet_count >= 120)
			{
				not_jet_count = 120;
			}
		}
	}
	 

	for (int i = 0; i < bullet_count; i++)
	{
		/*if (bullet[i]->GetDeleteFlg())
		{
			bullet[i] = nullptr;
			SortBullet(i);
		}
		else
		{
			bullet[i]->Update();
		}*/
	}

	if (beam != nullptr)
	{
		beam->Update(location.x, location.y);
	}

}

//-----------------------------------
// 弾を発射
//-----------------------------------
void Player::Shoot_Gun()
{
	/*if (count % 30 == 0)
	{
		bullet[bullet_count++] = new Bullet(location.x, location.y);
		if (bullet_count >= 30)
		{
			bullet_count = 30;
		}
	}*/

	if (beam == nullptr)
	{
		beam = new EfectBeam();
	}

}

//-----------------------------------
// 弾を並べ替え
//-----------------------------------
void Player::SortBullet(int delete_bullet)
{
	for (int i = delete_bullet + 1; i < 30; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet_count--;
			break;
		}
		if (bullet[i - 1] == nullptr)
		{
			bullet[i - 1] = bullet[i];
			bullet[i] = nullptr;
		}
	}
}