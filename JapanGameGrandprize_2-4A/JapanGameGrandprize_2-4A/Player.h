#pragma once
#include "Define.h"
#include "BoxCollider.h"
#include "BULLET.h"

class Player : public BoxCollider
{
private:
	int image;						//画像用変数
	int image_size_x, image_size_y; //画像のサイズ
	int bullet_count;				//撃った弾の数
	int count;                      //処理をカウントする
    float player_x, player_y;       //プレイヤーの座標
	Player* player;                 //引数で渡す用変数
	

	BULLET* bullet[30];             //弾の配列

public:
	Player();
	~Player() {};
	void Draw()const;
	void Update();

	void Shoot_Gun();

	float GetLocationX() { return location.x; }
	float GetLocationY() { return location.y; }

};

