//#include "Harpy.h"
//#include "CameraWork.h"
//
////ハーピィの画像サイズ(未定、画像が出来次第調整）
//#define HARPY_SIZE_X 40
//#define HARPY_SIZE_Y 80
//
////プレイヤー発見距離
//#define HARPY_DETECTION_DISTANCE 500
//
////物理攻撃範囲
//#define HARPY_ATTACK_RANGE 20
//
////魔法攻撃範囲	
//#define HARPY_ATTACK_MAGIC 400
//
////魔法攻撃した時の硬直時間
//#define HARPY_MAGIC_STANDBY 60
//
////近接攻撃した時の硬直時間
//#define HARPY_PHYSICAL_STANDBY 100
//
////移動スピード
//#define HARPY_SPEED 2.5
//
////攻撃スピード
//#define ATTACK_SPEED 5
//
////ドロップ量(最小)
//#define HARPY_MIN_DROP 0u
//
////ドロップ量(最大)
//#define HARPY_MAX_DROP 4u
//
//
////-----------------------------------
//// コンストラクタ
////-----------------------------------
//Harpy::Harpy()
//{
//	location.x = 1500;
//	location.y = 1200;
//	hp = 20;
//	can_delete = false;
//
//	// ドロップアイテムの設定
//		drop_element = new ElementItem * [WIND_DROP];
//	drop_type_volume = WIND_DROP;
//
//	int volume = 0;
//	for (int i = 0; i < WIND_DROP; i++)
//	{
//		volume = HARPY_MIN_DROP + GetRand(HARPY_MAX_DROP);
//		drop_element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(2 + i));
//		drop_element[i]->SetVolume(volume);
//		drop_volume += volume;
//	}
//	
//	//属性　（風）
//	type = new ENEMY_TYPE;
//	*type = ENEMY_TYPE::WIND;
//
//}
//
//
////-----------------------------------
//// デストラクタ
////-----------------------------------
//Harpy::~Harpy()
//{
//
//}
//
//
////-----------------------------------
//// 更新
////-----------------------------------
//void Harpy::Update()
//{
//
//}
//
//
//
////-----------------------------------
//// 描画
////-----------------------------------
//void Harpy::Draw() const
//{
//	//スクロールに合わせて描画
//	float x = location.x - CameraWork::GetCamera().x;
//	float y = location.y - CameraWork::GetCamera().y;
//
//	DrawBox(x, y, x + HARPY_SIZE_X, y + HARPY_SIZE_Y, GetColor(255, 255, 0), TRUE);
//	
//}
//
////-----------------------------------
//// ハーピィの動き
////-----------------------------------
//void Harpy::Move(const Location player_location)
//{
//	//距離
//	Distance(player_location);
//
//	switch (action)
//	{
//	case HARPY_STATE::NORMAL:
//		location.x -= HARPY_SPEED;
//		break;
//	case HARPY_STATE::NORMAL_RIGHT:
//		location.x += HARPY_SPEED;
//		break;
//	case HARPY_STATE::LEFT_lOWER:
//		location.x -= HARPY_SPEED;
//		location.y -= HARPY_SPEED;
//		break;
//	case HARPY_STATE::LEFT_UPPER:
//		location.x -= HARPY_SPEED;
//		location.y+= HARPY_SPEED;
//		break;
//	case HARPY_STATE::RIGHT_LOWER:
//		location.x+= HARPY_SPEED;
//		location.y-= HARPY_SPEED;
//		break;
//	case HARPY_STATE::RIGHT_UPPER:
//		location.x+= HARPY_SPEED;
//		location.y+= HARPY_SPEED;
//		break;
//	default:
//		break;
//	}
//
//}
//
//
////------------------------------------------
//// プレイヤーの距離を測った後に行動を決める
////------------------------------------------
//void Harpy::Distance(const Location player_location)
//{
//	float range; //プレイヤーとの距離	
//
//	range = fabsf(location.x - player_location.x);
//
//	//プレイヤーが発見距離内にいたら
//	if (range <= HARPY_DETECTION_DISTANCE && range >= -HARPY_DETECTION_DISTANCE)
//	{
//		if (location.x > player_location.x) //左に移動
//		{
//			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
//			{
//				action = HARPY_STATE::NORMAL;
//			}
//			else if (player_location.y > location.y)
//			{
//				action = HARPY_STATE::LEFT_lOWER;
//			}
//			else
//			{
//				action = HARPY_STATE::LEFT_UPPER;
//			}
//		}
//		else //右に移動
//		{
//			if (location.y + 10 >= player_location.y && location.y - 10 <= player_location.y)
//			{
//				action = HARPY_STATE::NORMAL_RIGHT;
//			}
//			else if (player_location.y > location.y)
//			{
//				action = HARPY_STATE::RIGHT_LOWER;
//			}
//			else
//			{
//				action = HARPY_STATE::RIGHT_UPPER;
//			}
//		}
//	}
//	else //通常移動
//	{
//		action = HARPY_STATE::NORMAL;
//		magic_attack = false;
//		physical_attack = false;
//	}
//}
//
////void Harpy::Idol()
////{
////
////}
////
////void Harpy::Attack(Location)
////{
////
////}
////
////AttackResource Harpy::HitCheck(const BoxCollider* collider)
////{
////	return AttackResource();
////}
////
////void Harpy::Death()
////{
////
////}
////
////bool Harpy::HitBullet(const BulletBase* bullet)
////{
////	return false;
////}
////
////Location Harpy::GetLocation() const
////{
////	return Location();
////}
//