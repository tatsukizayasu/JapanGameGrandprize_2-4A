#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "Bullet.h"
#include "Stage/Stage.h"

#define JUMP_INERTIA 0.2
#define WARK_INERTIA 0.5
#define HP_MAX 100

enum class PlayerState
{
	stop = 0,
	move_left,
	move_right,
	jump,
	down,
	death
};



class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int hp;							//体力
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float gravity_down;				//下降時の値
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	float speed_x;
	int select_count;
	int i;                          //スイッチ内でのループ用

	Player* player;

	Attribute attribute[6];         //弾の属性
	int attribute_c[6];
	int display_attribute; //画面に表示させる属性

	PlayerState player_state;
	
	
	Bullet** bullet;             //弾の配列
	Stage* stage;                //ステージへのポインタ
	EfectBeam* beam;

public:
	Player();
	Player(Stage*);
	~Player();
	void Draw()const;
	void Update();
	void Element_Update();

	void RightMove();
	void LeftMove();
	void NotInputStick();
	void Jump();
	void NotJump();
	void Shoot_Gun();
	void SortBullet(int);
	void Hp_Damage(int);
	void Hp_Heal(int);

	Bullet* GetBullet(int i) { return bullet[i]; }
	PlayerState GetState() { return player_state; }

	POINT collision_dir;

};
