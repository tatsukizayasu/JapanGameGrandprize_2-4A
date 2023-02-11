#pragma once
#include <direct.h>
class Directory
{
private:
	static char str[10];
	static char* main_dir; //main関数があるディレクトリ
	static char* current_dir; //現在のディレクトリ

public:
	//カレントディレクトリの更新
	static void Update()
	{
		current_dir = _getcwd(current_dir, 256);
	}

	//初期化 初回はmainディレクトリを取ってくる、それ以降はmainディレクトリを開く
	static bool Init()
	{
		bool isSuccess = false;
		if (main_dir == nullptr)
		{
			main_dir = _getcwd(main_dir, 256);
			current_dir = _getcwd(current_dir, 256);
			isSuccess = true;
		}
		else
		{
			if (OpenMain())isSuccess = true;
		}

		return isSuccess;
	}

	//カレントディレクトリからの相対パスでディレクトリを移動する
	static bool Open(const char* path);

	//main関数があるディレクトリを開く
	static bool OpenMain()
	{
		bool isSuccess = false;
		if (_chdir(main_dir) != -1)isSuccess = true;
		return isSuccess;
	}

	static char* GetCurrent() { return current_dir; }
};

