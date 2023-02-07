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
	for (int i = 0; i < 30; i++)
	{
		bullet[i] = nullptr;
	}
	//GetGraphSize(image, &image_size_x, &image_size_y);
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
		location.y -= 5;
	}
	else if (location.y >= 500)
	{
		location.y += 5;
	}

	Shoot_Gun();
}

void Player::Shoot_Gun()
{
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		bullet[bullet_count++] = new BULLET(location.x,location.y);
		if (bullet_count >= 30)
		{
			bullet_count = 30;
		}
	}

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i]->GetDeleteFlg())
		{
			delete bullet[i];
		}
		else
		{
			bullet[i]->Update();
		}
	}

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet[i] = bullet[i + 1];
			delete bullet[i + 1];
			bullet_count--;
		}
	}
}