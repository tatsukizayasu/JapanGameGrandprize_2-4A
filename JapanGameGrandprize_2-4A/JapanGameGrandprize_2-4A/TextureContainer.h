#pragma once
#include <map>
#include "DxLib.h"

class TextureContainer
{
private:
	TextureContainer();
	static TextureContainer* instance;

	std::map<const char*, int>texture;

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

