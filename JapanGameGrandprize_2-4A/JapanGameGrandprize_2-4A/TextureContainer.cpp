#include "TextureContainer.h"
#include <string.h>
#include <stdexcept>

TextureContainer* TextureContainer::instance = nullptr;

//---------------------------------
// コンストラクタ
//---------------------------------
TextureContainer::TextureContainer()
{
	;
}

//---------------------------------
// デストラクタ
//---------------------------------
TextureContainer::~TextureContainer()
{

}

//---------------------------------
// コンテナの削除
//---------------------------------
void TextureContainer::Delete()
{
	delete instance;
	instance = nullptr;
}

//---------------------------------
// 画像の取得
//---------------------------------
 int TextureContainer::GetTexture(const char* texture_name)
{
	int image_handle = 0;
	std::string _texture_name(texture_name);
	/*decltype (texture)::iterator it = texture.find(texture_name);
	if (it == texture.end()&&)
	{
		char path[100] = "images/Stage/";
		strcat_s(path, texture_name);
		strcat_s(path, ".png");
		if ((image_handle = LoadGraph(path)) == -1)
		{
			throw path;
			return 0;
		}
		else
		{
			texture.insert(std::make_pair(texture_name, image_handle));
		}
	}
	*/
	try
	{
		image_handle = texture.at(_texture_name);
	}
	catch(const std::out_of_range & error)
	{
		_texture_name = "images/Stage/" + _texture_name;
		_texture_name += ".png";

		if ((image_handle = LoadGraph(_texture_name.c_str())) == -1)
		{
			throw _texture_name.c_str();
			return 0;
		}
		else
		{
			texture.insert(std::make_pair(
				std::string (texture_name)
				, image_handle));
		}
	}

	return image_handle;
}

//---------------------------------
// 
//---------------------------------



//---------------------------------
// 
//---------------------------------

