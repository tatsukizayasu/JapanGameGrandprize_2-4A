#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "Bullet.h"
#include "Stage/Stage.h"
#include "EnemyBase.h"
#include "ElementItem.h"
#include "Pouch.h"
#include "DxLib.h"
#include "EnumEnemyType.h"
#include <vector>

#define JUMP_INERTIA 0.2
#define WARK_INERTIA 0.5
#define HP_MAX 100.f
#define HP_BAR_WIDTH 500
#define HP_BAR_HEIGHT 50
#define FUEL_MAX 100.f
#define FUEL_BAR_HEIGHT 100

#define EXPLOSION_MAX_NUM 13	//爆発の化合物の個数
#define POISON_MAX_NUM 18		//毒　の化合物の個数
#define MELT_MAX_NUM 13			//溶解の化合物の個数
#define PARARYSIS_MAX_NUM 11	//麻痺の化合物の個数
#define HEAL_MAX_NUM 7			//回復の化合物の個数

#define BULLET_MAX 50
#define GREEN GetColor(0,255,0)
#define RED GetColor(255,0,0)
#define YELLOW GetColor(255,239,0)

enum class PLAYER_STATE
{
	STOP = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	DOWN,
	DEATH
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
	const char* chemical_formula_name[18];
	const char* chemical_formula[10];
	ATTRIBUTE atribute;
	ChemicalFormulaMaterial material;
};

class Player : public BoxCollider
{
private:

	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int hp;							//体力
	int bullet_count;				//撃った弾の数
	int shoot_count;                //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float gravity_down;				//下降時の値
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	float speed_x;
	float old_x, old_y;				//壁とかに当たった時に元の位置に戻すための変数
	int select_count;
	int damage_count;				//無敵時間
	int flashing_count;				//点滅の間隔
	int i;                          //スイッチ内でのループ用
	int damage;                     //敵から受けたダメージの値

	bool damage_flg;				//ダメージを受けたかどうかのフラグ
	bool move_left;					//プレイヤーの向き true:左　false:右
	bool pouch_open;				//ポーチを開けている
	bool hit_stage;					//ステージのブロックに触れている

	ATTRIBUTE attribute[6];         //弾の属性
	const char* attribute_c[6];     //弾の属性の文字列
	int display_attribute;          //画面に表示させる属性

	PLAYER_STATE player_state;
	
	BulletBase** bullet;             //弾の配列
	Stage* stage;					 //ステージへのポインタ
	EfectBeam* beam;
	Pouch* pouch;					 //ポーチへのポインタ

	ElementItem** element;	//元素

	ChemicalFormulaParameter chemical_formula_explosion[13];
	ChemicalFormulaParameter chemical_formula_poison[18];
	ChemicalFormulaParameter chemical_formula_pararysis[11];
	ChemicalFormulaParameter chemical_formula_heal[7];
	ChemicalFormulaParameter chemical_formula_melt[13];
public:

	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void Update();
	void ElementUpdate();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void NotJump();
	void Shoot_Gun();
	void SortBullet(int);
	void HpDamage(AttackResource);
	void Hp_Heal(int);
	bool HitBlock(const Stage*);
	void InitChemicalParameter();
	void OpenPouch();

	BulletBase** GetBullet()const { return bullet; }
	PLAYER_STATE GetState() { return player_state; }
	ChemicalFormulaParameter GetExplosion(int);
	ChemicalFormulaParameter GetPoison(int);
	ChemicalFormulaParameter GetPararysis(int);
	ChemicalFormulaParameter GetHeal(int);
	ChemicalFormulaParameter GetMelt(int);

	//元素の量の設定
	void SetElementItem(class Item* item);
	//プレイヤーの向き
	bool GetMoveDirection();
};