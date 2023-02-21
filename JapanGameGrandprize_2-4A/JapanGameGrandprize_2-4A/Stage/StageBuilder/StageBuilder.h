#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include <vector>

#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3

#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:
	SphereCollider* mouse;//判定のみ
	Location mouse_pos;
	//ブロック画像
	int block_images[100];
	vector<MapChip*> map_chips;

	int mode;

	int menu_cursor;
	char arrow[ARROW_NUM];

	//todo:テストなので消す ヘッダーも
	class LineCollider2* line;
	

public:
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

	//メニューモードの描画
	void DrawMenu()const;
	//セーブモードの描画
	void DrawFileInfo()const;
	//格子の描画
	void DrawFrame()const;
	//ファイルの描画
	void DrawFile(float x,float y,const char* path ,int font_size)const;

	//マップチップを作成する
	void MakeMapChip();
	void MakeMapChip(float x,float y,float width,float height);

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

