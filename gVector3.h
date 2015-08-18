#ifndef GVECTOR3_H
#define GVECTOR3_H
#include <iostream>
#include <cmath>
using namespace std;


class GVector3
{

public:
	float x;
	float y;
	float z;
	// 缺省构造函数
	GVector3();
	~GVector3();
	// 用户构造函数
	GVector3(float posX, float posY, float posZ);
	//输出向量信息
	void getInfo();
	//矢量加法
	GVector3 operator+(GVector3 v);
	//矢量减法
	GVector3 operator-(GVector3 v);
	//数乘
	GVector3 operator*(float n);
	//数除
	GVector3 operator/(float n);
	//向量点积
	float dotMul(GVector3 v2) const;
	//向量叉乘
	GVector3 crossMul(GVector3 v2);
	//绝对值化
	GVector3 abs();
	//获取分量中的最大值
	float max();
	//获取分量的最小值
	float min();
	//获取矢量长度
	float getLength();
	//向量单位化
	GVector3 normalize();
	//求两点之间的距离
	float getDist(GVector3 v);
	//返回零向量
	GVector3 zero();
	//打印向量的分量值
	void show();

};

#endif // GVECTOR3_H
