#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "BULLET.h"





#define GRAVITY 10

class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
	int not_jet_count;              //跳んでない時を数える
	float player_speed;				//プレイヤーの移動スピード（横）
	float fuel;						//燃料
	float jump;                     //ジャンプの値
	float jump_power;               //ジャンプの力
	BULLET_TYPE bullet_type;        //撃つ弾の種類
	

	BULLET** bullet;                //弾の配列

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