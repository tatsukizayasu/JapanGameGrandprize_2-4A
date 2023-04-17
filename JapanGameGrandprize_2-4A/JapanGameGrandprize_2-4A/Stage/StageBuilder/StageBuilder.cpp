#include "StageBuilder.h"
#include "DxLib.h"
#include "../../Define.h"
#include "../../CameraWork.h"
#include "Directory.h"

#define _DEV

#ifdef _STAGE_BUILDER

//------------------------------------
// コンストラクタ
//------------------------------------
StageBuilder::StageBuilder()
{

	Directory::Init();
	mouse = new SphereCollider();
	select_collider = nullptr;
	menu_cursor = 0;
	arrow[0] = '>';

	if (LoadDivGraph("Images/Stage/map_chips.png", 50, 10, 5, CHIP_SIZE, CHIP_SIZE, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips_.png";
	}

	//TODO: BRUSH_MODEに戻す
	mode = MODULATION_MODE;

	for (int i = 1; i < ARROW_NUM; i++)
	{
		arrow[i] = ' ';
	}

	current_brush = BRUSH_MAP_CHIP;

#ifdef _DEV

	for (int i = 0; i < 0; i++)
	{
		Location test[3] =
		{
			{i * 10,i * 10},
			{i * 15,i * 10},
			{i * 20,i * 15}
		};
		poly_lines.push_back(new PolyLine(test, 3));
	}
	Location testloc[4]{ {300,300},{500,500},{200,700} , {900,400} };
	PolyLine testline(testloc, 4);
	//poly_lines.push_back(new PolyLine(testloc, 4));

	//boxes.push_back(new BoxCollider({ 640,360 }, { 100,100 }));

	BoxCollider box = BoxCollider({ 640,360 }, { 100,100 });

	objects.push_back(new ObjectBase({ 640,460 }, &testline));


#endif // _DEV
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

	for (int i = 0; i < pending_sphere.size(); i++)
	{
		delete pending_sphere[i];
	}
	pending_sphere.clear();

	for (int i = 0; i < poly_lines.size(); i++)
	{
		delete poly_lines[i];
	}
	poly_lines.clear();

	for (int i = 0; i < boxes.size(); i++)
	{
		delete boxes[i];
	}
	boxes.clear();

	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();

}

//------------------------------------
// 更新
//------------------------------------
void StageBuilder::Update()
{

	KeyManager::Update(); //StageBuilder上でしか使わないため、ソースコードの散らばりを避けています。
	UpdateMouse();

	if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE))
	{
		mode = MENU_MODE;
		Trash();
	}

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

#ifdef _DEV




#endif // _DEV
}

//------------------------------------
// 描画
//------------------------------------
void StageBuilder::Draw()const
{

	for (int i = 0; i < map_chips.size(); i++)
	{
		map_chips[i]->Draw();
	}

	for (int i = 0; i < poly_lines.size(); i++)
	{
		poly_lines[i]->Draw();
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


#ifdef _DEV


	for (int i = 0; i < poly_lines.size(); i++)
	{
		if (poly_lines[i]->HitSphere(mouse))
		{
			DrawString(640, 300, "hit", 0);
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->HitSphere(mouse))
		{
			DrawString(640, 300, "hit", 0);
		}
	}


	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->Draw();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}


#endif // _DEV

	DrawWhichMode();

	DrawMouse();

	mouse->Draw();

}

//--------------------------------------
// モードごとに分かれた描画
//--------------------------------------
void StageBuilder::DrawWhichMode()const
{

	switch (mode)
	{

	case MENU_MODE:
		DrawMenu();
		break;

	case BRUSH_MODE:
		DrawClassName();
		if (2 <= pending_sphere.size())
		{
			for (int i = 0; i + 1 < pending_sphere.size(); i++)
			{
				DrawLine(pending_sphere[i]->GetLocation() - CameraWork::GetCamera()
					, pending_sphere[i + 1]->GetLocation() - CameraWork::GetCamera());
			}
		}
		DrawSphere();
		break;

	case MODULATION_MODE:
		if (select_collider != nullptr)
		{
			DrawCircleAA(
				select_collider->GetLocation().x - CameraWork::GetCamera().x,
				select_collider->GetLocation().y - CameraWork::GetCamera().y,
				6, 20, 0xFFFF22, TRUE);
		}
		break;

	case SAVE_MODE:
	case LOAD_MODE:
		DrawFileInfo();
		break;
	}
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

	if (KeyManager::OnKeyClicked(KEY_INPUT_TAB))
	{
		current_brush++;
		if (CLASS_NUM <= current_brush)
		{
			current_brush -= CLASS_NUM;
		}
	}

	switch (current_brush)
	{

	case BRUSH_MAP_CHIP:
		if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
		{
			MakeMapChip();
		}
		break;

	case BRUSH_POLY_LINE:
		MakePolyLine();
		break;
	}
}

