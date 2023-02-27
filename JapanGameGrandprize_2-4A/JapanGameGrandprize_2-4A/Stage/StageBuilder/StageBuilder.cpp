#include "DxLib.h"
#include "StageBuilder.h"
#include "Directory.h"
#include <string>
#include <fstream>
#include <sstream>

//------------------------------------
// コンストラクタ
//------------------------------------
StageBuilder::StageBuilder()
{
	Directory::Init();
	mouse = new SphereCollider();
	mouse_pos = {};

	if (LoadDivGraph("Images/Stage/map_chips.png", 10, 10, 1, 40, 40, block_images) == -1) 
	{
		throw "Images/Stage/map_chips_test.png";
	}

	mode = BRUSH_MODE;

	menu_cursor = 0;	
	arrow[0] = '>';

	for (int i = 1; i < ARROW_NUM; i++)
	{
		arrow[i] = ' ';
	}

	line = new LineCollider2({0,360}, {1280,360});
}

//------------------------------------
// デストラクタ
//------------------------------------
StageBuilder::~StageBuilder()
{
	delete mouse;

	for (int i = 0; i < map_chips.size(); i++)
	{
		delete map_chips[i];
	}

	map_chips.clear();

	delete line;
}

//------------------------------------
// 更新
//------------------------------------
void StageBuilder::Update()
{
	KeyManager::Update(); //StageBuilder上でしか使わないため、ソースコードの散らばりを避けています。
	UpdateMouse();

	if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE))mode = MENU_MODE;

	switch (mode)
	{
	case MENU_MODE:
		UpdateMenu();
		break;
	
	case BRUSH_MODE:
		UpdateBrush();
		break;
	
	case MODULATION_MODE:
		UpdateModulation();
		break;

	case SAVE_MODE:
		Directory::Open("\\Stage\\StageBuilder\\dat");
		UpdateSave();
		break;
		
	case LOAD_MODE:
		Directory::Open("\\Stage\\StageBuilder\\dat");
		UpdateLoad();
		break;
	}

	if (map_chips.size() != 0)
	{
		map_chips[0]->MoveLocation();
	}

	line->MoveLocation();
	line->SetLocation(mouse_pos, LINE_START);
}

//------------------------------------
// 描画
//------------------------------------
void StageBuilder::Draw()const
{
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 2, 10, 0xFFFFFF);
	DrawCircleAA(mouse_pos.x, mouse_pos.y, 1, 10, 0x000000);

	for (int i = 0; i < map_chips.size(); i++)
	{
		map_chips[i]->Draw();
	}

	DrawFrame();

#ifdef _DEBUG
	SetFontSize(16);
	for (int i = 0; i < map_chips.size(); i++)
	{
		int frame_x = (int)(map_chips[i]->GetLocation().x / MAP_CHIP_SIZE);
		int frame_y = (int)(map_chips[i]->GetLocation().y / MAP_CHIP_SIZE);

		DrawFormatString(0, i * 20, 0xFFFFFF, "マス x:%d y:%d  座標x:%.0lf y:%.0lf ",
			frame_x, frame_y,
			(double)frame_x * MAP_CHIP_SIZE + 20, (double)frame_y * MAP_CHIP_SIZE) + 20;
	}

#endif
	if (mode == MENU_MODE)
	{
		DrawMenu();
	}
	if (mode == SAVE_MODE || mode == LOAD_MODE)
	{
		DrawFileInfo();
	}

	//line->DrawCollision();
}

//------------------------------------
// メニューモードの更新
//------------------------------------
void StageBuilder::UpdateMenu()
{
	Select(MENU_NUM);
	
	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		mode = menu_cursor;
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}
}

//------------------------------------
// ブラシモードの更新
//------------------------------------
void StageBuilder::UpdateBrush()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		MakeMapChip();
	}
}

//------------------------------------
// モデュレーションモードの更新
//------------------------------------
void StageBuilder::UpdateModulation()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		for (int i = 0; i < map_chips.size(); i++)
		{
			if (mouse->HitBox(map_chips[i]))
			{
				delete map_chips[i];
				map_chips.erase(map_chips.begin() + i);
				break;
			}
		}
	}
}

