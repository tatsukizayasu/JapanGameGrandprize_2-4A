#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"





//コンストラクタ
Pouch::Pouch()
{
	x = 700;
	y = 200;
	tab = Tab::Explosion_Tab;

	//元素の初期化
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = nullptr;
	}
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

