#pragma once
#include "ElementItem.h"
#include "Define.h"

#define EXPLOSION_MAX_NUM 13	//”š”­‚Ì‰»‡•¨‚ÌŒÂ”
#define POISON_MAX_NUM 18		//“Å@‚Ì‰»‡•¨‚ÌŒÂ”
#define MELT_MAX_NUM 13			//—n‰ğ‚Ì‰»‡•¨‚ÌŒÂ”
#define PARARYSIS_MAX_NUM 11	//–ƒáƒ‚Ì‰»‡•¨‚ÌŒÂ”
#define HEAL_MAX_NUM 7			//‰ñ•œ‚Ì‰»‡•¨‚ÌŒÂ”

#define MAX_STRING 40

#define POUCH_WIDTH 200
#define POUCH_HEIGHT 500

struct ChemicalFormulaMaterial
{
	int carbon;		//’Y‘f
	int hydrogen;	//…‘f
	int nitrogen;	//’‚‘f
	int oxygen;		//_‘f
	int sulfur;		//—°‰©
	int chlorine;	//‰–‘f
	int uranium;	//ƒEƒ‰ƒ“
};

struct ChemicalFormulaParameter
{
	int number_of_bullets;
	int time;
	int damage_per_second;
	int damage;
	const char* chemical_formula_name[MAX_STRING];
	const char* chemical_formula[MAX_STRING];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
};


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

	ChemicalFormulaParameter chemical_formula_explosion[EXPLOSION_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_poison[POISON_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_pararysis[PARARYSIS_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_heal[HEAL_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_melt[MELT_MAX_NUM];
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

	void InitChemicalParameter();

	ChemicalFormulaParameter GetExplosion(int);
	ChemicalFormulaParameter GetPoison(int);
	ChemicalFormulaParameter GetPararysis(int);
	ChemicalFormulaParameter GetHeal(int);
	ChemicalFormulaParameter GetMelt(int);
};