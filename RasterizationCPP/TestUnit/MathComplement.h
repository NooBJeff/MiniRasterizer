#ifndef RASTERIZER_MATHCLASS_H
#define RASTERIZER_MATHCLASS_H

/*
����������ѧ��������ĺ����ȵ�
�������
��ά����
��ά����

����֮��ĵ�������
����֮��ļӷ�������
�����Ĺ�һ��

���׾���
�Ľ׾���

�Լ�����֮��ĳ˷����ӷ�
����ĵ�λ��
���������ֵĳ˷�
*/

//#include "Declarations.h"
#include <string.h>


class Vector3;
class Vector4;
class Martix3;
class Martix4;


//��ά�ռ�����
class Vector3 {
public:
	//ֵ
	float x, y, z;

	//���캯��
	Vector3() {
		x = y = z = 0.0f;
	}
	Vector3(float _both) {
		x = y = z = _both;
	}
	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3(const Vector3 &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}
	~Vector3(){}

	//�������
	Vector3 CrossProduct(const Vector3);

	//�������
	float DotProduct(const Vector3);

	//3����������3�׾���
	Vector3 operator * (const Martix3);
	
	//�ӵ����������
	Vector3 operator + (const Vector3);
	//�������������
	Vector3 operator - (const Vector3);
};

/*
����
3 3

����3�׾�����ʹ�ù����в��Ǻܳ���
�����ݲ�����������Ĺ���
*/
class Martix3 {
public:
	float var[3][3];

	Martix3();
	Martix3(const Martix3&);
	~Martix3() {}

	void SetZero();

	//���س˷�
	Martix3 operator * (const Martix3&);
	Martix3 operator * (const float&);
};


/*
����
4 4
*/

class Martix4 {
public:
	float var[4][4];

	Martix4();
	Martix4(float);
	Martix4(const Martix4&);
	~Martix4() {}
	void SetZero();

	//������ʽ
	float Determinant(Martix3&);
	//�������
	void Invert();

	//���س˷�
	//���� x ����
	Martix4 operator * (const  Martix4 &);
	//���� x ����
	Martix4 operator * (const float&);
};

#endif