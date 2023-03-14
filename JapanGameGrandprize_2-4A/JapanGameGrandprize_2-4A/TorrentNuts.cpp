#include "TorrentNuts.h"
#include "CameraWork.h"

//弾の速度
#define TORRENT_NUTS_SPEED 5

//弾のダメージ
#define TORRENT_NUTS_DAMAGE 5

//-----------------------------------
//コンストラクタ
//-----------------------------------
TorrentNuts::TorrentNuts(ENEMY_TYPE type,
	Location spawn_location)
{
	location = spawn_location;
	radius = 20;
	speed = TORRENT_NUTS_SPEED;
	this->type = type;

	image = 0;
	damage = TORRENT_NUTS_DAMAGE;
	
}

//-----------------------------------
//デストラクタ
//-----------------------------------
TorrentNuts::~TorrentNuts()
{

}

//-----------------------------------
//更新
//-----------------------------------
void TorrentNuts::Update()
{
	location.y += speed;
}

//-----------------------------------
//描画
//-----------------------------------
void TorrentNuts::Draw() const
{
	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location + camera;

	DrawCircle(draw_location.x, draw_location.y, radius, 0xffffff, TRUE);

}