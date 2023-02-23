#pragma once

#define POUCH_SIZE 200


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
};