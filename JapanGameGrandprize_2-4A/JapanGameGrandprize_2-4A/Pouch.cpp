#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"
#include "EnumElementItem.h"
#include <stdlib.h>
#include <math.h>

#define STRING_DISTANCE 100

#define OPTION_ZERO OPTION_ONE - STRING_DISTANCE
#define OPTION_ONE 140
#define OPTION_TWO OPTION_ONE + STRING_DISTANCE
#define OPTION_THREE OPTION_TWO + STRING_DISTANCE
#define OPTION_FOUR OPTION_THREE + STRING_DISTANCE


//コンストラクタ
Pouch::Pouch()
{

	x = 1080;
	y = 100;
	cursol = 0;
	count = 0;
	page = 0;
	move_string = 0;
	on_bool = false;
	move_up = false;
	move_down = false;
	tab = ATTRIBUTE::EXPLOSION;
	second_tab_image = LoadGraph("Images/ItemTab/setumei.png");
	elemental_count = LoadGraph("Images/ItemTab/P_kazu.png");

	//元素の初期化
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = nullptr;
	}

	InitChemicalParameter();

	InitializeExplosion();

	InitializeMelt();

	InitializePararysis();

	InitializeHeal();

	InitializePoison();

	element_char[0] = 'H';
	element_char[1] = 'O';
	element_char[2] = 'C';
	element_char[3] = 'N';
	element_char[4] = 'S';
	element_char[5] = 'Ch';
	element_char[6] = 'U';
}

Pouch::~Pouch()
{

}


//爆発
void Pouch::ExplosionTabDraw() const
{
	DrawGraph(x - 254, y - 50, second_tab_image, TRUE);
	DrawFormatString(x - 200, y, 0xffffff, "%s", chemical_formula_explosion[cursol].chemical_formula);
	DrawFormatString(x - 70, y + 30, 0xffffff, "%d", chemical_formula_explosion[cursol].number_of_bullets);
	DrawFormatString(x - 70, y + 60, 0xffffff, "%d", chemical_formula_explosion[cursol].damage);



	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x00ffff, TRUE);
	if (page == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			DrawFormatString(x, y + 80 + (30 * i), 0xffff00, chemical_formula_explosion[i].chemical_formula_name);
		}
	}
	if (page == 1)
	{
		for (int i = 9, j = 0; i < EXPLOSION_MAX_NUM; i++, j++)
		{
			DrawFormatString(x, y + 80 + (30 * j), 0xffff00, chemical_formula_explosion[i].chemical_formula_name);
		}
	}


	ElementDraw(chemical_formula_explosion[cursol]);

	DrawString(x, y, "EXPLOSION", 0xaa5500);


	DrawBox(x, y + 80 + move_string, x + POUCH_WIDTH, y + move_string +110, 0xff00ff, FALSE);
}

//溶解
void Pouch::MeltTabDraw() const
{
	DrawGraph(x - 254, y - 50, second_tab_image, TRUE);
	DrawFormatString(x - 200, y, 0xffffff, "%s", chemical_formula_melt[cursol].chemical_formula);
	DrawFormatString(x - 70, y + 30, 0xffffff, "%d", chemical_formula_melt[cursol].number_of_bullets);
	DrawFormatString(x - 70, y + 60, 0xffffff, "%d", chemical_formula_melt[cursol].damage);



	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x00ffff, TRUE);
	if (page == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			DrawFormatString(x, y + 80 + (30 * i), 0xffff00, chemical_formula_melt[i].chemical_formula_name);
		}
	}
	if (page == 1)
	{
		for (int i = 9, j = 0; i < MELT_MAX_NUM; i++, j++)
		{
			DrawFormatString(x, y + 80 + (30 * j), 0xffff00, chemical_formula_melt[i].chemical_formula_name);
		}
	}


	ElementDraw(chemical_formula_melt[cursol]);

	DrawBox(x, y + 80 + move_string, x + POUCH_WIDTH, y + move_string + 110, 0xff00ff, FALSE);
	DrawString(POUCH_START_X, POUCH_START_Y + 50, "MELT", 0x000000);
}

