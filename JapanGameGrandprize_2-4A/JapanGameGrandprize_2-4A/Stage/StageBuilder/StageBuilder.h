#pragma once
#include "Debug.h"

#ifdef _STAGE_BUILDER
#include "../Define.h"
#include "../../TextureContainer.h"
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
#include <string_view>

//sphereColliderは約3000個程度ならフレームレートを落とさず更新できる


//モードの数とその種類------
#define MENU_NUM 4
#define MENU_MODE -1
#define BRUSH_MODE 0
#define MODULATION_MODE 1
#define SAVE_MODE 2
#define LOAD_MODE 3
//--------------------------

//ブラシの数とその種類---------
#define CLASS_NUM 4	
#define BRUSH_OBJECT 0
#define BRUSH_MAP_CHIP 1
#define BRUSH_BOX 2
#define BRUSH_POLY_LINE 3
//-----------------------------


//画像の数とその種類-----------------------------
#define IMAGE_NUM 6
#define YUKA_1 0
#define YUKA_2 1
#define KABE_1 2
#define KABE_2 3
#define KAIDANN_1 4
#define KAIDANN_2 5
//-----------------------------------------------

//ブラシモードのメニュー制御-------------
#define CLOSE 0
#define SELECT_CLASS 1
#define SELECT_IMAGE 2
#define SELECT_COLLIDER 3
//---------------------------------------


#define ARROW_NUM 16

using namespace std;

class StageBuilder
{
private:

	const char* class_name[CLASS_NUM] =
	{
		"object",
		"default_map_chip",
		"box",
		"poly_line"
	};

	const char* image_name[IMAGE_NUM] =
	{
		"yuka_1"
		,"yuka_2"
		,"kabe_1"
		,"kabe_2"
		,"kaidann_1"
		,"kaidann_2"
	};

	//インタフェース
	SphereCollider* mouse;
	ColliderBase* select_collider;
	int menu_cursor;
	char arrow[ARROW_NUM];

	//デフォルトマップチップ
	int block_images[110];		//ブロック画像
	vector<MapChip*> map_chips;
	vector<BoxCollider*> box_collider;
	vector<PolyLine*>poly_lines;
	vector<ObjectBase*>objects;

	//保留中のスフィア
	vector<SphereCollider*> pending_sphere;

	//ツール用
	int mode;
	int current_brush;
	int current_object_image;
	int current_object_collider;
	int brush_mode_state;


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
	//ブラシモードの描画
	void DrawBrushMode()const;

	//当たり判定の描画 + objectのpivot --- collider間のベクトル
	void DrawCollider()const;

	//格子の描画
	void DrawFrame()const;
	//マウスの描画
	void DrawMouse()const;
	//ファイルの描画
	void DrawFile(float x, float y, const char* path, int font_size)const;
	
	//現在のブラシになっているクラスを描画
	void DrawClassName()const;
	//クラス選択の描画
	void DrawSelectClass()const;
	//画像選択の描画
	void DrawSelectImage()const;
	//当たり判定選択の描画
	void DrawSelectCollider()const;

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
	MapChip* MakeMapChip(float x, float y, float width, float height); //CSVファイルからの読み込み用

	//objectクラスを作成する
	void MakeObject();

	//コリジョンクラスを作成する
	//折れ線
	bool MakePolyLine();
	//BoxColliderを作成する
	void MakeBoxCollider();
	//円
	void MakeSphere();
	//保留中のオブジェクトをリセットする
	void Trash();

	//メニュー選択
	void Select(int menu_max);

	//クラス選択
	void SelectClass();
	//画像選択
	void SelectImage();
	//当たり判定選択
	void SelectCollider();


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
	//BoxColliderの保存
	void SaveBoxCollider(FILE* fp);
	//オブジェクトの保存
	void SaveObject(FILE* fp);

	//マップチップの読み込み
	MapChip* LoadMapChip(istringstream* i_stringstream);
	//折れ線の読み込み
	PolyLine* LoadPolyLine(istringstream* i_stringstream);
	//BoxColliderの読み込み
	BoxCollider* LoadBoxCollider(istringstream* i_stringstream);

};


#endif