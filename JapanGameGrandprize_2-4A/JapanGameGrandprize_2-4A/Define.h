#pragma once

//180°
#define STRAIGHT_ANGLE 180

//360°
#define COMPLETE_ANGLE STRAIGHT_ANGLE * 2

//プレイヤーが持っている元素の種類
#define PLAYER_ELEMENT 7

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)
#define GRAVITY 10 //重力

#define BULLET_KINDS 5		//調合できる弾の種類数
#define EXPLOSION_MAX_NUM 5	//爆発の化合物の個数
#define POISON_MAX_NUM 5		//毒　の化合物の個数
#define MELT_MAX_NUM 5			//溶解の化合物の個数
#define PARARYSIS_MAX_NUM 5	//麻痺の化合物の個数
#define HEAL_MAX_NUM 2			//回復の化合物の個数

#define GREEN GetColor(0,255,0)
#define RED GetColor(255,0,0)
#define YELLOW GetColor(255,239,0)

#define MAX_STRING 40			//弾の名前の最大文字数
#define PARTICLE  20			//弾のエフェクト：パーティクル数

enum class ATTRIBUTE
{
	NORMAL = 0,
	EXPLOSION,
	MELT,
	POISON,
	PARALYSIS,
	HEAL
};

enum class COLLIDER
{
	DEFAULT = 0
	,SPHERE
	,BOX
	,LINE
	,POLY_LINE
};

struct ChemicalFormulaMaterial
{
	int carbon;		//炭素
	int hydrogen;	//水素
	int nitrogen;	//窒素
	int oxygen;		//酸素
	int sulfur;		//硫黄
	int chlorine;	//塩素
	int uranium;	//ウラン
};

struct ChemicalFormulaParameter
{
	int number_of_bullets;
	int time;
	int damage_per_second;
	int damage;
	char chemical_formula_name[MAX_STRING];
	char chemical_formula[MAX_STRING];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
	bool make_bool;
	int name_image;
	int tag_number;
	int dark_name_image;
	int ui_name_image;

};

struct Bullet_Effect {
	int Tick;
	int speed;
	int image;
	int image_Array[30];
	int frame;

	int x;
	int y;
	int x_Array[PARTICLE];
	int y_Array[PARTICLE];
	float X_radius;
	float Y_radius;

	int display_permit_Array[PARTICLE];
	int display_permit;

	int BrendMode_ALPFA_Array[PARTICLE];
	int BrendMode_ALPFA;

	float OvalY_Array_radius[PARTICLE];
	int OvalY_Array_permit[PARTICLE];
};

struct Delete_Effect {
	int Delete_x;
	int Delete_y;
	int Delete_display_permit;
	int Delete_image_array[10];
	int Delete_frame;
};

struct Heal_Effect {
	int Tick;
	int x;
	int y;
	int display_permit;
	int image_array[20];
	int frame;
};

//中心座標
struct Location
{
	float x;	//中心座標(x)
	float y;	//中心座標(y)

	Location operator +(Location location)
	{
		Location ret;

		ret.x = this->x + location.x;
		ret.y = this->y + location.y;

		return ret;
	}

	Location operator -(Location location)
	{
		Location ret;

		ret.x = this->x - location.x;
		ret.y = this->y - location.y;

		return ret;
	}

	Location operator /(Location location)
	{
		Location ret;

		ret.x = this->x / location.x;
		ret.y = this->y / location.y;

		return ret;
	}

	Location operator /(int num)
	{
		Location ret;

		ret.x = this->x / num;
		ret.y = this->y / num;

		return ret;
	}

	bool operator <(Location location)
	{
		bool ret;

		ret = (this->x < location.x) && (this->y < location.y);

		return ret;
	}

	bool operator >(Location location)
	{
		bool ret;

		ret = (this->x > location.x) && (this->y > location.y);

		return ret;
	}

	bool operator <=(Location location)
	{
		bool ret;

		ret = (this->x <= location.x) && (this->y <= location.y);

		return ret;
	}

	bool operator >=(Location location)
	{
		bool ret;

		ret = (this->x >= location.x) && (this->y >= location.y);

		return ret;
	}

	bool operator !=(Location location)
	{
		bool ret;

		ret = (this->x != location.x) || (this->y != location.y);

		return ret;
	}

	bool operator ==(Location location)
	{
		bool ret;

		ret = (this->x == location.x) && (this->y == location.y);

		return ret;
	}
};

//サイズ
struct Area
{
	float height;	//縦
	float width;	//横
};