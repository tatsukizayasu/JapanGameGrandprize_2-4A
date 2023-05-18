#pragma once

//îºåa
#define RADIUS 180

//íºåa
#define DIAMETER RADIUS * 2

//ÉvÉåÉCÉÑÅ[Ç™éùÇ¡ÇƒÇ¢ÇÈå≥ëfÇÃéÌóﬁ
#define PLAYER_ELEMENT 7

#define SCREEN_HEIGHT 720	//âÊñ ÉTÉCÉY (èc)
#define SCREEN_WIDTH 1280	//âÊñ ÉTÉCÉY (â°)
#define GRAVITY 10 //èdóÕ

#define BULLET_KINDS 5		//í≤çáÇ≈Ç´ÇÈíeÇÃéÌóﬁêî
#define EXPLOSION_MAX_NUM 5	//îöî≠ÇÃâªçáï®ÇÃå¬êî
#define POISON_MAX_NUM 5		//ì≈Å@ÇÃâªçáï®ÇÃå¬êî
#define MELT_MAX_NUM 5			//ónâÇÃâªçáï®ÇÃå¬êî
#define PARARYSIS_MAX_NUM 5	//ñÉ·ÉÇÃâªçáï®ÇÃå¬êî
#define HEAL_MAX_NUM 2			//âÒïúÇÃâªçáï®ÇÃå¬êî

#define GREEN GetColor(0,255,0)
#define RED GetColor(255,0,0)
#define YELLOW GetColor(255,239,0)

#define MAX_STRING 40			//íeÇÃñºëOÇÃç≈ëÂï∂éöêî
#define PARTICLE  20			//íeÇÃÉGÉtÉFÉNÉgÅFÉpÅ[ÉeÉBÉNÉãêî

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
	int carbon;		//íYëf
	int hydrogen;	//êÖëf
	int nitrogen;	//íÇëf
	int oxygen;		//é_ëf
	int sulfur;		//ó∞â©
	int chlorine;	//âñëf
	int uranium;	//ÉEÉâÉì
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

//íÜêSç¿ïW
struct Location
{
	float x;	//íÜêSç¿ïW(x)
	float y;	//íÜêSç¿ïW(y)

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

//ÉTÉCÉY
struct Area
{
	float height;	//èc
	float width;	//â°
};