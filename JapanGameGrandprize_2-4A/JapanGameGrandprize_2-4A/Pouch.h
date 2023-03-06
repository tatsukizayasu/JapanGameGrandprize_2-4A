#pragma once
#include "ElementItem.h"
#include "Define.h"


#define POUCH_WIDTH 200
#define POUCH_HEIGHT 500

enum class Tab
{
	Explosion_Tab = 0,
	Melt_Tab,
	Poison_Tab,
	Paralysis_Tab,
	Heal_Tab
};

class Pouch
{
private:

	float x, y;
	Tab tab;
	ElementItem* element[PLAYER_ELEMENT];
public:

	Pouch();
	~Pouch() {};

	void Update();
	void Draw() const;

	void ExplosionTab() const;
	void PoisonTab() const;
	void MeltTab() const;
	void ParalysisTab() const;
	void HealTab() const;
	void SetElement(ElementItem*,int i);
};