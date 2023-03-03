#include "Mage.h"
#include "CameraWork.h"
#include "MageBullet.h"

//魔法弾の発射レート
#define MAGE_SHOT_RATE 20

//移動速度
#define MAGE_SPEED 2

//ドロップ数
#define MAGE_MIN_DROP 0
#define MAGE_MAX_DROP 6

#define MAGE_SHOT_RATE 20

//体力
#define MAGE_HP 100

//移動範囲
#define MAGE_TELEPORT_AREA 200

//攻撃間隔
#define MAGE_ATTACK_INTERVAL 120

//-----------------------------------
//コンストラクタ
//-----------------------------------
Mage::Mage() 
{
	/*初期化*/
	can_delete = false;
	hp = MAGE_HP;
	shot_rate = 0;
	shot_count = 0;
	attack_interval = 0;
	speed = MAGE_SPEED;
	kind = ENEMY_KIND::MAGE;
	type = new ENEMY_TYPE;
	
	*type = static_cast<ENEMY_TYPE>(1 + GetRand(3));
	state = ENEMY_STATE::IDOL;
	drop_volume = 0;
	image = 0xffffff;

	/*当たり判定の設定*/
	location.x = 640.0f;
	location.y = 1120.0f;
	area.width = 40;
	area.height = 80;

	//ドロップアイテムの設定
	drop = 0;

	switch (*type)
	{
	case ENEMY_TYPE::NORMAL:
		break;
	case ENEMY_TYPE::FIRE:
		drop = FIRE_DROP;
		image = 0xff0000;
		break;
	case ENEMY_TYPE::WATER:
		drop = WATER_DROP;
		image = 0x0000ff;
		break;
	case ENEMY_TYPE::WIND:
		drop = WIND_DROP;
		image = 0xffffff;
		break;
	case ENEMY_TYPE::SOIL:
		drop = SOIL_DROP;
		image = 0xffff00;
		break;
	case ENEMY_TYPE::THUNDER:
		break;
	default:
		break;
	}

	drop_element = new ElementItem * [drop];
	drop_type_volume = drop;

	int volume = 0;

	for (int i = 0; i < drop; i++)
	{

		volume = MAGE_MIN_DROP + GetRand(MAGE_MAX_DROP);

		switch (*type)
		{
		case ENEMY_TYPE::NORMAL:
			break;
		case ENEMY_TYPE::FIRE:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(1 + i));
			break;
		case ENEMY_TYPE::WATER:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			}
			break;
		case ENEMY_TYPE::WIND:
			if (i < 2)
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
			}
			else
			{
				drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(1 + i));
			}
			break;
		case ENEMY_TYPE::SOIL:
			drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
			break;
		case ENEMY_TYPE::THUNDER:
			break;
		default:
			break;
		}

		drop_element[i]->SetVolume(volume);
		drop_volume += volume;
	}

	bullet = new EnemyBulletBase * [MAGE_BULLET_MAX];

	//弾の初期化
	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		bullet[i] = nullptr;
	}

}

//-----------------------------------
//デストラクタ
//-----------------------------------
Mage::~Mage()
{
	delete type;

	for (int i = 0; i < drop; i++)
	{
		delete drop_element[i];
	}

	delete[] drop_element;

	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		delete bullet[i];
	}

	delete[] bullet;
}

//-----------------------------------
//更新
//-----------------------------------
void Mage::Update()
{

	if (attack_interval < 0)
	{
		attack_interval--;
	}
	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		if (bullet[i] == nullptr)
		{
			break;
		}

		bullet[i]->Update();

		if (bullet[i]->ScreenOut()) //画面外に出たら削除
		{
			delete bullet[i];
			bullet[i] = nullptr;
			SortBullet(i);
			i--;
		}
	}

	Poison();
	Paralysis();

	if (CheckHp() && (state != ENEMY_STATE::DEATH))
	{
		state = ENEMY_STATE::DEATH;
	}
}


//-----------------------------------
//アイドル状態
//-----------------------------------
void Mage::Idol()
{
	Location scroll; //画面スクロールを考慮したX座標

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;
	if ((-area.width < scroll.x) && (scroll.x < SCREEN_WIDTH + area.width) &&
		(-area.height < scroll.y) && (scroll.y < SCREEN_HEIGHT + area.height))
	{
		state = ENEMY_STATE::MOVE;
	}
}

