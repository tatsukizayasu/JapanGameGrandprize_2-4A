#include "Player.h"
#include "DxLib.h"
#include "NormalBullet.h"
#include "PadInput.h"
#include "CameraWork.h"
#include "Item.h"
#include <iostream>

#define ANIMATION_MOVE 10


//-----------------------------------
// コンストラクタ
//-----------------------------------
Player::Player()
{
	animation = 0;
	location.x = 0;
	location.y = 420;
	image = new int[PLAYER_IMAGES];
	LoadDivGraph("Images/Player/ Player.png", PLAYER_IMAGES, PLAYER_IMAGES, 1, 40, 80, image);
	image_size_x = 40;
	image_size_y = 80;
	area.width = image_size_x;
	area.height = image_size_y;
	bullet_count = 0;
	shoot_count = 0;
	flashing_count = 0;
	damage_count = 0;
	jump = 0.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	fuel = 100.0;
	gravity_down = 0.0;
	old_x = 0.0;
	old_y = 0.0;
	damage = 0;
	image_count = 0;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = new BulletBase * [BULLET_MAX];
		bullet[i] = nullptr;
	}

	move_left = false;

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

	explosion = nullptr;
	melt = nullptr;
	poison = nullptr;
	pararysis = nullptr;
	heal = nullptr;


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

}

