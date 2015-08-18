#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include"gvector3.h"
#include "color.h"
#include "cray.h"
#include "material.h"
// global temp
static GVector3 lightDir = GVector3(1, 1, 1).normalize();
static Color lightColor = Color::white();
class PhongMaterial :public Material
{
public:
	PhongMaterial();
	PhongMaterial(const Color& _diffuse, const Color& _specular, const float& _shininess, float _reflectiveness = 0);
	virtual Color sample(const CRay& ray, const GVector3& position, const GVector3& normal);
	virtual ~PhongMaterial();
protected:
private:
	Color   diffuse;
	Color   specular;
	float   shininess;
};

#endif // PHONGMATERIAL_H
