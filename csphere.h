#ifndef CSPHERE_H
#define CSPHERE_H
#include "gvector3.h"
#include "intersectresult.h"
#include "cray.h"
#include "material.h"
#include "phongmaterial.h"
#include "cobject.h"
class CSphere :public CObject
{
public:
	CSphere();
	CSphere(GVector3 center, double radius);
	CSphere(CSphere& s);
	void setCenter(GVector3& c);
	void setRadius(double r);
	virtual void show();
	GVector3 getCenter();
	double getRadius();
	//��ȡ�������һ��ķ���
	virtual GVector3 getNormal(GVector3 point);
	//�����ж����ߺ͸�����Ľ���
	virtual IntersectResult isIntersected(CRay& ray);
	virtual ~CSphere();
protected:
private:
	GVector3 center;
	double radius;
};

#endif // CSPHERE_H
