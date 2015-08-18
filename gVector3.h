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
	// ȱʡ���캯��
	GVector3();
	~GVector3();
	// �û����캯��
	GVector3(float posX, float posY, float posZ);
	//���������Ϣ
	void getInfo();
	//ʸ���ӷ�
	GVector3 operator+(GVector3 v);
	//ʸ������
	GVector3 operator-(GVector3 v);
	//����
	GVector3 operator*(float n);
	//����
	GVector3 operator/(float n);
	//�������
	float dotMul(GVector3 v2) const;
	//�������
	GVector3 crossMul(GVector3 v2);
	//����ֵ��
	GVector3 abs();
	//��ȡ�����е����ֵ
	float max();
	//��ȡ��������Сֵ
	float min();
	//��ȡʸ������
	float getLength();
	//������λ��
	GVector3 normalize();
	//������֮��ľ���
	float getDist(GVector3 v);
	//����������
	GVector3 zero();
	//��ӡ�����ķ���ֵ
	void show();

};

#endif // GVECTOR3_H
