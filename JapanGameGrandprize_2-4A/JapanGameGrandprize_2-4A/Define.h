#pragma once

//ÉvÉåÉCÉÑÅ[Ç™éùÇ¡ÇƒÇ¢ÇÈå≥ëfÇÃéÌóﬁ
#define PLAYER_ELEMENT 7

#define SCREEN_HEIGHT 720	//âÊñ ÉTÉCÉY (èc)
#define SCREEN_WIDTH 1280	//âÊñ ÉTÉCÉY (â°)
#define GRAVITY 10 //èdóÕ

#define EXPLOSION_MAX_NUM 13	//îöî≠ÇÃâªçáï®ÇÃå¬êî
#define POISON_MAX_NUM 18		//ì≈Å@ÇÃâªçáï®ÇÃå¬êî
#define MELT_MAX_NUM 13			//ónâÇÃâªçáï®ÇÃå¬êî
#define PARARYSIS_MAX_NUM 12	//ñÉ·ÉÇÃâªçáï®ÇÃå¬êî
#define HEAL_MAX_NUM 7			//âÒïúÇÃâªçáï®ÇÃå¬êî

#define MAX_STRING 40			//íeÇÃñºëOÇÃç≈ëÂï∂éöêî

//âªçáï®ç\ë¢ëÃ
struct Compound
{
	int warter;				//êÖ
	int carbon_dioxide;		//ìÒé_âªíYëf
	int ozone;				//ÉIÉ]Éì
	int sulfuric_acid;		//ó∞é_
	int hydrochloric_acid;	//âñé_
	int alcohol;			//ÉAÉãÉRÅ[Éã
	int tear_gas;			//ç√ó‹ÉKÉX
	int suger;				//çªìú
	int ammonium_chloride;  //âñâªÉAÉìÉÇÉjÉEÉÄ
	int acetic_acid;		//ê|é_
	int propane;			//ÉvÉçÉpÉì
	int uranium;			//ÉEÉâÉì
};

enum class ATTRIBUTE
{
	NORMAL = 0,
	EXPLOSION,
	MELT,
	POISON,
	PARALYSIS,
	HEAL
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