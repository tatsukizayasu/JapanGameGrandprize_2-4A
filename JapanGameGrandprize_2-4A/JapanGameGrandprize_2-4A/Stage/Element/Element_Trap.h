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
	Element_Trap(short type, Stage* stage,EnemyBase** enemy, Resource resource, Location location, Area area);
	//デストラクタ
	~Element_Trap();
	//更新
	void Update(Player* player) override;

	void Draw()const override;
};