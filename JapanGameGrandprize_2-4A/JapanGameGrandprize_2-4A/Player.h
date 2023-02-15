#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "EfectBeam.h"
#include "BULLET.h"
#include "Stage/Stage.h"



class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float gravity_down;				//下降時の値
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	float speed_x;
	int select_count;

	Attribute attribute[6];         //弾の属性
	int attribute_c[6];
	int display_attribute; //画面に表示させる属性
	
	Bullet** bullet;             //弾の配列
	Stage* stage;
	EfectBeam* beam;

public:
	Player();
	~Player();
	void Draw()const;
	void Update();
	void Element_Update();

	void Shoot_Gun();
	void SortBullet(int);

	Bullet* GetBullet(int i) { return bullet[i]; }

};