//-----------------------------------
// コンストラクタ
//-----------------------------------
Player::Player(Stage* stage)
{
	animation = 0;
	area.height = 80;
	area.width = 40;

	this->stage = stage;
	location.x = stage->GetSpawnPoint().x;
	location.y = (stage->GetSpawnPoint().y - MAP_CHIP_SIZE / 2) - 1.0;
	image = new int[PLAYER_IMAGES];
	LoadDivGraph("Images/Player/Player.png", 7, 7, 1, 40, 80, image);

	image_size_x = 40;
	image_size_y = 80;
	area.width = image_size_x;
	area.height = image_size_y;
	bullet_count = 0;
	damage_count = 0;
	shoot_count = 0;
	select_count = 0;
	damage = 0;
	flashing_count = 0;
	jump = 0.0;
	jump_power = 0.0;
	not_jet_count = 0;
	speed_x = 0.0;
	old_x = 0.0;
	old_y = 0.0;
	fuel = 100.0;
	gravity_down = 0.0;
	image_count = 0;

	normal.atribute = ATTRIBUTE::NORMAL;
	normal.chemical_formula[0] = 'n';
	normal.chemical_formula_name[0] = 'a';
	normal.damage = 2;
	normal.damage_per_second = 0;
	normal.material.carbon = 0;
	normal.material.chlorine = 0;
	normal.material.hydrogen = 0;
	normal.material.nitrogen = 0;
	normal.material.oxygen = 0;
	normal.material.sulfur = 0;
	normal.material.uranium = 0;
	normal.number_of_bullets = 50;
	normal.time = 0;

	bullet = new BulletBase * [BULLET_MAX];
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i] = nullptr;
	}

	damage_flg = false;
	pouch_open = false;
	move_left = false;
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

	hp = 100;

	explosion = nullptr;
	melt = nullptr;
	poison = nullptr;
	pararysis = nullptr;
	heal = nullptr;

	beam = nullptr;

	this->stage = stage;

	area = { 80,40 };

	//元素の初期化
	element = new ElementItem * [PLAYER_ELEMENT];
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
	}

	pouch = new Pouch();

	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		pouch->SetElement(element[i], i);
		pouch->SetElementConstruct(i);
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

	float now_hp = (hp / HP_MAX) * HP_BAR_WIDTH;
	float now_fuel = (fuel / FUEL_MAX) * FUEL_BAR_HEIGHT;

	//FUELバーの表示ここから
	if (fuel >= 50)
	{
		DrawBoxAA(x - 50, (y - (area.height / 2)) + (FUEL_MAX - now_fuel),
			(x - 45), (y - (area.height / 2)) + FUEL_BAR_HEIGHT, GREEN, TRUE);
	}
	else if (fuel >= 20)
	{
		DrawBoxAA(x - 50, (y - (area.height / 2)) + (FUEL_MAX - now_fuel),
			(x - 45), (y - (area.height / 2)) + FUEL_BAR_HEIGHT, YELLOW, TRUE);
	}
	else
	{
		DrawBoxAA(x - 50, (y - (area.height / 2)) + (FUEL_MAX - now_fuel),
			(x - 45), (y - (area.height / 2)) + FUEL_BAR_HEIGHT, RED, TRUE);
	}
	//ここまで

	//HPバーの表示ここから
	if (hp >= 50)
	{
		DrawBoxAA(10, 50, now_hp - 1, 50 + HP_BAR_HEIGHT, GREEN, TRUE);
	}
	else if (hp >= 20)
	{
		DrawBoxAA(10, 50, now_hp - 1, 50 + HP_BAR_HEIGHT, YELLOW, TRUE);
	}
	else
	{
		DrawBoxAA(10, 50, now_hp - 1, 50 + HP_BAR_HEIGHT, RED, TRUE);
	}
	DrawBox(10, 50, HP_BAR_WIDTH - 1, 50 + HP_BAR_HEIGHT, 0x000000, FALSE);
	//ここまで

	for (int i = 0; i < bullet_count; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}

	DrawFormatString(0, 0, 0x00ff00, "%f %f", jump_power, fuel);

	//ダメージを受けた時点滅する
	if (damage_flg)
	{
		if (flashing_count < 5)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			DrawRotaGraphF(x, y, 1, 0, image[image_count], TRUE, move_left);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else if (flashing_count < 10)
		{
			DrawRotaGraphF(x, y, 1, 0, image[image_count], TRUE, move_left);
		}
		else {}
	}
	else
	{
		DrawRotaGraphF(x, y, 1, 0, image[image_count], TRUE, move_left);
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
	DrawCircle(990, 60, 5, 0x000000, TRUE);
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
	old_x = location.x;
	old_y = location.y;
	if (damage_flg == true)
	{
		damage_count++;
		if (damage_count <= damage)
		{
			if (hp > 0)
			{
				hp--;
			}
			else
			{
				hp = 0;
				player_state = PLAYER_STATE::DEATH;
			}
		}

		if (flashing_count++ >= 10)
		{
			flashing_count = 0;
		}

		if (damage_count % 120 == 0)
		{
			damage_flg = false;
			damage_count = 0;
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && !pouch_open)
	{
		pouch_open = true;
		for (int i = 0; i < PLAYER_ELEMENT; i++)
		{
			pouch->SetElement(element[i], i);
		}
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) && pouch_open)
	{
		pouch_open = false;
	}


	//ポーチオープン
	if (pouch_open)
	{
		pouch->Update();
		if (pouch->GetOnBool())
		{
			switch (pouch->GetAttribute())
			{
			case ATTRIBUTE::EXPLOSION:
				explosion = pouch->GetExplosion();
				break;
			case ATTRIBUTE::MELT:
				melt = pouch->GetMelt();
				break;
			case ATTRIBUTE::POISON:
				poison = pouch->GetPoison();
				break;
			case ATTRIBUTE::PARALYSIS:
				pararysis = pouch->GetPararysis();
				break;
			case ATTRIBUTE::HEAL:
				heal = pouch->GetHeal();
				break;
			default:
				break;
			}
		}
	}

	//スティック右入力
	if (PAD_INPUT::GetLStick().x >= 10000)
	{
		move_left = false;
		RightMove();
	}
	//スティック左入力
	else if (PAD_INPUT::GetLStick().x <= -10000)
	{
		move_left = true;
		LeftMove();
	}
	//スティック未入力
	else
	{
		NotInputStick();
	}

	//RBボタン入力
	if (!pouch_open)
	{
		if (PAD_INPUT::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER))
		{
			if (shoot_count++ % 10 == 0)
			{
				bullet_count++;
				Shoot_Gun();
			}
		}
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
				delete bullet[i];
				bullet[i] = nullptr;
				SortBullet(i);
			}
			else
			{
				bullet[i]->Update(stage);
			}
		}
	}

	//弾の属性の切り替え処理
	if (!pouch_open)
	{
		ElementUpdate();
	}
}

