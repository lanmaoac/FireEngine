#include "plane.h"

Plane::Plane()
{
	//ctor
}

Plane::~Plane()
{
	//dtor
}

Plane::Plane(const GVector3& _normal, float _d)
{
	normal = _normal;
	d = _d;
}
 void Plane::show()
{
	cout << "caotama" << endl;
}
IntersectResult Plane::isIntersected(CRay& ray)
{
	IntersectResult result = IntersectResult::IntersectResult();
	float a = ray.getDirection().dotMul(normal);
	if (a < 0.0)
	{
		result.isHit = 1;
		result.object = this;
		float b = normal.dotMul(ray.getOrigin() - normal*d);
		result.distance = -b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = normal;
		return result;
	}
	result.isHit=0;
	return result;
}

