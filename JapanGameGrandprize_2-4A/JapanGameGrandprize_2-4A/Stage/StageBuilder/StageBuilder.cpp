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
	for (int i = 1; i < ARROW_NUM; i++)
	{
		arrow[i] = ' ';
	}

	if (LoadDivGraph("Images/Stage/map_chips.png", 50, 10, 5, CHIP_SIZE, CHIP_SIZE, block_images + 1) == -1)
	{
		throw "Images/Stage/map_chips_.png";
	}

	mode = BRUSH_MODE;


	current_brush = BRUSH_MAP_CHIP;
	current_object_image = 0;
	current_object_collider = BRUSH_BOX;
	brush_mode_state = CLOSE;

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

	
	objects.push_back(new ObjectBase({ 640,460 }, &testline, "yuka_1"));


	Location mouse_line_loc[4]{ {0,0},{100,0},{150,100} , {200,100} };


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

	for (int i = 0; i < box_collider.size(); i++)
	{
		delete box_collider[i];
	}
	box_collider.clear();

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

	DrawCollider();

	DrawFrame();

#ifdef _DEBUG
	SetFontSize(20);
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


	for (int i = 0; i < objects.size(); i++)
	{
		if (mouse->HitCheck(objects[i]->GetColllider()))
		{
			DrawString(640, 300, "hit", 0xFFFFFF);
		}
	}



#endif // _DEV

	DrawWhichMode();

	DrawMouse();

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
		DrawBrushMode();
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
		brush_mode_state = SELECT_CLASS;
	}

	switch (brush_mode_state)
	{
	case SELECT_CLASS:
		SelectClass();
		break;
		
	case SELECT_IMAGE:
		SelectImage();
		break;
		
	case SELECT_COLLIDER:
		SelectCollider();
		break;

	}


	switch (current_brush)
	{
	case BRUSH_OBJECT:
		break;

	case BRUSH_MAP_CHIP:
		if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
		{
			MakeMapChip();
		}
		break;

	case BRUSH_BOX:
		if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
		{
			MakeBoxCollider();
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


		for (int i = 0; i < box_collider.size(); i++)
		{
			box_collider[i]->UpdatePos();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			int collider_type = objects[i]->GetColllider()->GetColliderType();
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

				objects[i]->UpdateColliderPos();
				poly_line->Update();
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
	file_name += "\\*.csv";

	const float draw_pos_x = 560.f;
	const float draw_pos_y = 240.f;

	int l_font_size = 20;
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
// ブラシモードの描画
//------------------------------------
void StageBuilder::DrawBrushMode()const
{

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


	switch (brush_mode_state)
	{
	case SELECT_CLASS:
		DrawSelectClass();
		break;
		
	case SELECT_IMAGE:
		DrawSelectImage();
		break;
		
	case SELECT_COLLIDER:
		DrawSelectCollider();
		break;

	}
	
}

//------------------------------------
// 当たり判定の描画
//------------------------------------
void StageBuilder::DrawCollider()const
{

	for (int i = 0; i < poly_lines.size(); i++)
	{
		poly_lines[i]->Draw();
	}

	for (int i = 0; i < box_collider.size(); i++)
	{
		box_collider[i]->Draw();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
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

	if (current_brush != BRUSH_OBJECT)
	{
		draw_width = GetDrawStringWidth(class_name[current_brush], -1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(0, 0, draw_width + 8, font_size + 4, 0x000000, TRUE);
		DrawBoxAA(0, 0, (float)draw_width + 8, (float)font_size + 4, 0xFFFFFF, FALSE, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(4, 4, 0xffffff, "%s", class_name[current_brush]);
	}
	else
	{
		string draw_text = string(class_name[current_brush]);
		draw_text += " image: ";
		draw_text += image_name[current_object_image];
		draw_text += " collider: ";
		draw_text += class_name[current_object_collider];

		draw_width = GetDrawStringWidth(draw_text.c_str(), -1);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(0, 0, draw_width + 8, font_size + 4, 0x000000, TRUE);
		DrawBoxAA(0, 0, (float)draw_width + 8, (float)font_size + 4, 0xFFFFFF, FALSE, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(4, 4, 0xffffff, "%s", draw_text.c_str());
	}
}

//--------------------------------------------
// クラス選択の描画
//--------------------------------------------
void StageBuilder::DrawSelectClass()const
{
	int scale = CLASS_NUM;
	int current = 0;

	const int l_font_size = 20;
	const int len = 15;
	const float draw_pos_x = 640.0f - (l_font_size * len / 2);
	const float draw_pos_y = 360.f - (l_font_size * scale / 2);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0x000000, TRUE);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0xFFFFFF, FALSE, 3);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < scale; i++)
	{
		DrawFormatString(draw_pos_x + l_font_size, draw_pos_y + l_font_size * i,
			GetColor(255, 255, 255), "%c %s", arrow[i], class_name[i]);

	}
}

//--------------------------------------------
// 画像選択の描画
//--------------------------------------------
void StageBuilder::DrawSelectImage()const
{
	int scale = IMAGE_NUM;
	int current = 0;

	const int l_font_size = 20;
	const int len = 15;
	const float draw_pos_x = 640.0f - (l_font_size * len / 2);
	const float draw_pos_y = 360.f - (l_font_size * scale / 2);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0x000000, TRUE);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0xFFFFFF, FALSE, 3);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < scale; i++)
	{
		DrawFormatString(draw_pos_x + l_font_size, draw_pos_y + l_font_size * i,
			GetColor(255, 255, 255), "%c %s", arrow[i], image_name[i]);

	}

}

//--------------------------------------------
// 当たり判定選択の描画
//--------------------------------------------
void StageBuilder::DrawSelectCollider()const
{
	int scale = CLASS_NUM - BRUSH_BOX;
	int current = 0;

	const int l_font_size = 20;
	const int len = 15;
	const float draw_pos_x = 640.0f - (l_font_size * len / 2);
	const float draw_pos_y = 360.f - (l_font_size * scale / 2);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0x000000, TRUE);

	DrawBoxAA(draw_pos_x, draw_pos_y,
		draw_pos_x + l_font_size * len, draw_pos_y + l_font_size * scale,
		0xFFFFFF, FALSE, 3);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < scale; i++)
	{
		DrawFormatString(draw_pos_x + l_font_size, draw_pos_y + l_font_size * i,
			GetColor(255, 255, 255), "%c %s", arrow[i], class_name[i + 2]);

	}

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
		int collider_type = objects[i]->GetColllider()->GetColliderType();

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
	for (int i = 0; i < box_collider.size(); i++)
	{
		SphereCollider* points = box_collider[i]->GetSpheres();


		for (int j = 0; j < 4; j++)
		{
			if (mouse->HitSphere(&points[j]))
			{
				select_collider = &points[j];
				return true;
			}
		}

		if (mouse->HitSphere(box_collider[i]->GetPivot()))
		{
			select_collider = box_collider[i]->GetPivot();
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
MapChip* StageBuilder::MakeMapChip(float x, float y, float width, float height)
{
	return (new MapChip(&block_images[1],
		{ x ,y }, { MAP_CHIP_SIZE,MAP_CHIP_SIZE }));
}

//------------------------------------
// BoxColliderの作成
//------------------------------------
void StageBuilder::MakeBoxCollider()
{
	box_collider.push_back(new BoxCollider(mouse->GetLocation(), { 100,100 }));
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

//-------------------------------------
// クラス選択
//-------------------------------------
void StageBuilder::SelectClass()
{
	Select(CLASS_NUM);

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';

		if (menu_cursor != BRUSH_OBJECT)
		{
			brush_mode_state = CLOSE;
			current_brush = menu_cursor;
		}
		else
		{
			brush_mode_state = SELECT_IMAGE;
			current_brush = menu_cursor;
		}

		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_BACK))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;

		brush_mode_state -= 1;
	}
}

