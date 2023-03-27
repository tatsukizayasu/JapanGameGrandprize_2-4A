#pragma once
#include "ElementItem.h"
#include "Define.h"


#define CURSOL_SPEED 30

#define POUCH_WIDTH 200
#define POUCH_HEIGHT 500




class Pouch
{
private:
	float x, y;
	int cursol;
	int count;
	bool on_bool;
	ATTRIBUTE tab;
	ElementItem* element[PLAYER_ELEMENT];

	ChemicalFormulaParameter chemical_formula_explosion[EXPLOSION_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_poison[POISON_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_pararysis[PARARYSIS_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_heal[HEAL_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_melt[MELT_MAX_NUM];

	ChemicalFormulaParameter* select_explosion;
	ChemicalFormulaParameter* select_poison;
	ChemicalFormulaParameter* select_pararysis;
	ChemicalFormulaParameter* select_heal;
	ChemicalFormulaParameter* select_melt;

public:
	Pouch();
	~Pouch();

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
	void SetElementConstruct(int i);

	void InitChemicalParameter();

	ChemicalFormulaParameter* GetExplosion();
	ChemicalFormulaParameter* GetPoison();
	ChemicalFormulaParameter* GetPararysis();
	ChemicalFormulaParameter* GetHeal();
	ChemicalFormulaParameter* GetMelt();
	ATTRIBUTE GetAttribute();

	void SetChemicalFormulaParameter();
	int GetCursol();
	bool GetOnBool();
	bool ComparisonElement(ChemicalFormulaParameter) const;
	void SetOnBool(bool);
	void ReduceAmmo(ATTRIBUTE);
	void ConsumptionMaterial();
	void DeleteExplosion();
	void DeletePoison();
	void DeleteMelt();
	void DeleteHeal();
	void DeletePararysis();
};