//麻痺
void Pouch::ParalysisTabDraw()const
{
	DrawGraph(x - 254, y - 50, second_tab_image, TRUE);
	DrawFormatString(x - 200, y, 0xffffff, "%s", chemical_formula_pararysis[cursol].chemical_formula);
	DrawFormatString(x - 70, y + 30, 0xffffff, "%d", chemical_formula_pararysis[cursol].number_of_bullets);
	DrawFormatString(x - 70, y + 60, 0xffffff, "%d", chemical_formula_pararysis[cursol].damage);



	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x00ffff, TRUE);
	if (page == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			DrawFormatString(x, y + 80 + (30 * i), 0xffff00, chemical_formula_pararysis[i].chemical_formula_name);
		}
	}
	if (page == 1)
	{
		for (int i = 9, j = 0; i < PARARYSIS_MAX_NUM; i++, j++)
		{
			DrawFormatString(x, y + 80 + (30 * j), 0xffff00, chemical_formula_pararysis[i].chemical_formula_name);
		}
	}


	ElementDraw(chemical_formula_melt[cursol]);

	DrawBox(x, y + 80 + move_string, x + POUCH_WIDTH, y + move_string + 110, 0xff00ff, FALSE);
	DrawString(POUCH_START_X, POUCH_START_Y + 50, "PARARYSIS", 0x000000);
}

//毒
void Pouch::PoisonTabDraw()const
{
	DrawGraph(x - 254, y - 50, second_tab_image, TRUE);
	DrawFormatString(x - 200, y, 0xffffff, "%s", chemical_formula_poison[cursol].chemical_formula);
	DrawFormatString(x - 70, y + 30, 0xffffff, "%d", chemical_formula_poison[cursol].number_of_bullets);
	DrawFormatString(x - 70, y + 60, 0xffffff, "%d", chemical_formula_poison[cursol].damage);



	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x00ffff, TRUE);
	if (page == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			DrawFormatString(x, y + 80 + (30 * i), 0xffff00, chemical_formula_poison[i].chemical_formula_name);
		}
	}
	if (page == 1)
	{
		for (int i = 9, j = 0; i < POISON_MAX_NUM; i++, j++)
		{
			DrawFormatString(x, y + 80 + (30 * j), 0xffff00, chemical_formula_poison[i].chemical_formula_name);
		}
	}


	ElementDraw(chemical_formula_poison[cursol]);

	DrawBox(x, y + 80 + move_string, x + POUCH_WIDTH, y + move_string + 110, 0xff00ff, FALSE);
	DrawString(POUCH_START_X, POUCH_START_Y + 50, "POISON", 0x000000);
}
//回復
void Pouch::HealTabDraw()const
{
	DrawGraph(x - 254, y - 50, second_tab_image, TRUE);
	DrawFormatString(x - 200, y, 0xffffff, "%s", chemical_formula_heal[cursol].chemical_formula);
	DrawFormatString(x - 70, y + 30, 0xffffff, "%d", chemical_formula_heal[cursol].number_of_bullets);
	DrawFormatString(x - 70, y + 60, 0xffffff, "%d", chemical_formula_heal[cursol].damage);



	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x00ffff, TRUE);
	if (page == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			DrawFormatString(x, y + 80 + (30 * i), 0xffff00, chemical_formula_heal[i].chemical_formula_name);
		}
	}
	if (page == 1)
	{
		for (int i = 9, j = 0; i < HEAL_MAX_NUM; i++, j++)
		{
			DrawFormatString(x, y + 80 + (30 * j), 0xffff00, chemical_formula_heal[i].chemical_formula_name);
		}
	}


	ElementDraw(chemical_formula_heal[cursol]);

	DrawBox(x, y + 80 + move_string, x + POUCH_WIDTH, y + move_string + 110, 0xff00ff, FALSE);
	DrawString(POUCH_START_X, POUCH_START_Y + 50, "HEAL", 0x000000);
}

