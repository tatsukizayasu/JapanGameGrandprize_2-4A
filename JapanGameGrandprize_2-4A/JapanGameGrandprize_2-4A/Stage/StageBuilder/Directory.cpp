#include "Directory.h"
#include "DxLib.h"
#include <string.h>

char Directory::str[10] = "null";
char* Directory::main_dir = nullptr;
char* Directory::current_dir = nullptr;

bool Directory::Open(const char* path)
{
	bool isSuccess = false;

	strncat(current_dir, path,256);

	if (_chdir(current_dir) != -1)isSuccess = true;
	return isSuccess;
}