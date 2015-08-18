#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H
#include "gvector3.h"
#include <iostream>
class CObject;
struct IntersectResult{
    CObject* object;
	float distance;
	bool isHit;
	GVector3 position;
	GVector3 normal;
	IntersectResult()
	{ 
		object = NULL;
		distance = 1e31;
		isHit = 0;
		position = GVector3(0.0, 0.0, 0.0);
		normal = GVector3(0.0, 0.0, 0.0);
	}
	void show()
	{
		position.show();
	}
};
#endif 