//描画
void Pouch::Draw() const
{

	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		ExplosionTabDraw();
		break;
	case ATTRIBUTE::MELT:
		MeltTabDraw();
		break;
	case ATTRIBUTE::POISON:
		PoisonTabDraw();
		break;
	case ATTRIBUTE::PARALYSIS:
		ParalysisTabDraw();
		break;
	case ATTRIBUTE::HEAL:
		HealTabDraw();
		break;
	default:
		break;
	}

	DrawBox(POUCH_START_X, POUCH_START_Y + 400, POUCH_START_X + POUCH_WIDTH, POUCH_START_Y + POUCH_HEIGHT, 0xaaaaaa, TRUE);

	for (int i = 0; i < 4; i++)
	{
		DrawBox(POUCH_START_X + (50 * i), POUCH_START_Y + 400, (POUCH_START_X + (50 * i)) + 50, POUCH_START_Y + 450, 0xffffff, FALSE);
		DrawFormatString(POUCH_START_X + (50 * i), POUCH_START_Y + 400, 0x000000, "%d", element[i]->GetVolume());
		DrawFormatString(POUCH_START_X + (50 * i), POUCH_START_Y + 430, 0x000000, "%c", element_char[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		DrawBox(POUCH_START_X + (50 * i) + 25, POUCH_START_Y + 450, (POUCH_START_X + (50 * i) + 50) + 25, POUCH_START_Y + POUCH_HEIGHT, 0xffffff, FALSE);
		DrawFormatString(POUCH_START_X + (50 * i) + 25, POUCH_START_Y + 450, 0xffffff, "%d", element[i + 4]->GetVolume());
		DrawFormatString(POUCH_START_X + (50 * i) + 25, POUCH_START_Y + 480, 0xffffff, "%c", element_char[i + 4]);
	}

	DrawGraph(x - 254, y + 200, elemental_count, TRUE);
}

void Pouch::ElementDraw(ChemicalFormulaParameter bring) const
{
	int i = 0;
	DrawFormatString(x - 180, y + 220, 0xffffff, "%d    %d",
		element[0]->GetVolume(), element[0]->GetVolume() - bring.material.carbon);
	DrawFormatString(x - 180, y + 250 + (30 * i), 0xffffff, "%d    %d",
		element[1]->GetVolume(), element[1]->GetVolume() - bring.material.hydrogen);
	DrawFormatString(x - 180, y + 280 + (30 * i), 0xffffff, "%d    %d",
		element[2]->GetVolume(), element[2]->GetVolume() - bring.material.nitrogen);
	DrawFormatString(x - 180, y + 310 + (30 * i), 0xffffff, "%d    %d",
		element[3]->GetVolume(), element[3]->GetVolume() - bring.material.oxygen);
	DrawFormatString(x - 180, y + 340 + (30 * i), 0xffffff, "%d    %d",
		element[4]->GetVolume(), element[4]->GetVolume() - bring.material.sulfur);
	DrawFormatString(x - 180, y + 370 + (30 * i), 0xffffff, "%d    %d",
		element[5]->GetVolume(), element[5]->GetVolume() - bring.material.chlorine);

}

//アップデート
void Pouch::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		cursol = 0;
		page = 0;
		move_down = false;
		move_up = false;
		move_string = 0;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			tab = ATTRIBUTE::MELT;
			break;
		case ATTRIBUTE::MELT:
			tab = ATTRIBUTE::POISON;
			break;
		case ATTRIBUTE::POISON:
			tab = ATTRIBUTE::PARALYSIS;
			break;
		case ATTRIBUTE::PARALYSIS:
			tab = ATTRIBUTE::HEAL;
			break;
		case ATTRIBUTE::HEAL:
			tab = ATTRIBUTE::EXPLOSION;
			break;
		default:
			break;
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		cursol = 0;
		page = 0;
		move_down = false;
		move_up = false;
		move_string = 0;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			tab = ATTRIBUTE::HEAL;
			break;
		case ATTRIBUTE::MELT:
			tab = ATTRIBUTE::EXPLOSION;
			break;
		case ATTRIBUTE::POISON:
			tab = ATTRIBUTE::MELT;
			break;
		case ATTRIBUTE::PARALYSIS:
			tab = ATTRIBUTE::POISON;
			break;
		case ATTRIBUTE::HEAL:
			tab = ATTRIBUTE::PARALYSIS;
			break;
		default:
			break;
		}
	}

	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		TabUpdate(EXPLOSION_MAX_NUM);
		break;
	case ATTRIBUTE::MELT:
		TabUpdate(MELT_MAX_NUM);
		break;
	case ATTRIBUTE::POISON:
		TabUpdate(POISON_MAX_NUM);
		break;
	case ATTRIBUTE::PARALYSIS:
		TabUpdate(PARARYSIS_MAX_NUM);
		break;
	case ATTRIBUTE::HEAL:
		TabUpdate(HEAL_MAX_NUM);
		break;
	default:
		break;
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		on_bool = true;
		switch (tab)
		{
		case ATTRIBUTE::EXPLOSION:
			if (!select_explosion.make_bool)
			{
				SetChemicalFormulaParameter();
				ConsumptionMaterial();
			}
			break;
		case ATTRIBUTE::MELT:
			if (!select_melt.make_bool)
			{
				SetChemicalFormulaParameter();
				ConsumptionMaterial();
			}
			break;
		case ATTRIBUTE::POISON:
			if (!select_poison.make_bool)
			{
				SetChemicalFormulaParameter();
				ConsumptionMaterial();
			}
			break;
		case ATTRIBUTE::PARALYSIS:
			if (!select_pararysis.make_bool)
			{
				SetChemicalFormulaParameter();
				ConsumptionMaterial();
			}
			break;
		case ATTRIBUTE::HEAL:
			if (!select_heal.make_bool)
			{
				SetChemicalFormulaParameter();
				ConsumptionMaterial();
			}
			break;
		default:
			break;
		}
	}
}

