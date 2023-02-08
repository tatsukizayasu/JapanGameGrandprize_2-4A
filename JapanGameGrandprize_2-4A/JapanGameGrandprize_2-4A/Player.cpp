#include "Player.h"
#include "DxLib.h"
#include "PadInput.h"


Player::Player()
{
	location.x = 0;
	location.y = 420;
	image = 0;
	image_size_x = 40;
	image_size_y = 80;
	bullet_count = 0;
	count = 0;
	jump = 10;
	jump_power = 0;
	for (int i = 0; i < 30; i++)
	{
		bullet = new BULLET * [30];
		bullet[i] = nullptr;
	}
	//GetGraphSize(image, &image_size_x, &image_size_y);
}

Player::~Player()
{
	for (int i = 0; i < 30; i++)
	{
		delete bullet[i];
	}
	delete[] bullet;
}

void Player::Draw() const
{
	DrawBox(location.x, location.y, location.x + image_size_x, location.y + image_size_y, 0x00ff00, TRUE);

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}
}

void Player::Update()
{	
	if (PAD_INPUT::GetLStick().x >= 10000)
	{
		location.x += 5;
	}
	else if (PAD_INPUT::GetLStick().x <= -10000)
	{
		location.x -= 5;
	}

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B))
	{
		jump_power = jump - GRAVITY;
		jump++;

		if (jump > 10)
		{
			jump = 10;
		}

		if (location.y > 0)
		{
			location.y -= jump;
		}
	}
	else
	{
		location.y += GRAVITY;
		if (location.y > 600)
		{
			location.y = 600;
		}
	}

	Shoot_Gun();
}

void Player::Shoot_Gun()
{
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		if (count % 30 == 0)
		{
			bullet[bullet_count++] = new BULLET(location.x, location.y);
			if (bullet_count >= 30)
			{
				bullet_count = 30;
			}
		}
		count++;
	}

	for (int i = 0; i < bullet_count; i++)
	{

			if (bullet[i]->GetDeleteFlg())
			{
				bullet[i] = nullptr;
			}
			else
			{
				bullet[i]->Update();
			}
	}

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] == nullptr && bullet[i + 1] != nullptr)
		{
			bullet[i] = bullet[i + 1];
			bullet[i + 1] = nullptr;
		}
	}
	if (bullet[bullet_count - 1] == nullptr && bullet_count > 0)
	{
		bullet_count--;
	}
}