#ifndef Plane_H
#define Plane_H
#include "gvector3.h"
#include "intersectresult.h"
#include "cray.h"
#include "checkermaterial.h"
#include "cobject.h"
class Plane :public CObject
{
public:
	Plane();
	Plane(const GVector3& _normal, float _d);
	virtual ~Plane();
	virtual void show();
	virtual IntersectResult isIntersected(CRay& RAY);
protected:
private:
	//法向量
	GVector3 normal;
	//到原点的距离
	float d;
};

#endif // Plane_H