//スティックを入力していないとき
void Player::NotInputStick()
{
	image_count = 0;
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
			player_state = PLAYER_STATE::STOP;
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
		player_state = PLAYER_STATE::STOP;
		speed_x = 0;
	}

	if (!HitBlock(stage))
	{
		location.x += speed_x;
	}
	if (HitBlock(stage))
	{
		speed_x = 0.0;
		location.x = old_x;
	}
}

//左移動
void Player::LeftMove()
{




	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
	{
		if (speed_x > -PLAYER_SPEED_X)
		{
			speed_x = speed_x - JUMP_INERTIA;
		}
		else
		{
			speed_x = -PLAYER_SPEED_X;
		}
	}
	else
	{

		MoveAnimation();
		player_state = PLAYER_STATE::MOVE_LEFT;
		if (speed_x > -PLAYER_SPEED_X)
		{
			speed_x = speed_x - WARK_INERTIA;
		}
		else
		{
			speed_x = -PLAYER_SPEED_X;
		}
	}

	if (!HitBlock(stage))
	{
		location.x += speed_x;
	}

	if (location.x < 0)
	{
		speed_x = 0.0;
	}

	if (HitBlock(stage))
	{
		location.x = old_x;
	}
}

//右移動
void Player::RightMove()
{


	if (player_state == PLAYER_STATE::JUMP || player_state == PLAYER_STATE::DOWN)
	{
		if (speed_x < PLAYER_SPEED_X)
		{
			speed_x = speed_x + JUMP_INERTIA;
		}
		else
		{
			speed_x = PLAYER_SPEED_X;
		}
	}
	else
	{
		MoveAnimation();
		player_state = PLAYER_STATE::MOVE_RIGHT;
		if (speed_x < PLAYER_SPEED_X)
		{
			speed_x = speed_x + WARK_INERTIA;
		}
		else
		{
			speed_x = PLAYER_SPEED_X;
		}
	}

	if (!HitBlock(stage))
	{
		location.x += speed_x;
	}

	if (HitBlock(stage))
	{
		location.x = old_x;
		speed_x = 0.0;
	}

	if (location.x < 0)
	{
		speed_x = 0.0;
	}
}

//ジャンプ
void Player::Jump()
{
	image_count = 0;
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

	if (!HitBlock(stage))
	{
		location.y -= jump;
	}

	if (HitBlock(stage))
	{
		jump = 0.0;
		location.y = old_y;
	}
}

