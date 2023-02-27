#include "Player.h"
#include "DxLib.h"
#include "NormalBullet.h"
#include "PadInput.h"
#include "CameraWork.h"
#include "Item.h"
#include <iostream>

//プレイヤーが持っている元素の種類
#define PLAYER_ELEMENT 7

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
	area.width = image_size_x;
	area.height = image_size_y;
	bullet_count = 0;
	count = 0;
	damage_count = 0;
	jump = 10.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	fuel = 100.0;
	gravity_down = 0.0;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = new BulletBase * [BULLET_MAX];
		bullet[i] = nullptr;
	}

	damage_flg = false;
	i = 0;

	attribute[0] = ATTRIBUTE::NORMAL;
	attribute[1] = ATTRIBUTE::EXPLOSION;
	attribute[2] = ATTRIBUTE::MELT;
	attribute[3] = ATTRIBUTE::POISON;
	attribute[4] = ATTRIBUTE::PARALYSIS;
	attribute[5] = ATTRIBUTE::HEAL;

	attribute_c[0] = "NORMAL";
	attribute_c[1] = "EXPLOSION";
	attribute_c[2] = "MELT";
	attribute_c[3] = "POISON";
	attribute_c[4] = "PARALYSIS";
	attribute_c[5] = "HEAL";


	player_state = PLAYER_STATE::STOP;

	display_attribute = 0;

	hp = 0;

	beam = nullptr;

	stage = nullptr;



	//元素の初期化
	element = new ElementItem * [PLAYER_ELEMENT];
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
	}

	pouch = nullptr;

	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// コンストラクタ
//-----------------------------------
Player::Player(Stage* stage)
{

	area.height = 80;
	area.width = 40;

	this->stage = stage;
	location.x = 0;
	location.y = 1220;
	image = 0;
	image_size_x = 40;
	image_size_y = 80;
	area.width = image_size_x;
	area.height = image_size_y;
	bullet_count = 0;
	damage_count = 0;
	count = 0;
	jump = 10.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	fuel = 100.0;
	gravity_down = 0.0;
	bullet = new BulletBase * [BULLET_MAX];
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i] = nullptr;
	}

	damage_flg = false;
	pouch_open = false;
	i = 0;

	attribute[0] = ATTRIBUTE::NORMAL;
	attribute[1] = ATTRIBUTE::EXPLOSION;
	attribute[2] = ATTRIBUTE::MELT;
	attribute[3] = ATTRIBUTE::POISON;
	attribute[4] = ATTRIBUTE::PARALYSIS;
	attribute[5] = ATTRIBUTE::HEAL;

	attribute_c[0] = ("NORMAL");
	attribute_c[1] = ("EXPLOSION");
	attribute_c[2] = ("MELT");
	attribute_c[3] = ("POISON");
	attribute_c[4] = ("PARALYSIS");
	attribute_c[5] = ("HEAL");


	for (int i = 0; i < 6; i++)
	{
		attribute_c[i] = i;
	}

	player_state = PLAYER_STATE::STOP;

	display_attribute = 0;

	hp = 100;

	beam = nullptr;

	pouch = new Pouch();

	stage = new Stage();

	area = { 80,40 };

	//元素の初期化
	element = new ElementItem * [PLAYER_ELEMENT];
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
	}
	//GetGraphSize(image, &image_size_x, &image_size_y);
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Player::~Player()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		delete bullet[i];
	}
	delete[] bullet;
}

//-----------------------------------
// 描画
//-----------------------------------
void Player::Draw() const
{

	float x = location.x - CameraWork::GetCamera().x;
	float y = location.y - CameraWork::GetCamera().y;

	DrawBox(x - (area.width / 2), y - (area.height / 2), x - (area.width / 2) + area.width, y - (area.height / 2) + area.height, 0x00ff00, TRUE);


	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}

	//if (beam != nullptr)
	//{
	//	beam->Draw();
	//}
	DrawFormatString(0, 0, 0x00ff00, "%f %f", jump_power, fuel);


	//ダメージを受けた時点滅する
	if (damage_flg)
	{
		if (damage_count < 5)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			DrawBox(x, y, x + image_size_x, y + image_size_y, 0x00ff00, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else if (10 < damage_count < 10)
		{
			DrawBox(x, y, x + image_size_x, y + image_size_y, 0x00ff00, TRUE);
		}
	}
	else
	{
	}

#ifdef _DEBUG
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		DrawFormatString(20 * i, 100, 0x000000, "%d", element[i]->GetVolume());
	}

