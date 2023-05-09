#pragma once
#include "ElementItem.h"
#include "Define.h"

#define CURSOL_SPEED 12

#define ATTRIBUTE_IMAGES 10
#define POUCH_WIDTH 200
#define POUCH_HEIGHT 500
#define POUCH_START_X 1080
#define POUCH_START_Y 100

class Pouch
{
private:

	short old;
	float x, y;
	int window_x, window_y;
	int attribute_name_x, attribute_name_y;
	int second_tab_image[4];
	int* attribute_images;
	int window_image;
	int window_image_two;
	int text_window_image_lit;
	int text_window_image_dark;
	int elemental_count;
	int page_jump_count;
	int cursol;
	int each_cursor[5];
	int each_page[5];
	int count;
	int page;
	int move_string;	//選択肢の移動量
	bool on_bool;
	bool move_up;		//選択肢を上に動かす時のフラグ
	bool move_down;		//選択肢を下に動かす時のフラグ
	char element_char[PLAYER_ELEMENT];
	ATTRIBUTE tab;
	ElementItem* element[PLAYER_ELEMENT];

	ChemicalFormulaParameter chemical_formula_explosion[EXPLOSION_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_poison[POISON_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_pararysis[PARARYSIS_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_heal[HEAL_MAX_NUM];
	ChemicalFormulaParameter chemical_formula_melt[MELT_MAX_NUM];

	ChemicalFormulaParameter select_explosion;
	ChemicalFormulaParameter select_poison;
	ChemicalFormulaParameter select_pararysis;
	ChemicalFormulaParameter select_heal;
	ChemicalFormulaParameter select_melt;
public:

	Pouch();
	~Pouch();

	void Update();
	void Draw() const;
	void ElementDraw(ChemicalFormulaParameter) const;

	void TabUpdate(int);

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
	void InitializeExplosion();
	void InitializePoison();
	void InitializeMelt();
	void InitializeHeal();
	void InitializePararysis();

	void InitializeDisplayChemicalFormula();
};
