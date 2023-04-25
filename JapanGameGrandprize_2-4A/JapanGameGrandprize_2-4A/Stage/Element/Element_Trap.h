#pragma once
#include "Stage_Element_Base.h"
#include "../EnemyBase.h"
#include "../BULLET.h"
#include "../Stage.h"

class Element_Trap : public Stage_Element_Base
{
private:

	Stage* stage;
	EnemyBase** enemy;
	BulletBase* bullet;
	ChemicalFormulaParameter explosion{};

	enum class STATE {
		NONE,		//なし
		EXPLOSION,	//爆発
		EXTINGUISHMENT	//消滅
	}state;
public:

	//コンストラクタ
	Element_Trap(short type,std::vector<std::shared_ptr<Stage_Element_Base>> element, Stage* stage,EnemyBase** enemy, std::vector<int> images, Location location, Area area);
	//デストラクタ
	~Element_Trap();
	//更新
	void Update(Player* player) override;

	void Draw()const override;
};