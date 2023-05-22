#include "TorrentBullet.h"
#include "CameraWork.h"


//弾の速度
#define TORRENT_BULLET_SPEED 7

//弾のダメージ
#define TORRENT_BULLET_DAMAGE 5

//最大値
#define MAX_LEAF_RADIAN 20

//角度の変化量
#define LEAF_ADD_ANGLE 45

//プレイヤーを中心とした半径
#define LEAF_RADIUS 50

//-----------------------------------
//コンストラクタ
//-----------------------------------
TorrentBullet::TorrentBullet(const Location spawn_location, const Location player_location)
{

	location = spawn_location;
	radius = 10;
	speed = TORRENT_BULLET_SPEED;
	type = ENEMY_TYPE::WIND;

	damage = TORRENT_BULLET_DAMAGE;
	float radian; //角度

	radian = atan2f(player_location.y - location.y,
		player_location.x - location.x);

	radian += (M_PI / STRAIGHT_ANGLE) * 
		((static_cast<double>(GetRand(5)) * 6) - MAX_LEAF_RADIAN) ;
	x_speed = static_cast<int>(speed * cosf(radian));
	y_speed = static_cast<int>(speed * sinf(radian));

	images = new int[3];

	LoadDivGraph("Images/Enemy/Torrent/leaf.png", 3, 3, 1, 80, 80, images);

	image = images[GetRand(2)];
	angle = 0;
}

//-----------------------------------
//デストラクタ
//-----------------------------------
TorrentBullet::~TorrentBullet()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(images[i]);
	}
	delete[] images;
}

//-----------------------------------
//更新
//-----------------------------------
void TorrentBullet::Update()
{
	location.x += x_speed;
	location.y += y_speed;
	angle = angle + LEAF_ADD_ANGLE;
}

//-----------------------------------
//描画
//-----------------------------------
void TorrentBullet::Draw() const
{

	Location draw_location = location; //描画座標
	Location camera = CameraWork::GetCamera();

	draw_location = draw_location - camera;

	DrawRotaGraphF(draw_location.x, draw_location.y, 0.4, (M_PI / STRAIGHT_ANGLE) * angle, image, TRUE);
	DrawCircle(draw_location.x, draw_location.y, radius, 0x77ff00, FALSE);
}