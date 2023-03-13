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

	void ExplosionTabUpdate();
	void PoisonTabUpdate();
	void MeltTabUpdate();
	void ParalysisTabUpdate();
	void HealTabUpdate();

	void ExplosionTabDraw() const;
	void PoisonTabDraw() const;
	void MeltTabDraw() const;
	void ParalysisTabDraw() const;
	void HealTabDraw() const;
	void SetElement(ElementItem*,int i);
};