//ジャンプしてない
void Player::NotJump()
{
	player_state = PLAYER_STATE::DOWN;

	jump -= 0.25;

	if (jump < -10)
	{
		jump = -10;
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

	if (!HitBlock(stage))
	{
		location.y -= jump;
	}

	if (HitBlock(stage))
	{
		jump = 0;
		location.y = old_y;
		player_state = PLAYER_STATE::STOP;
	}
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
				bullet[i] = new NormalBullet(location.x, location.y, move_left, &normal);
				break;
			case 1:
				if (explosion != nullptr)
				{
					if (explosion->number_of_bullets > 0)
					{
						bullet[i] = new NormalBullet(location.x, location.y, move_left, explosion);
						pouch->ReduceAmmo(attribute[display_attribute]);
					}
					else
					{
						explosion = nullptr;
						pouch->DeleteExplosion();
					}
				}
				break;
			case 2:
				if (melt != nullptr)
				{
					if (melt->number_of_bullets > 0)
					{
						bullet[i] = new NormalBullet(location.x, location.y, move_left, melt);
						pouch->ReduceAmmo(attribute[display_attribute]);
					}
					else
					{
						melt = nullptr;
						pouch->DeleteMelt();
					}
				}
				break;
			case 3:
				if (poison != nullptr)
				{
					if (poison->number_of_bullets > 0)
					{
						bullet[i] = new NormalBullet(location.x, location.y, move_left, poison);
						pouch->ReduceAmmo(attribute[display_attribute]);
					}
					else
					{
						poison = nullptr;
						pouch->DeletePoison();
					}
				}
				break;
			case 4:
				if (pararysis != nullptr)
				{
					if (pararysis->number_of_bullets > 0)
					{
						bullet[i] = new NormalBullet(location.x, location.y, move_left, pararysis);
						pouch->ReduceAmmo(attribute[display_attribute]);
					}
					else
					{
						pararysis = nullptr;
						pouch->DeletePararysis();
					}
				}
				break;
			case 5:
				if (heal != nullptr)
				{
					if (heal->number_of_bullets > 0)
					{
						bullet[i] = new NormalBullet(location.x, location.y, move_left, pararysis);
						pouch->ReduceAmmo(attribute[display_attribute]);
					}
					else
					{
						heal = nullptr;
						pouch->DeleteHeal();
					}
				}
				break;
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
	for (int i = delete_bullet + 1; i < BULLET_MAX; i++)
	{
		if ((bullet[i] == nullptr))
		{
			break;
		}

		bullet[i - 1] = bullet[i];
		bullet[i] = nullptr;
	}
	bullet_count--;
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
void Player::HpDamage(AttackResource attack)
{
	if (!damage_flg)
	{
		if (attack.damage > 0)
		{
			damage_flg = true;
			damage = attack.damage;

			if (attack.type != nullptr)
			{
				for (int i = 0; i < attack.type_count; i++)
				{
					switch (attack.type[i])
					{
					case ENEMY_TYPE::NORMAL:
						break;
					case ENEMY_TYPE::FIRE:
						break;
					case ENEMY_TYPE::WATER:
						break;
					case ENEMY_TYPE::WIND:
						break;
					case ENEMY_TYPE::SOIL:
						break;
					case ENEMY_TYPE::THUNDER:
						break;
					default:
						break;
					}
				}
			}
		}
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

//-----------------------------------wer
//元素の量の設定
//-----------------------------------
void Player::SetElementItem(class Item* item)
{
	int num = static_cast<int>(item->GetElementType());

	element[num]->SetVolume(element[num]->GetVolume() + 1);

}

bool Player::HitBlock(const Stage* stage_pointa)
{
	//マップチップ
	std::vector<MapChip*>map_chip = stage_pointa->GetMapChip();

	//描画範囲
	Location camera = CameraWork::GetCamera();

	for (MapChip* map_chip : map_chip)
	{
		if (map_chip != nullptr)
		{

			Location draw_location = map_chip->GetLocation();
			Area draw = { SCREEN_HEIGHT + CHIP_SIZE,SCREEN_WIDTH + CHIP_SIZE };

			// 画面内にあるMapChipオブジェクトだけUpdateする
			if ((camera.x < draw_location.x + draw.width) && (draw_location.x < camera.x + draw.width)
				&& (camera.y < draw_location.y + draw.height) && (draw_location.y < camera.y + draw.height))
			{
				if (HitBox(map_chip))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Player::GetMoveDirection()
{
	return move_left;
}


void Player::SetExplosion(ChemicalFormulaParameter* a)
{
	explosion = a;
}

void Player::SetPoison(ChemicalFormulaParameter* a)
{
	poison = a;
}

void Player::SetMelt(ChemicalFormulaParameter* a)
{
	melt = a;
}

void Player::SetPararysis(ChemicalFormulaParameter* a)
{
	pararysis = a;
}

void Player::SetHeal(ChemicalFormulaParameter* a)
{
	heal = a;
}

void Player::MoveAnimation()
{
	animation++;
	if (animation % ANIMATION_MOVE == 0)
	{
		image_count++;
	}

	if (image_count >= PLAYER_IMAGES)
	{
		image_count = 0;
	}
}

