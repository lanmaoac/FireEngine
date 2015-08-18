#ifndef COBJECT_H
#define COBJECT_H
#include "material.h"
#include "intersectresult.h"
#include "cray.h"

class CObject
{
public:
	Material* material;
	CObject();
	virtual IntersectResult isIntersected(CRay& _ray) = 0;
	virtual ~CObject();
	virtual void show();
protected:

private:
};

#endif // COBJECT_H
