#include "SceneManager.h"
#include "DxLib.h"
#include <time.h>
#include "../FpsController.h"

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* SceneManager::Update()
{

	AbstractScene* NextScene;
	try
	{
		NextScene = mScene->Update();
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

		return nullptr;
	}

	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}

	return mScene;
}

//-----------------------------------
// 描画
//-----------------------------------
void SceneManager::Draw() const
{

	mScene->Draw();
}