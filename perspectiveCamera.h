#ifndef PerspectiveCamera_H
#define PerspectiveCamera_H
#include "cray.h"
class PerspectiveCamera{
public:
	PerspectiveCamera();
	~PerspectiveCamera();
	PerspectiveCamera(const GVector3& _eye, const GVector3& _front, const GVector3& _refUp, float _fov);
	CRay generateRay(float x, float y);

private:
	GVector3 eye;
	GVector3 front;
	GVector3 refUp;
	float   fov;
	GVector3 right;
	GVector3 up;
	float   fovScale;
};
#endif
