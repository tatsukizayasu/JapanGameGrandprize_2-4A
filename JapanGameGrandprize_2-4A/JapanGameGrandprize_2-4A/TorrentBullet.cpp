#include "TorrentBullet.h"
#include "CameraWork.h"

//弾の速度
#define TORRENT_BULLET_SPEED 5

//弾のダメージ
#define TORRENT_BULLET_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
TorrentBullet::TorrentBullet(ENEMY_TYPE type,
	Location spawn_location, Location player_location)
{
	location = spawn_location;
	radius = 6;
	speed = TORRENT_BULLET_SPEED;
	this->type = type;

	image = 0;
	damage = TORRENT_BULLET_DAMAGE;
	float radian; //角度
	radian = atan2f((player_location.y - 10) - location.y, player_location.x - location.x);
	x_speed = speed * cosf(radian);
	y_speed = speed * sinf(radian);
}

//-----------------------------------
//デストラクタ
//-----------------------------------
TorrentBullet::~TorrentBullet()
{

}

//-----------------------------------
//更新
//-----------------------------------
void TorrentBullet::Update()
{
	location.x += x_speed;
	location.y += y_speed;
}

//-----------------------------------
//描画
//-----------------------------------
void TorrentBullet::Draw() const
{
	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawCircle(draw_location.x, draw_location.y, radius, 0x77ff00, TRUE);

}