void Pouch::TabUpdate(int max_num)
{
	if (PAD_INPUT::GetRStick().y > 5000)
	{
		if (count++ % 10 == 0)
		{

			switch (page)
			{
			case 0:
				if (cursol > 0)
				{
					move_string -= 30;
					cursol--;
				}
				else
				{
					move_string = 30 * 7;
					cursol = 7;
				}
				break;
			case 1:
				if (cursol > 9)
				{
					move_string -= 30;
					cursol--;
				}
				else
				{
					move_string = 30 * 8;
					cursol = 7;
					if (tab != ATTRIBUTE::HEAL)
					{
						page = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	if (PAD_INPUT::GetRStick().y < -5000)
	{
		if (count++ % 10 == 0)
		{
			switch (page)
			{
			case 0:
				if (cursol < 8)
				{
					move_string += 30;
					cursol++;
				}
				else
				{
					move_string = 0;
					cursol = 9;
					if (tab != ATTRIBUTE::HEAL)
					{
						page = 1;
					}
				}
				break;
			case 1:
				if (cursol < max_num - 1)
				{
					move_string += 30;
					cursol++;
				}
				else
				{
					move_string = 0;
					cursol = 9;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Pouch::SetElement(ElementItem* item, int i)
{

	element[i] = item;
}

void Pouch::SetElementConstruct(int i)
{

	switch (element[i]->GetType())
	{
	case ELEMENT_ITEM::HYDROGEN:
		element[i]->SetVolume(50);
		break;
	case ELEMENT_ITEM::OXYGEN:
		element[i]->SetVolume(30);
		break;
	case ELEMENT_ITEM::CARBON:
		element[i]->SetVolume(30);
		break;
	case ELEMENT_ITEM::NITROGEN:
		element[i]->SetVolume(30);
		break;
	case ELEMENT_ITEM::SULFUR:
		element[i]->SetVolume(10);
		break;
	case ELEMENT_ITEM::CHLORINE:
		element[i]->SetVolume(10);
		break;
	case ELEMENT_ITEM::URANIUM:
		element[i]->SetVolume(1);
		break;
	default:
		break;
	}
}

void Pouch::InitChemicalParameter()
{

	int count = EXPLOSION_MAX_NUM;
	FILE* fp; //FILE型構造体
	errno_t error;
	error = fopen_s(&fp, "Data/chemical_formula_data/ChemicalFormulaParameter.csv", "r");
	if (error != 0) //ファイルが開けてない
	{
		return;
	}
	else     //ファイルが開けた
	{
		int attribute;
		char line[100];
		for (int i = 0; i < EXPLOSION_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_explosion[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_explosion[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_explosion[i].material.carbon,
				&chemical_formula_explosion[i].material.hydrogen,
				&chemical_formula_explosion[i].material.nitrogen,
				&chemical_formula_explosion[i].material.oxygen,
				&chemical_formula_explosion[i].material.sulfur,
				&chemical_formula_explosion[i].material.chlorine,
				&chemical_formula_explosion[i].number_of_bullets,
				&chemical_formula_explosion[i].damage,
				&chemical_formula_explosion[i].damage_per_second,
				&chemical_formula_explosion[i].time,
				&attribute);
			chemical_formula_explosion[i].atribute = static_cast <ATTRIBUTE>(attribute);
			chemical_formula_explosion[i].make_bool = true;
		}
		for (int i = 0; i < POISON_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_poison[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_poison[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_poison[i].material.carbon,
				&chemical_formula_poison[i].material.hydrogen,
				&chemical_formula_poison[i].material.nitrogen,
				&chemical_formula_poison[i].material.oxygen,
				&chemical_formula_poison[i].material.sulfur,
				&chemical_formula_poison[i].material.chlorine,
				&chemical_formula_poison[i].number_of_bullets,
				&chemical_formula_poison[i].damage,
				&chemical_formula_poison[i].damage_per_second,
				&chemical_formula_poison[i].time,
				&attribute);
			chemical_formula_poison[i].atribute = static_cast <ATTRIBUTE>(attribute);
			chemical_formula_poison[i].make_bool = true;
		}

		for (int i = 0; i < PARARYSIS_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_pararysis[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_pararysis[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_pararysis[i].material.carbon,
				&chemical_formula_pararysis[i].material.hydrogen,
				&chemical_formula_pararysis[i].material.nitrogen,
				&chemical_formula_pararysis[i].material.oxygen,
				&chemical_formula_pararysis[i].material.sulfur,
				&chemical_formula_pararysis[i].material.chlorine,
				&chemical_formula_pararysis[i].number_of_bullets,
				&chemical_formula_pararysis[i].damage,
				&chemical_formula_pararysis[i].damage_per_second,
				&chemical_formula_pararysis[i].time,
				&attribute);
			chemical_formula_pararysis[i].atribute = static_cast <ATTRIBUTE>(attribute);
			chemical_formula_pararysis[i].make_bool = true;
		}

		for (int i = 0; i < HEAL_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_heal[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_heal[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_heal[i].material.carbon,
				&chemical_formula_heal[i].material.hydrogen,
				&chemical_formula_heal[i].material.nitrogen,
				&chemical_formula_heal[i].material.oxygen,
				&chemical_formula_heal[i].material.sulfur,
				&chemical_formula_heal[i].material.chlorine,
				&chemical_formula_heal[i].number_of_bullets,
				&chemical_formula_heal[i].damage,
				&chemical_formula_heal[i].damage_per_second,
				&chemical_formula_heal[i].time,
				&attribute);
			chemical_formula_heal[i].atribute = static_cast <ATTRIBUTE>(attribute);
			chemical_formula_heal[i].make_bool = true;

		}

		for (int i = 0; i < MELT_MAX_NUM && (fgets(line, 100, fp) != NULL); i++)
		{
			sscanf_s(line, "%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
				chemical_formula_melt[i].chemical_formula_name,
				MAX_STRING,
				chemical_formula_melt[i].chemical_formula,
				MAX_STRING,
				&chemical_formula_melt[i].material.carbon,
				&chemical_formula_melt[i].material.hydrogen,
				&chemical_formula_melt[i].material.nitrogen,
				&chemical_formula_melt[i].material.oxygen,
				&chemical_formula_melt[i].material.sulfur,
				&chemical_formula_melt[i].material.chlorine,
				&chemical_formula_melt[i].number_of_bullets,
				&chemical_formula_melt[i].damage,
				&chemical_formula_melt[i].damage_per_second,
				&chemical_formula_melt[i].time,
				&attribute);
			chemical_formula_melt[i].atribute = static_cast <ATTRIBUTE>(attribute);
			chemical_formula_melt[i].make_bool = true;
		}
		return;
	}
	fclose(fp); //ファイルを閉じる
}

ChemicalFormulaParameter* Pouch::GetExplosion()
{
	return &select_explosion;
}

ChemicalFormulaParameter* Pouch::GetPoison()
{

	return &select_poison;
}

ChemicalFormulaParameter* Pouch::GetPararysis()
{

	return &select_pararysis;
}

ChemicalFormulaParameter* Pouch::GetHeal()
{

	return &select_heal;
}

ChemicalFormulaParameter* Pouch::GetMelt()
{

	return &select_melt;
}

ATTRIBUTE Pouch::GetAttribute()
{

	return tab;
}

int Pouch::GetCursol()
{

	return cursol;
}

bool Pouch::GetOnBool()
{

	return on_bool;
}

void Pouch::SetOnBool(bool a)
{

	on_bool = a;
}


//-----------------------------------
// 弾を減らす
//-----------------------------------
void Pouch::ReduceAmmo(ATTRIBUTE a)
{

	switch (a)
	{
	case ATTRIBUTE::NORMAL:
		break;
	case ATTRIBUTE::EXPLOSION:
		if (select_explosion.make_bool)
		{
			select_explosion.number_of_bullets--;
		}
		break;
	case ATTRIBUTE::MELT:
		if (select_melt.make_bool)
		{
			select_melt.number_of_bullets--;
		}
		break;
	case ATTRIBUTE::POISON:
		if (select_poison.make_bool)
		{
			select_poison.number_of_bullets--;
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		if (select_pararysis.make_bool)
		{
			select_pararysis.number_of_bullets--;
		}
		break;
	case ATTRIBUTE::HEAL:
		select_heal.number_of_bullets--;
		break;
	default:
		break;
	}
}

void Pouch::SetChemicalFormulaParameter()
{
	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		if (ComparisonElement(chemical_formula_explosion[cursol]))
		{
			select_explosion = chemical_formula_explosion[cursol];
		}
		break;
	case ATTRIBUTE::MELT:
		if (ComparisonElement(chemical_formula_melt[cursol]))
		{
			select_melt = chemical_formula_melt[cursol];
		}
		break;
	case ATTRIBUTE::POISON:
		if (ComparisonElement(chemical_formula_poison[cursol]))
		{
			select_poison = chemical_formula_poison[cursol];
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		if (ComparisonElement(chemical_formula_pararysis[cursol]))
		{
			select_pararysis = chemical_formula_pararysis[cursol];
		}
		break;
	case ATTRIBUTE::HEAL:
		if (ComparisonElement(chemical_formula_heal[cursol]))
		{
			select_heal = chemical_formula_heal[cursol];
		}
		break;
	default:
		break;
	}
}

bool Pouch::ComparisonElement(ChemicalFormulaParameter subject) const
{
	if (subject.material.hydrogen <= element[0]->GetVolume() &&
		subject.material.oxygen <= element[1]->GetVolume() &&
		subject.material.carbon <= element[2]->GetVolume() &&
		subject.material.nitrogen <= element[3]->GetVolume() &&
		subject.material.sulfur <= element[4]->GetVolume() &&
		subject.material.chlorine <= element[5]->GetVolume())
	{
		return true;
	}
	return false;
}

void Pouch::ConsumptionMaterial()
{

	int difference[PLAYER_ELEMENT];
	switch (tab)
	{
	case ATTRIBUTE::EXPLOSION:
		difference[static_cast<int>(ELEMENT_ITEM::HYDROGEN)] = element[0]->GetVolume() - chemical_formula_explosion[cursol].material.hydrogen;
		difference[static_cast<int>(ELEMENT_ITEM::OXYGEN)] = element[1]->GetVolume() - chemical_formula_explosion[cursol].material.oxygen;
		difference[static_cast<int>(ELEMENT_ITEM::CARBON)] = element[2]->GetVolume() - chemical_formula_explosion[cursol].material.carbon;
		difference[static_cast<int>(ELEMENT_ITEM::NITROGEN)] = element[3]->GetVolume() - chemical_formula_explosion[cursol].material.nitrogen;
		difference[static_cast<int>(ELEMENT_ITEM::SULFUR)] = element[4]->GetVolume() - chemical_formula_explosion[cursol].material.sulfur;
		difference[static_cast<int>(ELEMENT_ITEM::CHLORINE)] = element[5]->GetVolume() - chemical_formula_explosion[cursol].material.chlorine;
		for (int i = 0; i < PLAYER_ELEMENT - 1; i++)
		{
			element[i]->SetVolume(difference[i]);
		}
		break;
	case ATTRIBUTE::MELT:
		difference[static_cast<int>(ELEMENT_ITEM::HYDROGEN)] = element[0]->GetVolume() - chemical_formula_melt[cursol].material.hydrogen;
		difference[static_cast<int>(ELEMENT_ITEM::OXYGEN)] = element[1]->GetVolume() - chemical_formula_melt[cursol].material.oxygen;
		difference[static_cast<int>(ELEMENT_ITEM::CARBON)] = element[2]->GetVolume() - chemical_formula_melt[cursol].material.carbon;
		difference[static_cast<int>(ELEMENT_ITEM::NITROGEN)] = element[3]->GetVolume() - chemical_formula_melt[cursol].material.nitrogen;
		difference[static_cast<int>(ELEMENT_ITEM::SULFUR)] = element[4]->GetVolume() - chemical_formula_melt[cursol].material.sulfur;
		difference[static_cast<int>(ELEMENT_ITEM::CHLORINE)] = element[5]->GetVolume() - chemical_formula_melt[cursol].material.chlorine;
		for (int i = 0; i < PLAYER_ELEMENT - 1; i++)
		{
			element[i]->SetVolume(difference[i]);
		}
		break;
	case ATTRIBUTE::POISON:
		difference[static_cast<int>(ELEMENT_ITEM::HYDROGEN)] = element[0]->GetVolume() - chemical_formula_poison[cursol].material.hydrogen;
		difference[static_cast<int>(ELEMENT_ITEM::OXYGEN)] = element[1]->GetVolume() - chemical_formula_poison[cursol].material.oxygen;
		difference[static_cast<int>(ELEMENT_ITEM::CARBON)] = element[2]->GetVolume() - chemical_formula_poison[cursol].material.carbon;
		difference[static_cast<int>(ELEMENT_ITEM::NITROGEN)] = element[3]->GetVolume() - chemical_formula_poison[cursol].material.nitrogen;
		difference[static_cast<int>(ELEMENT_ITEM::SULFUR)] = element[4]->GetVolume() - chemical_formula_poison[cursol].material.sulfur;
		difference[static_cast<int>(ELEMENT_ITEM::CHLORINE)] = element[5]->GetVolume() - chemical_formula_poison[cursol].material.chlorine;
		for (int i = 0; i < PLAYER_ELEMENT - 1; i++)
		{
			element[i]->SetVolume(difference[i]);
		}
		break;
	case ATTRIBUTE::PARALYSIS:
		difference[static_cast<int>(ELEMENT_ITEM::HYDROGEN)] = element[0]->GetVolume() - chemical_formula_pararysis[cursol].material.hydrogen;
		difference[static_cast<int>(ELEMENT_ITEM::OXYGEN)] = element[1]->GetVolume() - chemical_formula_pararysis[cursol].material.oxygen;
		difference[static_cast<int>(ELEMENT_ITEM::CARBON)] = element[2]->GetVolume() - chemical_formula_pararysis[cursol].material.carbon;
		difference[static_cast<int>(ELEMENT_ITEM::NITROGEN)] = element[3]->GetVolume() - chemical_formula_pararysis[cursol].material.nitrogen;
		difference[static_cast<int>(ELEMENT_ITEM::SULFUR)] = element[4]->GetVolume() - chemical_formula_pararysis[cursol].material.sulfur;
		difference[static_cast<int>(ELEMENT_ITEM::CHLORINE)] = element[5]->GetVolume() - chemical_formula_pararysis[cursol].material.chlorine;
		for (int i = 0; i < PLAYER_ELEMENT - 1; i++)
		{
			element[i]->SetVolume(difference[i]);
		}
		break;
	case ATTRIBUTE::HEAL:
		difference[static_cast<int>(ELEMENT_ITEM::HYDROGEN)] = element[0]->GetVolume() - chemical_formula_heal[cursol].material.hydrogen;
		difference[static_cast<int>(ELEMENT_ITEM::OXYGEN)] = element[1]->GetVolume() - chemical_formula_heal[cursol].material.oxygen;
		difference[static_cast<int>(ELEMENT_ITEM::CARBON)] = element[2]->GetVolume() - chemical_formula_heal[cursol].material.carbon;
		difference[static_cast<int>(ELEMENT_ITEM::NITROGEN)] = element[3]->GetVolume() - chemical_formula_heal[cursol].material.nitrogen;
		difference[static_cast<int>(ELEMENT_ITEM::SULFUR)] = element[4]->GetVolume() - chemical_formula_heal[cursol].material.sulfur;
		difference[static_cast<int>(ELEMENT_ITEM::CHLORINE)] = element[5]->GetVolume() - chemical_formula_heal[cursol].material.chlorine;
		for (int i = 0; i < PLAYER_ELEMENT - 1; i++)
		{
			element[i]->SetVolume(difference[i]);
		}
		break;
	default:
		break;
	}
}

void Pouch::InitializeExplosion()
{
	select_explosion = { 0 };
	select_explosion.make_bool = false;
}

void Pouch::InitializeHeal()
{
	select_heal = { 0 };
	select_heal.make_bool = false;
}

void Pouch::InitializeMelt()
{
	select_melt = { 0 };
	select_melt.make_bool = false;
}

void Pouch::InitializePararysis()
{

	select_pararysis = { 0 };
	select_pararysis.make_bool = false;
}

void Pouch::InitializePoison()
{
	select_poison = { 0 };
	select_poison.make_bool = false;
}