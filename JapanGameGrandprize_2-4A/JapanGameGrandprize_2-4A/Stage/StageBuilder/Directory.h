#pragma once
#include <direct.h>
#include <string>
#define DIRECTORY_BUFFER_SIZE 256
using namespace std;
class Directory
{
private:
	static string main_dir; //main関数があるディレクトリ
	static string current_dir; //現在のディレクトリ

public:
	//カレントディレクトリの更新
	static void Update()
	{
		char buffer[DIRECTORY_BUFFER_SIZE];
		const char* get_current = _getcwd(buffer, DIRECTORY_BUFFER_SIZE);
		current_dir = buffer;

	}

	//初期化 初回はmainディレクトリを取ってくる、それ以降はmainディレクトリを開く
	static bool Init()
	{
		bool isSuccess = false;
		if (main_dir.empty())
		{
			char buffer[DIRECTORY_BUFFER_SIZE];
			const char* get_current = _getcwd(buffer, DIRECTORY_BUFFER_SIZE);
			main_dir = buffer;
			current_dir = buffer;
			isSuccess = true;
		}
		else
		{
			if (OpenMain())
			{
				Update();
				isSuccess = true;
			}
		}

		return isSuccess;
	}

	//カレントディレクトリからの相対パスでディレクトリを移動する
	static bool Open(const char* path);

	//main関数があるディレクトリを開く
	static bool OpenMain()
	{
		bool isSuccess = false;
		if (!main_dir.empty())
		{
			if (_chdir(main_dir.c_str()) != -1)isSuccess = true;

			Update();
		}
		return isSuccess;
	}

	static const char* GetCurrent() { return current_dir.c_str(); }
};

