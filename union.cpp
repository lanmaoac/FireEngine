#include "union.h"

Union::Union()
{
	//ctor
}

Union::~Union()
{
	//dtor
}
void Union::push(CObject* object)

{
	cobjects.push_back(object);
}
IntersectResult Union::isIntersected(CRay& _ray)
{
	const float Infinity = 1e30;
	float minDistance = Infinity;
	IntersectResult minResult = IntersectResult::IntersectResult();
	long size = cobjects.size();
	for (long i = 0; i<size; ++i){
		IntersectResult result = cobjects[i]->isIntersected(_ray);
		if (result.distance < minDistance) {
			minDistance = result.distance;
			minResult = result;
			minResult.isHit = 1;
			minResult.object = cobjects[i];
		}
	}
	return minResult;
}
