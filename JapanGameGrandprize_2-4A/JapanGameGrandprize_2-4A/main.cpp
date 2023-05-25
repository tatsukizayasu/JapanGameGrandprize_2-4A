#include "DxLib.h"
#include "Define.h"
#include "Scene/SceneManager.h"
#include "Scene/GameMain.h"
#include "PadInput.h"
#include "Scene/Title.h"
#include "EnemySE.h"
#include "EnemyBase.h"
#include "Pouch.h"

#define FRAMERATE 60.0 //フレームレート

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	double dNextTime = GetNowCount();

	SetMainWindowText("Science Revenge");

	SetWindowIconID(01);

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	SetAlwaysRunFlag(true);		//常にアクティブにする

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//画面サイズの設定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager* sceneMng;

	try
	{
		unsigned int a[7];
		
		sceneMng = new SceneManager((AbstractScene*)new Title());
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	EnemyBase::LoadWeakness();
	EnemySE::LoadSound();
	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr))
	{

		ClearDrawScreen();		// 画面の初期化
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();

		//強制終了
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
		{
			break;
		}
#ifdef _DEBUG
		//レイアウト設計用
		if (PAD_INPUT::OnPressed(XINPUT_BUTTON_X))
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			for (int x = 0; x < 1280; x += 40)
			{
				DrawLineAA(x, 0, x, 720, 0x000000, 0.01F);
				for (int y = 0; y < 720; y += 40) 
				{
					DrawLineAA(0, y, 1280, y, 0x000000, 0.01F);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
#endif

		ScreenFlip();			// 裏画面の内容を表画面に反映

		//フレームレートの設定
		dNextTime += 1.0 / 60.0 * 1000.0;

		if (dNextTime > GetNowCount()) 
		{
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//補正
	}

	EnemySE::DeleteSound();
	EnemyBase::DeleteWeakness();

	return 0;
}