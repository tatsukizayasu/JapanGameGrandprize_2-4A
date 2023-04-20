#pragma once
#include "Debug.h"
#include "../Define.h"
#include "KeyManager.h"
#include "../MapChip.h"
#include "../SphereCollider.h"
#include "../../LineCollider.h"
#include "PolyLine.h"
#include "ObjectBase.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//sphereColliderは約3600個程度ならフレームレートを落とさず更新できる

#ifdef _STAGE_BUILDER

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
#define BRUSH_MAP_CHIP 0
#define BRUSH_POLY_LINE 1
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

	//インタフェース
	SphereCollider* mouse;
	ColliderBase* select_collider;
	int menu_cursor;
	char arrow[ARROW_NUM];

	//デフォルトマップチップ
	int block_images[110];		//ブロック画像
	vector<MapChip*> map_chips;
	vector<PolyLine*>poly_lines;
	vector<ObjectBase*>objects;

	//保留中のスフィア
	vector<SphereCollider*> pending_sphere;

	//ツール用
	int mode;
	int current_brush;

	//todo:テスト 
	vector<BoxCollider*> boxes;

public:
	/*******************更新描画系統*******************/
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
	//マウスの描画
	void DrawMouse()const;
	//ファイルの描画
	void DrawFile(float x, float y, const char* path, int font_size)const;
	//現在のブラシになっているクラスを描画
	void DrawClassName()const;
	//保留中のスフィアの描画
	void DrawSphere()const;
	//保留中のラインの描画
	void DrawLine(Location start, Location end)const;

	/**********************機能系**************************/
	//マウス入力によるオブジェクトの移動
	void MovementByMouse();
	//キーボード入力によるオブジェクトの移動
	void MovementByKey();

	//オブジェクトの削除
	void DeleteObject();

	//オブジェクトの選択
	void IsSelectedObject();

	//折れ線の変形
	bool TransformPolyLine();
	bool TransformPolyLine(PolyLine* poly_line);
	//矩形の変形
	bool TransformBox();
	bool TransformBox(BoxCollider* box);

	//マップチップを作成する
	void MakeMapChip(); //クリックしたとき用
	void MakeMapChip(float x, float y, float width, float height); //CSVファイルからの読み込み用

	//コリジョンクラスを作成する
	//折れ線
	void MakePolyLine();
	//円
	void MakeSphere();
	//保留中のオブジェクトをリセットする
	void Trash();

	//メニュー選択
	void Select(int menu_max);

	const int* GetImage(int image_index)const;


	/******************ファイルへの書き込み読み込み系*********************/
	//CSVファイルへの書き出し(新規追加)
	void SaveStage(int stage_num);
	//上書き保存
	void SaveStage(char* stage_name);
	//CSVファイルからの読み込み
	void LoadStage(char* stage_name);
	//ファイルカウント
	int FileCount(const char* path)const;


	//マップチップの保存
	void SaveMapChips(FILE* fp);
	//折れ線の保存
	void SavePolyLine(FILE* fp);
	//オブジェクトの保存
	void SaveObject(FILE* fp);

	//マップチップの読み込み
	void LoadMapChip(istringstream* i_stringstream);
	//折れ線の読み込み
	void LoadPolyLine(istringstream* i_stringstream);
};


#endif