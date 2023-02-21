#include "Element_MoveFloor.h"

Element_MoveFloor::Element_MoveFloor()
{
	image = LoadGraph("Images/Stage/test.png");

	se = LoadSoundMem("Sounds/Stage/test.mp3");
}

Element_MoveFloor::~Element_MoveFloor()
{
	DeleteGraph(image);
	DeleteSoundMem(se);
}

void Element_MoveFloor::Update()
{


}

void Element_MoveFloor::Draw() const
{
}
