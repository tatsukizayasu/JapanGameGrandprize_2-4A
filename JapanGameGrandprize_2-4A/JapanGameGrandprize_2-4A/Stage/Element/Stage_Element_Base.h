#pragma once
#include "../Define.h"
#include <memory>
#include <chrono>
#include <functional>
#include <vector>
#include <thread>
#include "../MapChip.h"

class Player;


class Stage_Element_Base : public MapChip
{
protected:
	
	MapChip* mapchip;
	short type;

	//間隔時間の開始時間
	std::chrono::steady_clock::time_point start_time;
	//ミリ秒単位の時間間隔
	std::chrono::duration<long long, std::milli> elapsed;
	//実行した回数
	int count;


public:
	
	//デフォルトコンストラクタ
	Stage_Element_Base();

	Stage_Element_Base(std::vector<std::shared_ptr<Stage_Element_Base>> element, int* image, Location location, Area area);
	//コンストラクタ
	//Stage_Element(const int* p_image, Location location, Area area);
	//デストラクタ
	~Stage_Element_Base();
	virtual void Update(Player* player) {};
	////描画
	//virtual void Draw() const {};

	/// <summary>
	/// プレイヤーとブロックが当たっているかのGetter
	/// </summary>
	bool HitPlayer(Player* player) const;

	/// <summary>
	/// アニメーションSetter
	/// </summary>
	void StartAnimation(float time, std::function<void()>* callback);

	/// <summary>
	/// アニメーションSetter
	/// </summary>
	float GetAnimationTime() { return elapsed.count() / 1000.0f; };
};