//-----------------------------------
//移動
//-----------------------------------
void Mage::Move(const Location player_location)
{
	Location scroll; //画面スクロールを考慮したX座標

	

	if (attack_interval < 0)
	{
		state = ENEMY_STATE::ATTACK;
	}

	scroll.x = location.x - CameraWork::GetCamera().x;
	scroll.y = location.y - CameraWork::GetCamera().y;

	if ((scroll.x < -area.width) || (SCREEN_WIDTH + area.width < scroll.x) ||
		(scroll.y < -area.height) || (SCREEN_HEIGHT + area.height < scroll.y))
	{
		state = ENEMY_STATE::IDOL;
	}
}

//-----------------------------------
//テレポート
//-----------------------------------
void Mage::Teleport()
{

}

//-----------------------------------
//攻撃
//-----------------------------------
void  Mage::Attack(Location player_location)
{
	CreateBullet(player_location);
	
	if (shot_count >= MAGE_BULLET_MAX)
	{
		state = ENEMY_STATE::MOVE;
		shot_count = 0;
		attack_interval = MAGE_ATTACK_INTERVAL;
	}
}

//-----------------------------------
//攻撃が当たっているか
//-----------------------------------
AttackResource Mage::HitCheck(const BoxCollider* collider)
{
	AttackResource ret = { 0,nullptr,0 }; //戻り値

	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		if (bullet[i] == nullptr)
		{
			break;
		}

		if (bullet[i]->HitBox(collider))
		{
			ENEMY_TYPE attack_type[1] = { bullet[i]->GetType() };
			ret.damage += bullet[i]->GetDamage();
			ret.type = attack_type;
			ret.type_count = 1;

			delete bullet[i];
			bullet[i] = nullptr;
			SortBullet(i);
		}
	}
	return ret;
}

//-----------------------------------
//死亡
//-----------------------------------
void Mage::Death()
{
	can_delete = true;
}

//-----------------------------------
//弾の生成
//-----------------------------------
void Mage::CreateBullet(Location player_location)
{
	shot_rate++;

	if (shot_rate % MAGE_SHOT_RATE == 0)
	{
		for (int i = 0; i < MAGE_BULLET_MAX; i++)
		{
			if (bullet[i] == nullptr)
			{
				bullet[i] = new MageBullet(*type, location, player_location);
				shot_count++;
				break;
			}
		}
	}
}

//-----------------------------------
//弾の並び替え
//-----------------------------------
void Mage::SortBullet(int bullet_num)
{
	//弾の中身をソートする
	for (int i = bullet_num + 1; i < MAGE_BULLET_MAX; i++)
	{
		if ((bullet[i] == nullptr))
		{
			break;
		}
		bullet[i - 1] = bullet[i];
		bullet[i] = nullptr;
	}
}

//-----------------------------------
//プレイヤーの弾との当たり判定
//-----------------------------------
bool Mage::HitBullet(const BulletBase* bullet)
{
	bool ret = false; //戻り値

	if (HitSphere(bullet))
	{
		switch (bullet->GetAttribute())
		{
		case ATTRIBUTE::NORMAL:
			hp -= bullet->GetDamage() * WEAKNESS_DAMAGE;
			break;
		case ATTRIBUTE::EXPLOSION:
			hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
			break;
		case ATTRIBUTE::MELT:
			hp -= bullet->GetDamage() * RESISTANCE_DAMAGE;
			break;
		case ATTRIBUTE::POISON:
			poison_damage = bullet->GetDamage();
			poison_time = bullet->GetDebuffTime() * WEAKNESS_DEBUFF;
			break;
		case ATTRIBUTE::PARALYSIS:
			paralysis_time = bullet->GetDebuffTime() * RESISTANCE_DEBUFF;
			break;
		case ATTRIBUTE::HEAL:
			break;
		default:
			break;
		}
		ret = true;
	}

	return ret;
}

//-----------------------------------
//描画
//-----------------------------------
void Mage::Draw() const
{

	Location draw_location; //描画用の座標

	draw_location.x = location.x - CameraWork::GetCamera().x;
	draw_location.y = location.y - CameraWork::GetCamera().y;

	DrawBox(draw_location.x, draw_location.y, draw_location.x + area.width, draw_location.y + area.height, image, TRUE);

	for (int i = 0; i < MAGE_BULLET_MAX; i++)
	{
		if (bullet[i] == nullptr)
		{
			break;
		}

		bullet[i]->Draw();
	}
}

//-----------------------------------
//弾の取得
//-----------------------------------
EnemyBulletBase** Mage::GetBullet() const
{
	return bullet;
}

//-----------------------------------
//座標の取得
//-----------------------------------
Location Mage::GetLocation() const
{
	return location;
}