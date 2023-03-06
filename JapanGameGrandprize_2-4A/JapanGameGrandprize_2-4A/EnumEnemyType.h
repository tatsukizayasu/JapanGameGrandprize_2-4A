#pragma once

//属性
enum class ENEMY_TYPE
{
	NORMAL = 0,	//無属性
	FIRE,		//火属性
	WATER,		//水属性
	WIND,		//風属性
	SOIL,		//土属性
	THUNDER,	//雷属性
};

struct AttackResource
{
	int damage; //ダメージ
	ENEMY_TYPE* type; //攻撃タイプ
	int type_count; //攻撃タイプの数
};