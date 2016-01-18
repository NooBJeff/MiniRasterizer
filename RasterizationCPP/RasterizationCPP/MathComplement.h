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

#include <cmath>
#include "Declarations.h"

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

	//�����Ĺ�һ��
	void VectorUnify();

	//�������
	Vector3 CrossProduct(const Vector3);

	//�������
	float DotProduct(const Vector3);

	//���ظ��ݵ�ǰ�������ɵ�ƽ�ƾ���
	Matrix4 GetTransitonMatrix();


	/////////////////////
	//��������ز���  //
	////////////////////

	//3����������3�׾���
	Vector3 operator * (const Matrix3);
	
	//�ӵ����������
	Vector3 operator + (const Vector3);
	//�������������
	Vector3 operator - (const Vector3);
};

/*
����
3 x 3

����3�׾�����ʹ�ù����в��Ǻܳ���
�����ݲ�����������ȵ�"�߼�"����
*/
class Matrix3 {
public:
	float var[3][3];

	Matrix3();
	Matrix3(const Matrix3&);
	~Matrix3() {}

	void SetZero();


	/////////////////////
	//��������ز���  //
	////////////////////

	//���س˷�
	Matrix3 operator * (const Matrix3&);
	Matrix3 operator * (const float&);
};


/***************************
����
4 x 4
***************************/

class Matrix4 {
public:
	float var[4][4];

	//�����Ĺ������
	Matrix4();
	Matrix4(const Matrix4&);
	~Matrix4() {}
	void SetZero();


	/////////////////////////
	// �����ô��Ĺ������ //
	/////////////////////////

	//�����Խ���Ԫ��Ϊ������ֵ�ľ���
	//����Ԫ��Ϊ0
	Matrix4(float);

	//����ƽ�ƾ���
	Matrix4(const Vector3&);
	//todo
	//MAtrix4(float x,float y,float z);

	//������ת����
	//��ת��λΪ ����
	//���� +90 ��
	//�Ƶ�һ�����ת
	Matrix4(char axis, float degree);
	//�����������������ת����
	//todo
	Matrix4(float degreeX, float degreeY, float degreeZ);

	////////////////�����ǹ��캯��////////////////

	//������������ƽ�ƾ���
	void TransitionMatrix(const Vector3 &);

	//fixme
	//������ת�Ĳ�������ǰ�������ó�Ϊ��ת����
	//void GetRotateSingleAxis(char axis, float degree);
	
	//������ʽ
	float Determinant(Matrix3&);
	//�������
	void Invert();

	/////////////////////
	//��������ز���  //
	////////////////////

	//���س˷�
	//���� x ����
	Matrix4 operator * (const  Matrix4&);
	//���� x ����
	Matrix4 operator * (const float&);
};

#endif