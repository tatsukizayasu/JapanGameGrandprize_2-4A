#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include "PolyLine.h"
#include <vector>

//モードの数とその種類------
#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3
//--------------------------

//ブラシの数とその種類---------
#define CLASS_NUM 2	
#define MAP_CHIP 0
#define POLY_LINE 1
//-----------------------------

#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:
	const char* class_name[CLASS_NUM] =
	{
		"default_map_chip",
		"poly_line"
	};

	SphereCollider* mouse;
	Location mouse_pos;
	int block_images[100];		//ブロック画像
	vector<MapChip*> map_chips;
	ColliderBase* select_collider;
	int mode;

	int menu_cursor;
	char arrow[ARROW_NUM];
	int current_brush;

	//todo:テスト 後々vector配列にして運用する
	class PolyLine* line;


	//コンストラクタ
	StageBuilder();
	//デストラクタ
	~StageBuilder();
	//更新
	void Update();
	//描画
	void Draw()const;

	//メニューモードの更新
	void UpdateMenu();
	//ブラシモードの更新
	void UpdateBrush();
	//モデュレーションモードの更新
	void UpdateModulation();
	//セーブモードの更新
	void UpdateSave();
	//ロードモードの更新
	void UpdateLoad();
	//マウスの更新
	void UpdateMouse();

	//モードごとに分かれた描画
	void DrawWhichMode()const;
	//メニューモードの描画
	void DrawMenu()const;
	//セーブモードの描画
	void DrawFileInfo()const;
	//格子の描画
	void DrawFrame()const;
	//ファイルの描画
	void DrawFile(float x, float y, const char* path, int font_size)const;
	//現在のブラシになっているクラスを描画
	void DrawClassName()const;

	//マップチップを作成する
	void MakeMapChip(); //クリックしたとき用
	void MakeMapChip(float x, float y, float width, float height); //CSVファイルからの読み込み用

	//コリジョンクラスを作成する
	//折れ線
	void MakePolyLine();
	//円
	void MakeSphere();
	//線
	void MakeLine();
	//線を作り切れなかったときにリセットする
	void LineReset() {}

	//ファイルカウント
	int FileCount(const char* path)const;

	//メニュー選択
	void Select(int menu_max);

	const int* GetImage(int image_index)const;

	//CSVファイルへの書き出し(新規追加)
	void SaveStage(int stage_num);
	//上書き保存
	void SaveStage(char* stage_name);
	//CSVファイルからの読み込み
	void LoadStage(char* stage_name);
};