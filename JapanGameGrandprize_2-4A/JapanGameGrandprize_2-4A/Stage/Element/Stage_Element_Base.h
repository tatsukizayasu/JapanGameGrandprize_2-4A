#pragma once
#include "../Define.h"
#include <memory>
#include <chrono>
#include <functional>
#include <vector>
#include <thread>
#include <unordered_map>
#include "../MapChip.h"
#include <tuple>

class Player;

//struct RECT
//{
//	float x;
//	float y;
//	float width;
//	float height;
//};

enum class HIT_DIRECTION
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Stage_Element_Base : public MapChip
{
protected:
	
	MapChip* mapchip;
	short type;

	//LoopImagesの開始時間
	std::chrono::steady_clock::time_point start_time;

	//グラフィックハンドル用Vector
	std::vector<int> images;
	
	//実行した回数
	int count;

	//各time値に対応する開始時刻を格納するマップ
	std::unordered_map<float, std::chrono::steady_clock::time_point> start_time_map;

	//各time値に対応するミリ秒単位の経過時間を格納するマップ
	std::unordered_map<float, float> elapsed_time_map;

	//描画している画像カウント
	int current_image;
public:
	
	//デフォルトコンストラクタ
	Stage_Element_Base();

	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	virtual ~Stage_Element_Base();
	virtual void Update(Player* player) {};
	////描画
	//virtual void Draw() const {};

	short GetType() const { return type; };

	/// <summary>
	/// アニメーション用ループタイマー
	/// </summary>
	/// <param name = "*images">画像列ポインタ</param>
	/// <param name = "time">秒数</param>
	/// <param name = "total_images">画像総数</param>
	/// <param name = "std::function* callback">timeで指定した秒数毎に呼ぶ関数
	/// <para>　　　　　　　　　呼び出したい関数がない場合はnullptr</para></param>
	void LoopImages(std::vector<int>& images, float time, int total_images, std::function<void()>* callback);

	/// <summary>
	/// プレイヤーとブロックが当たっているかのGetter
	/// </summary>
	/// <returns>false:当たっていない
	/// <para>true:当たっている</para></returns>	
	//bool HitPlayer(Player* player) const;

	/// <summary>
	/// プレイヤーとブロックが当たっているか
	/// <para>と当たっている方向のGetter</para>
	/// </summary>
	/// <returns>tuple(bool型, HITDIRECTION構造体型)
	// <para>false:当たっていない</para>
	/// <para>true:当たっている</para>
	/// <para>HITDIRECTION::NONE:当たっていない</para>
	/// <para>HITDIRECTION::UP:上</para>
	/// <para>HITDIRECTION::DOWN;下</para>
	/// <para>HITDIRECTION::LEFT:左</para>
	/// <para>HITDIRECTION::RIGHT:右</para></returns>	
	std::tuple<bool, HIT_DIRECTION> HitPlayer(Player* player) const;

	/// <summary>
	/// ループタイマー		Setter
	/// </summary>
	/// <param name = "time">秒数</param>
	/// <param name = "std::function* callback">timeで指定した秒数毎に呼ぶ関数
	/// <para>　　　　　　　　　呼び出したい関数がない場合はnullptr</para></param>
	void LoopTimer(float time, std::function<void()>* callback);

	/// <summary>
	/// ルームタイマー	の経過時間	Getter
	/// </summary>
	/// <param name = "time">取得したいタイマーの秒数</param>
	/// <returns>経過時間</returns>	
	float GetElapsedTime(float time) const;

	/// <summary>
	/// ルームタイマー	の経過時間リセット
	/// </summary>
	/// <param name = "time">リセットしたいタイマーの秒数</param>
	void ResetElapsedTime(float time);
};