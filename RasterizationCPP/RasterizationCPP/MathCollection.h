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

#include "Declarations.h"

//��ά�ռ�����
class FLOAT3D {
public:
	//ֵ
	float x, y, z;

	//���캯��
	FLOAT3D() {
		x = y = z = 0.0f;
	}
	FLOAT3D(float _both) {
		x = y = z = _both;
	}
	FLOAT3D(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	FLOAT3D(const FLOAT3D &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}

	//�������
	FLOAT3D CrossProduct(const FLOAT3D);

	//�������
	float DotProduct(const FLOAT3D);
	
	//�ӵ����������
	FLOAT3D operator + (const FLOAT3D);
	//�������������
	FLOAT3D operator - (const FLOAT3D);
};


#endif