//#include<dxlib.h>
//#define _USE_MATH_DEFINES
//#include<math.h>
//#include"EnemySlimeBoss.h"
//#include"Player.h"
//#include"Stage/Stage.h"
//
////ˆÚ“®‘¬“x
//#define SLIME_SPEED 2
//#define SLIME_ATTACK_DAMAGE 10
//
//#define SLIME_MIN_DROP 0u
//#define SLIME_MAX_DROP 3u
//
//
//
//EnemySlimeBoss::EnemySlimeBoss()
//{
//	for (int i = 0; i < BODY_MAX; i++)
//	{
//		if (i == 0)slime_boss_body[i] = new SlimeBossBody(100, 700, 5, 100, 5, 10, BODY_TYPE::head);
//		else slime_boss_body[i] = new SlimeBossBody(100, 100, 5, 100, 5, 10, BODY_TYPE::body);
//	}
//}
//
//void EnemySlimeBoss::Update(const Stage* stage, const Player* player)
//{
//	for(int i = 0; i < BODY_MAX; i++)
//	{
//		if (slime_boss_body[i]->GetBodyType() == BODY_TYPE::head)
//		{
//			slime_boss_body[i]->Update(player, stage);
//		}
//		else
//		{
//			slime_boss_body[i]->SetLocation(location_data[DATA / (i * BODY_MAX)]);
//		}
//	}
//
//	Location now = slime_boss_body[0]->GetLocation();
//	Location old;
//	
//	for(int i = 0; i < DATA; i++)
//	{
//		old.x = location_data[i].x;
//		old.y = location_data[i].y;
//
//		location_data[i].x = now.x;
//		location_data[i].y = now.y;
//		
//		now.x = old.x;
//		now.y = old.y;
//	}
//}
//
//void EnemySlimeBoss::Draw()const
//{
//	for (int i = 0; i < BODY_MAX; i++)
//	{
//		slime_boss_body[i]->Draw();
//	}
//}