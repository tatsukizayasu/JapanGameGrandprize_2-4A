#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "Stage/Stage.h"



class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	float speed_x;
	

	Bullet** bullet;             //弾の配列
	Stage* stage;

public:
	Player();
	~Player();
	void Draw()const;
	void Update();

	void Shoot_Gun();
	void SortBullet(int);

	float GetLocationX() { return location.x; }
	float GetLocationY() { return location.y; }

};
