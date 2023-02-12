#include "Directory.h"
#include "DxLib.h"
#include <string.h>

string Directory::main_dir;
string Directory::current_dir;

bool Directory::Open(const char* path)
{
	bool isSuccess = false;

	current_dir += path;

	if (_chdir(current_dir.c_str()) != -1)isSuccess = true;

	Update();
	return isSuccess;
}