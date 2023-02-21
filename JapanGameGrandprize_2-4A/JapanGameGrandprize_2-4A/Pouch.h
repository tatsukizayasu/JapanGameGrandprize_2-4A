#pragma once

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
	float pouch_x, pouch_y;

public:
	Pouch();
	~Pouch() {};

	void Update();
	void Draw() const;

	void ExplosionTab();
	void PoisonTab();
	void MeltTab();
	void ParalysisTab();
	void HealTab();
};