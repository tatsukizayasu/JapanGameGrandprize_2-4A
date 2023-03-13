#include "Element_DamageWall.h"
#include "../Player.h"


Element_DamageWall::Element_DamageWall(short type, std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area) : Stage_Element_Base(element, image, location, area)
{
	this->type = type;
}

Element_DamageWall::~Element_DamageWall()
{
}

void Element_DamageWall::Update(Player* player)
{
	if (this->player == nullptr) { this->player = player; }
	if (HitPlayer(player))
	{
		//printfDx("当たってるよ\n");		
		std::function<void()> f = [&]() { player->HpDamage(AttackResource{ 1, nullptr, 5 }); };
		//StartAnimation(10.2, [&]() {player->HpDamage(AttackResource{1, nullptr, 5});});
		//StartAnimation(10.2, &f);
		//if (GetAnimationTime() < 5.1) { image = 0; }
		//std::thread thread1(&Element_DamageWall::Damage, this, player);
		//thread1.join();
		auto future = std::async(std::launch::async, &Element_DamageWall::Damage, this, player);
		
		future.wait(); // メソッドの終了を待つ
	}

}

void Element_DamageWall::Damage(Player *player)
{
	for (int i = 0; i < 360; i++) {
		if (i == 359) {
			player->HpDamage(AttackResource{ 1, nullptr, 5 });
		}
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
}



//void Element_DamageWall::Draw() const
//{
//
//}
