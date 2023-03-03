#include "Pouch.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"

//コンストラクタ
Pouch::Pouch()
{
	x = 700;
	y = 50;
	tab = Tab::Explosion_Tab;

	//元素の初期化
	element = new ElementItem * [PLAYER_ELEMENT];
	for (int i = 0; i < PLAYER_ELEMENT; i++)
	{
		element[i] = new ElementItem(static_cast<ELEMENT_ITEM>(i));
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



}

//爆発
void Pouch::ExplosionTab () const 
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff99ff, TRUE);
}

//溶解
void Pouch::MeltTab() const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff55ff, TRUE);
}

//麻痺
void Pouch::ParalysisTab()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff0099, TRUE);
}

//毒
void Pouch::PoisonTab()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0x5500ff, TRUE);
}

//回復
void Pouch::HealTab()const
{
	DrawBox(x, y, x + POUCH_WIDTH, y + POUCH_HEIGHT, 0xff1111, TRUE);
}

//描画
void Pouch::Draw() const
{
	switch (tab)
	{
	case Tab::Explosion_Tab:
		ExplosionTab();
		break;
	case Tab::Melt_Tab:
		MeltTab();
		break;
	case Tab::Poison_Tab:
		PoisonTab();
		break;
	case Tab::Paralysis_Tab:
		ParalysisTab();
		break;
	case Tab::Heal_Tab:
		HealTab();
		break;
	default:
		break;
	}


	for (int i = 0; i < 4; i++)
	{
		DrawBox(x + (50 * i), y + 400, (x + (50 * i)) + 50, y + 450, 0xffffff, FALSE);
	}

}