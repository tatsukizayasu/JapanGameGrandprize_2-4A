#pragma once

//エネミーの種類
enum class ENEMY_KIND
{
	/*雑魚敵*/
	SLIME = 200,//スライム
	UNDEAD,		//アンデット
	HARPY,		//ハーピィ
	MAGE,		//メイジ
	GHOST,		//ゴースト
	WYVERN,		//ワイバーン

	/*ボス*/
	SLIME_BOSS, //スライムキング
	TORRENT,	//トレント
	KRAKEN,	    //クラーケン
	DRAGON,		//ドラゴン
	LAST_BOSS,	//ラスボス
	NONE
};
