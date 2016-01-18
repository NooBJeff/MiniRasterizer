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
class Matrix3;
class Matrix4;


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
	Vector3 operator * (const Matrix3);
	
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
class Matrix3 {
public:
	float var[3][3];

	Matrix3();
	Matrix3(const Matrix3&);
	~Matrix3() {}

	void SetZero();

	//���س˷�
	Matrix3 operator * (const Matrix3&);
	Matrix3 operator * (const float&);
};


/*
����
4 4
*/

class Matrix4 {
public:
	float var[4][4];

	Matrix4();
	Matrix4(float);
	Matrix4(const Matrix4&);
	~Matrix4() {}
	void SetZero();

	//������ʽ
	float Determinant(Matrix3&);
	//�������
	void Invert();

	//���س˷�
	//���� x ����
	Matrix4 operator * (const  Matrix4 &);
	//���� x ����
	Matrix4 operator * (const float&);
};

#endif