//------------------------------------
// セーブモードの更新
//------------------------------------
void StageBuilder::UpdateSave()
{
	static int stage_max = 0;

	if (stage_max == 0)
	{
		string file_name(Directory::GetCurrent());
		file_name += "\\*.csv";

		stage_max = FileCount(file_name.c_str());
		stage_max++;//新規追加分
	}

	Select(stage_max);

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';

		char stage_argc[16];
		if (menu_cursor != stage_max - 1)
		{

			sprintf_s(stage_argc, 16, "stage%d.csv", menu_cursor + 1);
			SaveStage(stage_argc);
		}
		else
		{
			SaveStage(stage_max);
			stage_max++;
		}
		
		Directory::OpenMain();
		mode = BRUSH_MODE;
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}
}

//------------------------------------
// ロードモードの更新
//------------------------------------
void StageBuilder::UpdateLoad()
{

	int stage_max = 0;

	string file_name(Directory::GetCurrent());
	file_name += "\\*.csv";

	stage_max = FileCount(file_name.c_str());


	Select(stage_max);

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';

		char stage_argc[16];

		sprintf_s(stage_argc, 16, "stage%d.csv", menu_cursor + 1);
		LoadStage(stage_argc);


		Directory::OpenMain();
		mode = BRUSH_MODE;
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}
}

//------------------------------------
// マウスの更新
//------------------------------------
void StageBuilder::UpdateMouse()
{
	int x, y;
	GetMousePoint(&x, &y);
	mouse_pos.x = (float)x;
	mouse_pos.y = (float)y;

	mouse->SetLocation(mouse_pos);
}

//------------------------------------
// メニューの描画
//------------------------------------
void StageBuilder::DrawMenu()const
{
	int font_size = 20;
	int current = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(0, 0, 320, font_size * MENU_NUM,0x000000,TRUE);
	DrawBoxAA(0, 0, 320, (float)(font_size * MENU_NUM), 0xFFFFFF, FALSE, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetFontSize(font_size);
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c BRUSH_MODE", arrow[current]);
	current++;
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c MODULATION_MODE", arrow[current]);
	current++;
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c SAVE", arrow[current]);
	current++;
	DrawFormatString(0, font_size * current, 0xFFFF00, " %c LOAD", arrow[current]);
	current++;
}

//------------------------------------
// セーブモードの描画
//------------------------------------
void StageBuilder::DrawFileInfo()const
{
	string file_name(Directory::GetCurrent());
	int scale = 0;
	int current = 0;
	file_name += "\\*.csv";

	const float draw_pos_x = 560.f;
	const float draw_pos_y = 240.f;

	int l_font_size = 16;
	scale = FileCount(file_name.c_str());
	if (mode == SAVE_MODE)scale++;//新規追加分

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + MAP_CHIP_SIZE * 4, draw_pos_y + l_font_size * scale, 
		0x000000, TRUE);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		560.f + MAP_CHIP_SIZE * 4, draw_pos_y + l_font_size * scale,
		0xFFFFFF, FALSE, 3);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFile(draw_pos_x, draw_pos_y, file_name.c_str(),l_font_size);

	if (mode == SAVE_MODE)
	{
		DrawFormatStringF(draw_pos_x + l_font_size,
			draw_pos_y + l_font_size * (scale-1),
			GetColor(255, 255, 255), "%c %s", arrow[scale-1], "新規追加");
	}
}