#endif


	SetFontSize(30);

	//上の選択肢
	if (display_attribute - 1 < 0)
	{
		DrawFormatString(1000, 10, 0x778877, "%s", attribute_c[display_attribute + 5]);
		cout << attribute_c[display_attribute + 5] << endl;
	}
	else
	{
		DrawFormatString(1000, 10, 0x778877, "%s", attribute_c[display_attribute - 1]);
	}
	//下の選択肢
	if (display_attribute + 1 > 5)
	{
		DrawFormatString(1000, 90, 0x778877, "%s", attribute_c[display_attribute - 5]);
	}
	else
	{
		DrawFormatString(1000, 90, 0x778877, "%s", attribute_c[display_attribute + 1]);
	}
	//現在の選択肢
	DrawFormatString(1000, 50, 0x778877, "%s", attribute_c[display_attribute]);

	DrawFormatString(0, 400, 0x999999, "%d", hp);

	if (pouch_open)
	{
		pouch->Draw();
	}
}

//-----------------------------------
// 更新
//-----------------------------------
void Player::Update()
{


	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		location.y -= 10;
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		location.y += 10;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		location.x += 10;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		location.x -= 10;
	}

	else if (CheckHitKey(KEY_INPUT_S))
	{
		location.x += 400;
	}

	//マップチップのオブジェクト取得
	//for (int i = 0; i < stage->GetMapChip().size(); i++)
	//{
	//}


	damage_count++;
	if (damage_count >= 10)
	{
		damage_count = 0;
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && !pouch_open)
	{
		pouch_open = true;
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && pouch_open)
	{
		pouch_open = false;
	}

	if (pouch_open)
	{
		pouch->Update();
	}

	//スティック右入力
	if (PAD_INPUT::GetLStick().x >= 10000)
	{
		RightMove();
	}
	//スティック左入力
	else if (PAD_INPUT::GetLStick().x <= -10000)
	{
		LeftMove();
	}
	//スティック未入力
	else
	{
		NotInputStick();
	}

	//RBボタン入力
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		count++;

		if (count % 30 == 0)
		{
			bullet_count++;
			Shoot_Gun();
		}
	}

	//RBボタン入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		bullet_count++;
		Shoot_Gun();
	}
	//Bボタン入力
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B) && fuel > 0)
	{
		Jump();
	}
	//Bボタン未入力
	else
	{
		NotJump();
	}

	//Bボタン解放時
	if (PAD_INPUT::OnRelease(XINPUT_BUTTON_B))
	{
		player_state = PLAYER_STATE::DOWN;
	}



	//弾のアップデート呼び出し
	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			if (bullet[i]->GetEfectFlg())
			{
				bullet[i] = nullptr;
				SortBullet(i);
			}
			else
			{
				bullet[i]->Update();
			}
		}
	}

	//弾の属性の切り替え処理
	ElementUpdate();

}

//スティックを入力していないとき
void Player::NotInputStick()
{
	if (speed_x > 0)
	{
		if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
		{
			speed_x -= JUMP_INERTIA;
		}
		else
		{
			speed_x -= WARK_INERTIA;
		}

		if (speed_x < 0)
		{
			speed_x = 0;
		}
	}

	if (speed_x < 0)
	{
		if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
		{
			speed_x += JUMP_INERTIA;
		}
		else
		{
			speed_x += WARK_INERTIA;
		}

		if (speed_x > 0)
		{
			speed_x = 0;
		}
	}

	if (speed_x > -JUMP_INERTIA && speed_x < JUMP_INERTIA)
	{
		speed_x = 0;
	}

	location.x += speed_x;
}