//------------------------------------
// モデュレーションモードの更新
//------------------------------------
void StageBuilder::UpdateModulation()
{
	DeleteObject();

	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		IsSelectedObject();
	}




	if (select_collider != nullptr)
	{
		MovementByMouse();
		MovementByKey();


		for (int i = 0; i < poly_lines.size(); i++)
		{
			poly_lines[i]->Update();
		}


		for (int i = 0; i < boxes.size(); i++)
		{
			boxes[i]->UpdatePos();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			int collider_type = objects[i]->GetColllider()->GetName();
			if (collider_type == (int)COLLIDER::BOX)
			{
				BoxCollider* box
					= static_cast<BoxCollider*>(objects[i]->GetColllider());

				box->UpdatePos();
				objects[i]->UpdateColliderPos();
			}

			if (collider_type == (int)COLLIDER::POLY_LINE)
			{
				PolyLine* poly_line
					= static_cast<PolyLine*>(objects[i]->GetColllider());

				poly_line->Update();
				objects[i]->UpdateColliderPos();
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

	x = x + (int)CameraWork::GetCamera().x;
	y = y + (int)CameraWork::GetCamera().y;

	mouse->SetLocation({ (float)x,(float)y });
}

//------------------------------------
// メニューの描画
//------------------------------------
void StageBuilder::DrawMenu()const
{

	int font_size = 20;
	int current = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(0, 0, 320, font_size * MENU_NUM, 0x000000, TRUE);
	DrawBoxAA(0, 0, 320, (float)(font_size * MENU_NUM), 0xFFFFFF, FALSE, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

	DrawFile(draw_pos_x, draw_pos_y, file_name.c_str(), l_font_size);

	if (mode == SAVE_MODE)
	{
		DrawFormatStringF(draw_pos_x + l_font_size,
			draw_pos_y + l_font_size * (scale - 1),
			GetColor(255, 255, 255), "%c %s", arrow[scale - 1], "新規追加");
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

//-------------------------------------
// マウスの描画
//-------------------------------------
void StageBuilder::DrawMouse()const
{

	DrawCircleAA(mouse->GetLocation().x - CameraWork::GetCamera().x,
		mouse->GetLocation().y - CameraWork::GetCamera().y, 2, 10, 0xFFFFFF);
	DrawCircleAA(mouse->GetLocation().x - CameraWork::GetCamera().x,
		mouse->GetLocation().y - CameraWork::GetCamera().y, 1, 10, 0x000000);
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
			DrawFormatString(x + font_size, y + font_size * count_y,
				GetColor(255, 255, 255), "%c %s", arrow[count_y], file_info.Name);

			// 描画y座標をずらす
			count_y++;

			// 検索に引っかかる次のファイルの情報を取得、無かったらループを抜ける
		} while (FileRead_findNext(find_handle, &file_info) >= 0);

		// 検索ハンドルの後始末
		FileRead_findClose(find_handle);
	}
}

//-------------------------------------
// 現在のブラシになっているクラスを描画
//-------------------------------------
void StageBuilder::DrawClassName()const
{

	int draw_width;

	int font_size = 20;
	SetFontSize(font_size);
	draw_width = GetDrawStringWidth(class_name[current_brush], -1);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(0, 0, draw_width + 8, font_size + 4, 0x000000, TRUE);
	DrawBoxAA(0, 0, (float)draw_width + 8, (float)font_size + 4, 0xFFFFFF, FALSE, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(4, 4, 0xffffff, "%s", class_name[current_brush]);
}

//---------------------------------------------
// 保留中のスフィアの描画
//---------------------------------------------
void StageBuilder::DrawSphere()const
{

	for (int i = 0; i < pending_sphere.size(); i++)
	{
		pending_sphere[i]->Draw();
	}
}

//---------------------------------------------
// 保留中のラインの描画
//---------------------------------------------
void StageBuilder::DrawLine(Location start, Location end)const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawLineAA(start.x, start.y, end.x, end.y, 0xE9FF00, 3);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------
// マウス入力によるオブジェクトの移動
//---------------------------------------------
void StageBuilder::MovementByMouse()
{
	if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT))
	{
		float set_x = (int)(mouse->GetLocation().x) / 10 * 10;
		float set_y = (int)(mouse->GetLocation().y) / 10 * 10;
		select_collider->SetLocation({ set_x,set_y });
	}
}

//---------------------------------------------
// キーボード入力によるオブジェクトの移動
//---------------------------------------------
void StageBuilder::MovementByKey()
{
	select_collider->MoveLocation();
}

//---------------------------------------------
// オブジェクトの削除
//---------------------------------------------
void StageBuilder::DeleteObject()
{
	if (KeyManager::OnMouseClicked(MOUSE_INPUT_RIGHT))
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

		for (int i = 0; i < poly_lines.size(); i++)
		{
			vector<SphereCollider*> points = poly_lines[i]->GetPoints();

			for (int j = 0; j < points.size(); j++)
			{
				if (mouse->HitSphere(points[j]))
				{
					poly_lines[i]->DeleteBendPoint(j);
					if (poly_lines[i]->GetPoints().size() < 2)
					{
						delete poly_lines[i];
						poly_lines.erase(poly_lines.begin() + i);
					}
				}
			}
		}
	}
}

//-----------------------------------------------
// オブジェクトが選択されたかどうかを返す
//-----------------------------------------------
void StageBuilder::IsSelectedObject()
{
	if (TransformPolyLine())
	{
		return;
	}

	if (TransformBox())
	{
		return;
	}


	for (int i = 0; i < objects.size(); i++)
	{
		int collider_type = objects[i]->GetColllider()->GetName();
		//todo:名前から判断してstatic_castを使い、それぞれのクラス型に沿った処理をする

		switch (collider_type)
		{
		case (int)COLLIDER::BOX:
		{
			BoxCollider* box = static_cast<BoxCollider*>(objects[i]->GetColllider());
			if (TransformBox(box))
			{
				return;
			}
			break;
		}
		case (int)COLLIDER::POLY_LINE:
		{
			PolyLine* poly_line = static_cast<PolyLine*>(objects[i]->GetColllider());
			if (TransformPolyLine(poly_line))
			{
				return;
			}
			break;
		}
		default:
			;

		}

		if (mouse->HitSphere(objects[i]->GetPivot()))
		{
			select_collider = objects[i]->GetPivot();
			return;
		}
		else
		{
			select_collider = nullptr;

		}
	}


}


//---------------------------------------------
// 折れ線の変形 戻り値：選択されたか
//---------------------------------------------
bool StageBuilder::TransformPolyLine()
{
	for (int i = 0; i < poly_lines.size(); i++)
	{
		vector<SphereCollider*> points = poly_lines[i]->GetPoints();

		for (int j = 0; j < points.size(); j++)
		{
			if (mouse->HitSphere(points[j]))
			{
				select_collider = points[j];
				points.clear();
				return true;
			}
		}

		if (mouse->HitSphere(poly_lines[i]->GetPivot()))
		{
			select_collider = poly_lines[i]->GetPivot();
			return true;
		}

		points.clear();
	}

	return false;
}

//---------------------------------------------
// 折れ線の変形 戻り値：選択されたか
//---------------------------------------------
bool StageBuilder::TransformPolyLine(PolyLine* poly_line)
{
	vector<SphereCollider*> points = poly_line->GetPoints();

	for (int i = 0; i < points.size(); i++)
	{
		if (mouse->HitSphere(points[i]))
		{
			select_collider = points[i];
			points.clear();
			return true;
		}
	}

	if (mouse->HitSphere(poly_line->GetPivot()))
	{
		select_collider = poly_line->GetPivot();
		return true;
	}

	points.clear();


	return false;
}

//---------------------------------------------
// 矩形の変形　戻り値：選択されたか
//---------------------------------------------
bool StageBuilder::TransformBox()
{
	for (int i = 0; i < boxes.size(); i++)
	{
		SphereCollider* points = boxes[i]->GetSpheres();


		for (int j = 0; j < 4; j++)
		{
			if (mouse->HitSphere(&points[j]))
			{
				select_collider = &points[j];
				return true;
			}
		}

		if (mouse->HitSphere(boxes[i]->GetPivot()))
		{
			select_collider = boxes[i]->GetPivot();
			return true;
		}
	}

	return false;
}


//---------------------------------------------
// 矩形の変形　戻り値：選択されたか
//---------------------------------------------
bool StageBuilder::TransformBox(BoxCollider* box)
{
	SphereCollider* points = box->GetSpheres();

	for (int i = 0; i < 4; i++)
	{
		if (mouse->HitSphere(&points[i]))
		{
			select_collider = &points[i];
			return true;
		}
	}

	if (mouse->HitSphere(box->GetPivot()))
	{
		select_collider = box->GetPivot();
		return true;
	}

	return false;
}

//------------------------------------
// マップチップの作成
//------------------------------------
void StageBuilder::MakeMapChip()
{

	float pos_x = (int)(mouse->GetLocation().x
		/ MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	float pos_y = (int)(mouse->GetLocation().y
		/ MAP_CHIP_SIZE) * MAP_CHIP_SIZE;
	map_chips.push_back(new MapChip(&block_images[1],
		{ pos_x + MAP_CHIP_SIZE / 2,pos_y + MAP_CHIP_SIZE / 2 },
		{ MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// マップチップの作成
//------------------------------------
void StageBuilder::MakeMapChip(float x, float y, float width, float height)
{

	map_chips.push_back(new MapChip(&block_images[1],
		{ x ,y }, { MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// PolyLine classの生成
//------------------------------------
void StageBuilder::MakePolyLine()
{

	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		MakeSphere();

	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		if (2 <= pending_sphere.size())
		{
			poly_lines.push_back(new PolyLine(pending_sphere));
			Trash();
		}
	}
}

//------------------------------------
// Sphere classの生成
//------------------------------------
void StageBuilder::MakeSphere()
{

	pending_sphere.push_back(new SphereCollider(mouse->GetLocation()));
}

//--------------------------------------
// 線を作り切れなかったときリセット
//--------------------------------------
void StageBuilder::Trash()
{

	for (int i = 0; i < pending_sphere.size(); i++)
	{
		delete pending_sphere[i];
	}
	pending_sphere.clear();
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

	SaveMapChips(fp);

	SavePolyLine(fp);

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

	SaveMapChips(fp);

	SavePolyLine(fp);

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

	string str_conma_buf;
	string line;
	ifstream ifstream(stage_name);

	if (!ifstream)
	{
		std::exit(1);
		return;
	}

	while (!(getline(ifstream, line).eof()))
	{
		istringstream i_stringstream(line);

		getline(i_stringstream, str_conma_buf, ',');
		class_name = str_conma_buf;

		if (class_name == "default")
		{
			LoadMapChip(&i_stringstream);
			continue;
		}

		if (class_name == "PolyLine")
		{
			LoadPolyLine(&i_stringstream);
			continue;
		}
	}

	ifstream.close();
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
// マップチップの保存
//------------------------------------
void StageBuilder::SaveMapChips(FILE* fp)
{
	if (fp)
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
}

//------------------------------------
// 折れ線の保存
//------------------------------------
void StageBuilder::SavePolyLine(FILE* fp)
{
	if (fp)
	{
		for (int i = 0; i < poly_lines.size(); i++)
		{
			fprintf_s(fp, "PolyLine");
			vector<SphereCollider*> points = poly_lines[i]->GetPoints();
			fprintf_s(fp, ",%d", int(points.size()));

			for (int j = 0; j < points.size(); j++)
			{
				fprintf_s(fp, ",%.1lf,%.1lf",
					points[j]->GetLocation().x,
					points[j]->GetLocation().y
				);
			}
			fprintf_s(fp, "\n");

			points.clear();
		}
	}
}

//------------------------------------
// マップチップの読み込み
//------------------------------------
void StageBuilder::LoadMapChip(istringstream* i_stringstream)
{
	string str_conma_buf;
	string line;

	float x;
	float y;
	float width = MAP_CHIP_SIZE;
	float height = MAP_CHIP_SIZE;

	getline(*i_stringstream, str_conma_buf, ',');
	x = atof(str_conma_buf.c_str());

	getline(*i_stringstream, str_conma_buf, ',');
	y = atof(str_conma_buf.c_str());

	MakeMapChip(x, y, width, height);

}

//------------------------------------
// 折れ線の読み込み
//------------------------------------
void StageBuilder::LoadPolyLine(istringstream* i_stringstream)
{
	string str_conma_buf;
	string line;
	vector<Location> location;
	int size = 0;

	getline(*i_stringstream, str_conma_buf, ',');
	size = atoi(str_conma_buf.c_str());

	for (int i = 0; i < size; i++)
	{
		location.push_back({ 0,0 });
		getline(*i_stringstream, str_conma_buf, ',');
		location[i].x = atof(str_conma_buf.c_str());

		getline(*i_stringstream, str_conma_buf, ',');
		location[i].y = atof(str_conma_buf.c_str());
	}

	poly_lines.push_back(new PolyLine(&location[0], location.size()));
}

#endif