//------------------------------------
// 格子の描画
//------------------------------------
void StageBuilder::DrawFrame()const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);

	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_HEIGHT; i++)
	{
		DrawLineAA(0, i * MAP_CHIP_SIZE, SCREEN_WIDTH, i * MAP_CHIP_SIZE, 0xFFFFFF);
	}

	for (int i = 0; i * MAP_CHIP_SIZE < SCREEN_WIDTH; i++)
	{
		DrawLineAA(i * MAP_CHIP_SIZE, 0, i * MAP_CHIP_SIZE, SCREEN_HEIGHT, 0xFFFFFF);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//------------------------------------
// ファイルの描画
//------------------------------------
void StageBuilder::DrawFile(float x, float y, const char* path, int font_size)const
{
	FILEINFO file_info;
	int count_y = 0;

	__int64 find_handle = FileRead_findFirst(path, &file_info);
	if (find_handle != (__int64)-1)
	{
		do
		{
			// ファイル名の描画
			DrawFormatString(x + font_size, y + font_size * count_y ,
				GetColor(255, 255, 255), "%c %s", arrow[count_y], file_info.Name);

			// 描画y座標をずらす
			count_y++;

			// 検索に引っかかる次のファイルの情報を取得、無かったらループを抜ける
		} while (FileRead_findNext(find_handle, &file_info) >= 0);

		// 検索ハンドルの後始末
		FileRead_findClose(find_handle);
	}
}

//------------------------------------
// マップチップの作成
//------------------------------------
void StageBuilder::MakeMapChip()
{
	float pos_x = (int)(mouse_pos.x / MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	float pos_y = (int)(mouse_pos.y / MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	map_chips.push_back(new MapChip(&block_images[0],
		{ pos_x + MAP_CHIP_SIZE / 2,pos_y + MAP_CHIP_SIZE / 2 },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// マップチップの作成
//------------------------------------
void StageBuilder::MakeMapChip(float x, float y, float width, float height)
{
	map_chips.push_back(new MapChip(&block_images[0],
		{ x ,y },{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// ファイルカウント
//------------------------------------
int StageBuilder::FileCount(const char* path)const
{
	int count = 0;

	FILEINFO file_info;

	__int64 find_handle = FileRead_findFirst(path, &file_info);
	if (find_handle != (__int64)-1)
	{
		do
		{
			count++;
			// 検索に引っかかる次のファイルの情報を取得、無かったらループを抜ける
		} while (FileRead_findNext(find_handle, &file_info) >= 0);

		// 検索ハンドルの後始末
		FileRead_findClose(find_handle);
	}

	return count;
}

//------------------------------------
// メニュー選択
//------------------------------------
void StageBuilder::Select(int menu_max)
{

	if (KeyManager::OnKeyClicked(KEY_INPUT_S) || KeyManager::OnKeyClicked(KEY_INPUT_DOWN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor++;

		if (menu_cursor > menu_max - 1)
		{
			menu_cursor = 0;
		}

		arrow[menu_cursor] = tmp;
	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_W) || KeyManager::OnKeyClicked(KEY_INPUT_UP))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor--;

		if (menu_cursor < 0)
		{
			menu_cursor = menu_max - 1;
		}

		arrow[menu_cursor] = tmp;
	}
}

//------------------------------------
// 画像の取得
//------------------------------------
const int* StageBuilder::GetImage(int image_index)const
{
	return &block_images[image_index];
}

//------------------------------------
// CSVファイルへ書き出す
//------------------------------------
void StageBuilder::SaveStage(int stage_num)
{

	FILE* fp = NULL;
	char stage_name[16];
	sprintf_s(stage_name, 16, "stage%d.csv", stage_num);

	//ファイルオープン
	fopen_s(&fp, stage_name, "w");
	
	//クラス名, x, y, image_handle
	for (int i = 0; i < map_chips.size(); i++)
	{

		fprintf_s(fp, "%s,%lf,%lf,%d\n",
			map_chips[i]->GetName(),
			map_chips[i]->GetLocation().x,
			map_chips[i]->GetLocation().y,
			0);
	}

	if (fp)
	{
		fclose(fp);
	}
}

//------------------------------------
// CSVファイルへ書き出す
//------------------------------------
void StageBuilder::SaveStage(char* stage_name)
{
	FILE* fp = NULL;

	//ファイルオープン
	fopen_s(&fp, stage_name, "w");

	if (fp != NULL)
	{
		//クラス名, x, y, image_handle
		for (int i = 0; i < map_chips.size(); i++)
		{

			fprintf_s(fp, "%s,%lf,%lf,%d\n",
				map_chips[i]->GetName(),
				map_chips[i]->GetLocation().x,
				map_chips[i]->GetLocation().y,
				0);
		}
	}

	if (fp)
	{
		fclose(fp);
	}
}

//------------------------------------
// CSVファイルからの読み込み
//------------------------------------
void StageBuilder::LoadStage(char* stage_name)
{
	string class_name;
	float x;
	float y;
	float width = MAP_CHIP_SIZE;
	float height = MAP_CHIP_SIZE;
	float image;

	string str_conma_buf;
	string line;
	ifstream ifstream(stage_name);

	if (!ifstream)
	{
		std::exit(1);
		return;
	}

	while(!(getline(ifstream,line).eof()))
	{
		istringstream i_stringstream(line);

		getline(i_stringstream, str_conma_buf, ',');
		class_name = str_conma_buf;


		getline(i_stringstream, str_conma_buf, ',');
		x = atof(str_conma_buf.c_str());


		getline(i_stringstream, str_conma_buf, ',');
		y = atof(str_conma_buf.c_str());


		getline(i_stringstream, str_conma_buf, ',');
		image = atof(str_conma_buf.c_str());

		MakeMapChip(x, y, width, height);
	}

	ifstream.close();
}