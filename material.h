#ifndef Material_H
#define Material_H
#include "gvector3.h"
#include "intersectresult.h"
#include "cray.h"
#include "color.h"
class Material
{
public:
	Material();
	Material(float _reflectiveness);
	float getRef();
	void setRef(float _reflectiveness);
	virtual ~Material();
	virtual Color sample(const CRay& ray, const GVector3& position, const GVector3& normal);
protected:
	float reflectiveness;
private:

};

#endif // Material_H
