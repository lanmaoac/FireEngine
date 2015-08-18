#ifndef UNION_H
#define UNION_H
#include "cobject.h"
#include <vector>
using namespace std;

class Union :public CObject
{
public:
	Union();
	virtual ~Union();
	void push(CObject* object);
	virtual IntersectResult isIntersected(CRay& _ray);
protected:
private:
	vector<CObject*> cobjects;
};

#endif // UNION_H