//-------------------------------------
// 画像選択
//-------------------------------------
void StageBuilder::SelectImage()
{
	Select(IMAGE_NUM);

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';

		current_object_image = menu_cursor;
		brush_mode_state = SELECT_COLLIDER;

		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_BACK))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;

		brush_mode_state -= 1;
	}

}

//-------------------------------------
// 当たり判定選択
//-------------------------------------
void StageBuilder::SelectCollider()
{

	Select(CLASS_NUM - BRUSH_BOX);

	if (KeyManager::OnKeyClicked(KEY_INPUT_RETURN))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';

		current_object_collider = menu_cursor + BRUSH_BOX;
		brush_mode_state = CLOSE;

		menu_cursor = 0;
		arrow[menu_cursor] = tmp;
	}

	if (KeyManager::OnKeyClicked(KEY_INPUT_BACK))
	{
		char tmp = arrow[menu_cursor];
		arrow[menu_cursor] = ' ';
		menu_cursor = 0;
		arrow[menu_cursor] = tmp;

		brush_mode_state -= 1;
	}
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

	SaveObject(fp);

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

	SaveObject(fp);

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

	int collider_type;
	const char* object_name;
	string texture_name;


	string str_conma_buf;
	string line;
	ifstream ifstream(stage_name);

	Directory::OpenMain();

	if (!ifstream)
	{
		std::exit(1);
		return;
	}

	while (!(getline(ifstream, line).eof()))
	{
		istringstream i_stringstream(line);

		getline(i_stringstream, str_conma_buf, ',');
		object_name = str_conma_buf.c_str();

		if (strcmp(OBJECT_NAME_DEFAULT, object_name) == 0)
		{
			getline(i_stringstream, str_conma_buf, ',');
			texture_name = str_conma_buf.c_str();

			Location arg_location;
			getline(i_stringstream, str_conma_buf, ',');
			arg_location.x = atof(str_conma_buf.c_str());

			getline(i_stringstream, str_conma_buf, ',');
			arg_location.y = atof(str_conma_buf.c_str());

			getline(i_stringstream, str_conma_buf, ',');
			collider_type = atoi(str_conma_buf.c_str());



			if (collider_type == (int)COLLIDER::POLY_LINE)
			{
				PolyLine* loaded = LoadPolyLine(&i_stringstream);
				objects.push_back
				(new ObjectBase(arg_location,loaded,texture_name.c_str()));
				continue;
			}
		}

		collider_type = atoi(str_conma_buf.c_str());

		if (collider_type == (int)COLLIDER::MAP_CHIP)
		{
			map_chips.push_back(LoadMapChip(&i_stringstream));
			continue;
		}

		if (collider_type == (int)COLLIDER::POLY_LINE)
		{
			poly_lines.push_back(LoadPolyLine(&i_stringstream));
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
			fprintf_s(fp, "%d,%lf,%lf,%d\n",
				map_chips[i]->GetColliderType(),
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
			fprintf_s(fp,"%d", (int)COLLIDER::POLY_LINE);
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
// オブジェクトの保存
//------------------------------------
void StageBuilder::SaveObject(FILE* fp)
{
	if (fp)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			fprintf_s(fp, "%s,%s,%lf,%lf,", 
				objects[i]->GetObjectName(),
				objects[i]->GetTextureName(),
				objects[i]->GetPivot()->GetLocation().x,
				objects[i]->GetPivot()->GetLocation().y
			);


			int collider_type = objects[i]->GetColllider()->GetColliderType();

			switch (collider_type)
			{
			case (int)COLLIDER::MAP_CHIP:
			{
				MapChip* saved
					= static_cast<MapChip*>(objects[i]->GetColllider());
				fprintf_s(fp, "%d,%lf,%lf,%d\n",
					saved->GetColliderType(),
					saved->GetLocation().x,
					saved->GetLocation().y,
					0);
				break;
			}
			case (int)COLLIDER::SPHERE:
			{
				SphereCollider* saved
					= static_cast<SphereCollider*>(objects[i]->GetColllider());
				fprintf_s(fp, "%d,%lf,%lf,%d\n",
					saved->GetColliderType(),
					saved->GetLocation().x,
					saved->GetLocation().y,
					saved->GetRadius()
				);
			}
			case (int)COLLIDER::BOX:
			{
				BoxCollider* saved
					= static_cast<BoxCollider*>(objects[i]->GetColllider());
				fprintf_s(fp, "%d,%lf,%lf,%lf,%lf",
					saved->GetColliderType(),
					saved->GetLocation().x,
					saved->GetLocation().y,
					saved->GetArea().width,
					saved->GetArea().height
				);
			}
			case(int)COLLIDER::LINE:
			{
				LineCollider* saved
					= static_cast<LineCollider*>(objects[i]->GetColllider());
				fprintf_s(fp, "%d,%lf,%lf,%lf,%lf,%lf,%lf",
					saved->GetColliderType(),
					saved->ColliderBase::GetLocation().x,
					saved->ColliderBase::GetLocation().y,
					saved->GetLocation(LINE_START).x,
					saved->GetLocation(LINE_START).y,
					saved->GetLocation(LINE_END).x,
					saved->GetLocation(LINE_END).y
				);
			}
			case(int)COLLIDER::POLY_LINE:
			{
				PolyLine* saved
					= static_cast<PolyLine*>(objects[i]->GetColllider()); 
				fprintf_s(fp, "%d", (int)COLLIDER::POLY_LINE);
				vector<SphereCollider*> points = saved->GetPoints();
				fprintf_s(fp, ",%d", int(points.size()));

				for (int j = 0; j < points.size(); j++)
				{
					fprintf_s(fp, ",%.1lf,%.1lf",
						points[j]->GetLocation().x,
						points[j]->GetLocation().y
					);
				}
				points.clear();
			}


			}
			fprintf_s(fp, "\n");
		}
	}
}

//------------------------------------
// マップチップの読み込み
//------------------------------------
MapChip* StageBuilder::LoadMapChip(istringstream* i_stringstream)
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

	return MakeMapChip(x, y, width, height);

}

//------------------------------------
// 折れ線の読み込み
//------------------------------------
PolyLine* StageBuilder::LoadPolyLine(istringstream* i_stringstream)
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

	return (new PolyLine(&location[0], location.size()));
}

#endif