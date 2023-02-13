#pragma once
#include "Define.h"

#define RADIUS_MAX 20

class EfectBeam
{
private:
	Location location;
	float filling_radius_x;
	float filling_radius_y;

	
public:
	EfectBeam();
	~EfectBeam() {};

	void Draw() const;
	void Update(float,float);
};

