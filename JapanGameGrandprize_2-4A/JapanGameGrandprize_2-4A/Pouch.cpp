#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"


#define FILE_GROUP_ONE (EXPLOSION_MAX_NUM)
#define FILE_GROUP_TWO (FILE_GROUP_ONE + POISON_MAX_NUM)
#define FILE_GROUP_THREE (FILE_GROUP_TWO + POISON_MAX_NUM)
#define FILE_GROUP_FOUR (FILE_GROUP_THREE + POISON_MAX_NUM)
#define FILE_GROUP_FIVE (FILE_GROUP_FOUR + POISON_MAX_NUM)



//コンストラクタ
Pouch::Pouch()
{
	x = 1080;
	y = 100;
	tab = Tab::Explosion_Tab;

	//元素の初期化
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = nullptr;
	}

	InitChemicalParameter();
}


//爆発
void Pouch::ExplosionTabDraw() const 
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff99ff, TRUE);
	DrawString(x, y + 50, "EXPLOSION", 0x000000);
}

//溶解
void Pouch::MeltTabDraw() const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff55ff, TRUE);
	DrawString(x, y + 50, "MELT", 0x000000);
}

//麻痺
void Pouch::ParalysisTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff0099, TRUE);
	DrawString(x, y + 50, "PARALYSIS", 0x000000);
}

//毒
void Pouch::PoisonTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x5500ff, TRUE);
	DrawString(x, y + 50, "POISON", 0x000000);
}

//回復
void Pouch::HealTabDraw()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff1111, TRUE);
	DrawString(x, y + 50, "HEAL", 0x000000);
}

//描画
void Pouch::Draw() const
{
	switch (tab)
	{
	case Tab::Explosion_Tab:
		ExplosionTabDraw();
		break;
	case Tab::Melt_Tab:
		MeltTabDraw();
		break;
	case Tab::Poison_Tab:
		PoisonTabDraw();
		break;
	case Tab::Paralysis_Tab:
		ParalysisTabDraw();
		break;
	case Tab::Heal_Tab:
		HealTabDraw();
		break;
	default:
		break;
	}

	

	DrawBox(x, y + 500, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff00ff, TRUE);

	for (int i = 1; i < 4; i++)
	{
		DrawFormatString(x, y + (100 * i), 0x000000, "%d", chemical_formula_explosion[i].material.carbon);
	}

	for (int i = 0; i < 4; i++)
	{
		DrawBox(x + (50 * i), y + 400, (x + (50 * i)) + 50, y + 450, 0xffffff, FALSE);
		DrawFormatString(x + (50 * i), y + 400, 0x000000, "%d", element[i]->GetVolume());
	}

	for (int i = 0; i < 3; i++)
	{
		DrawBox(x + (50 * i) + 25, y + 450, (x + (50 * i) + 50) + 25, y + POUCH_HEIGHT, 0xffffff, FALSE);
		DrawFormatString(x + (50 * i) + 25, y + 450, 0xffffff, "%d", element[i + 4]->GetVolume());
	}
}

//アップデート
void Pouch::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		switch (tab)
		{
		case Tab::Explosion_Tab:
			tab = Tab::Melt_Tab;
			break;
		case Tab::Melt_Tab:
			tab = Tab::Poison_Tab;
			break;
		case Tab::Poison_Tab:
			tab = Tab::Paralysis_Tab;
			break;
		case Tab::Paralysis_Tab:
			tab = Tab::Heal_Tab;
			break;
		case Tab::Heal_Tab:
			tab = Tab::Explosion_Tab;
			break;
		default:
			break;
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		switch (tab)
		{
		case Tab::Explosion_Tab:
			tab = Tab::Heal_Tab;
			break;
		case Tab::Melt_Tab:
			tab = Tab::Explosion_Tab;
			break;
		case Tab::Poison_Tab:
			tab = Tab::Melt_Tab;
			break;
		case Tab::Paralysis_Tab:
			tab = Tab::Poison_Tab;
			break;
		case Tab::Heal_Tab:
			tab = Tab::Paralysis_Tab;
			break;
		default:
			break;
		}
	}

	switch (tab)
	{
	case Tab::Explosion_Tab:
		ExplosionTabUpdate();
		break;
	case Tab::Melt_Tab:
		MeltTabUpdate();
		break;
	case Tab::Poison_Tab:
		PoisonTabUpdate();
		break;
	case Tab::Paralysis_Tab:
		ParalysisTabUpdate();
		break;
	case Tab::Heal_Tab:
		HealTabUpdate();
		break;
	default:
		break;
	}
}

void Pouch::ExplosionTabUpdate()
{
	
}

void Pouch::PoisonTabUpdate()
{

}

void Pouch::HealTabUpdate()
{

}

void Pouch::MeltTabUpdate()
{

}

void Pouch::ParalysisTabUpdate()
{

}


void Pouch::SetElement(ElementItem* item, int i)
{
	element[i] = item;
}

void Pouch::InitChemicalParameter()
{
	int count = EXPLOSION_MAX_NUM;
	FILE* fp; //FILE型構造体
	errno_t error;     error = fopen_s(&fp, "Data/chemical_formula_data/ChemicalFormulaParameter.csv", "r");
	if (error != 0) //ファイルが開けてない
	{
		return;
	}
	else     //ファイルが開けた
	{
		char line[100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)
		{
			if (i < FILE_GROUP_ONE)
			{
				sscanf_s(line, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
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
					&chemical_formula_explosion[i].atribute);
			}
			else if (i < FILE_GROUP_TWO)
			{
				sscanf_s(line, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
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
					&chemical_formula_poison[i].atribute);
			}
			else if (i < FILE_GROUP_THREE)
			{
				sscanf_s(line, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
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
					&chemical_formula_pararysis[i].atribute);
			}
			else if (i < FILE_GROUP_FOUR)
			{
				sscanf_s(line, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
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
					&chemical_formula_heal[i].atribute);
			}
			else if (i < FILE_GROUP_FIVE)
			{
				sscanf_s(line, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",//入っている数字や文字に合わせてdとかfとか変える
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
					&chemical_formula_melt[i].atribute);
			}
			else;
		}
		return;
	}
	fclose(fp); //ファイルを閉じる
}

ChemicalFormulaParameter Pouch::GetExplosion(int i)
{
	return chemical_formula_explosion[i];
}

ChemicalFormulaParameter Pouch::GetPoison(int i)
{
	return chemical_formula_poison[i];
}

ChemicalFormulaParameter Pouch::GetPararysis(int i)
{
	return chemical_formula_pararysis[i];
}

ChemicalFormulaParameter Pouch::GetHeal(int i)
{
	return chemical_formula_heal[i];
}

ChemicalFormulaParameter Pouch::GetMelt(int i)
{
	return chemical_formula_melt[i];
}