//左移動
void Player::LeftMove()
{
	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
	{
		if (speed_x > -5.0)
		{
			speed_x = speed_x - JUMP_INERTIA;
		}
		else
		{
			speed_x = -5.0;
		}
	}
	else
	{
		player_state = PLAYER_STATE::MOVE_LEFT;
		if (speed_x > -5.0)
		{
			speed_x = speed_x - WARK_INERTIA;
		}
		else
		{
			speed_x = -5.0;
		}
	}
	location.x += speed_x;
}

//右移動
void Player::RightMove()
{
	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
	{
		if (speed_x < 5.0)
		{
			speed_x = speed_x + JUMP_INERTIA;
		}
		else
		{
			speed_x = 5.0;
		}
	}
	else
	{
		player_state = PLAYER_STATE::MOVE_RIGHT;
		if (speed_x < 5.0)
		{
			speed_x = speed_x + WARK_INERTIA;
		}
		else
		{
			speed_x = 5.0;
		}
	}

	location.x += speed_x;
}

//ジャンプ
void Player::Jump()
{
	player_state = PLAYER_STATE::JUMP;
	not_jet_count = 0;


	gravity_down = 0.0;

	jump += 0.25;
	fuel -= 0.25;


	if (jump > 10)
	{
		jump = 10.0;
	}

	if (fuel < 0)
	{
		fuel = 0;
		player_state = PLAYER_STATE::DOWN;
	}

	if (location.y > 40)
	{
		location.y -= jump;
	}
	else
	{
		location.y = 40;
	}

	if (location.y > 400)
	{
		//location.y = 1200;
		jump = 0.0;
	}
}

//ジャンプしてない
void Player::NotJump()
{
	player_state = PLAYER_STATE::DOWN;
	if (location.y < 400)
	{
		location.y -= jump;
	}
	else
	{
		player_state = PLAYER_STATE::STOP;
	}

	if(location.y < 40)
	{
		jump = 0;
		//location.y = 40;
	}

	jump -= 0.25;

	if (jump < -10)
	{
		jump = -10;
	}
	
	if (not_jet_count++ >= 120)
	{
		jump = 0;
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

	/*jump_power -= 0.5;
	if (location.y > 0)
	{
		location.y -= jump_power;
	}
	else
	{
		jump_power = 0;
	}

	jump = 10;

	if (location.y < 400)
	{
		location.y += gravity_down;
	}
	else
	{
		player_state = PLAYER_STATE::STOP;
	}
	gravity_down += 0.25;



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
	}*/
}

//-----------------------------------
// 弾を発射
//-----------------------------------
void Player::Shoot_Gun()
{
	for (i = 0; i < bullet_count; i++)
	{
		if (bullet[i] == nullptr)
		{
			switch (display_attribute)
			{
			case 0:
				bullet[i] = new NormalBullet(location.x, location.y, attribute[display_attribute]);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			default:
				break;
			}
		}
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

//-----------------------------------
//属性を変更
//-----------------------------------
void Player::ElementUpdate()
{
	if (PAD_INPUT::GetRStick().y > 5000)
	{
		if (select_count % 20 == 0)
		{
			display_attribute--;
			if (display_attribute < 0)
			{
				display_attribute = 5;
			}
		}
	}

	if (PAD_INPUT::GetRStick().y < -5000)
	{
		if (select_count % 20 == 0)
		{
			display_attribute++;
			if (display_attribute > 5)
			{
				display_attribute = 0;
			}
		}
	}

	select_count++;
}

//-----------------------------------
//ダメージを受けた時
//-----------------------------------
void Player::Hp_Damage(int damage_value)
{
	damage_flg = true;
	hp -= damage_value;
	if (hp <= 0)
	{
		hp = 0;
		player_state = PLAYER_STATE::DEATH;
	}
}

////敵からダメージを受けた時
//void Player::Being_Attacked(EnemyBase* enemy_base)
//{}

//回復
//-----------------------------------
void Player::Hp_Heal(int heal_value)
{
	hp += heal_value;
	if (hp >= HP_MAX)
	{
		hp = HP_MAX;
	}
}

//-----------------------------------
//元素の量の設定
//-----------------------------------
void Player::SetElementItem(class Item* item)
{

	int num = static_cast<int>(item->GetElementType());

	element[num]->SetVolume(element[num]->GetVolume() + 1);
}