#pragma once
#include <map>
#include <string>
#include "DxLib.h"

class TextureContainer
{
private:
	TextureContainer();
	static TextureContainer* instance;

	std::map<std::string, int>texture;

public:
	~TextureContainer();

	static void Delete();
	static TextureContainer* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new TextureContainer();
		}

		return instance;
	}

	int GetTexture(const char* texture_name);
};

