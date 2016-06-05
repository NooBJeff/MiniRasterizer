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
���������ֵĳ˷�
*/

#include "ProjectHeader.h"

///////////////
// ��ǰ���� //
//////////////

template < class T = float >
class Vector2;

class Vector3;
class Vector4;
class Matrix3;
class Matrix4;
typedef struct Fragment_TYPE Fragment;

///////////
// ���� //
//////////

//����
template <typename T>
void swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

//Clipping
//ֻҪ��һ���������棬�Ͳ�Ҫ
//ͬʱ���б����޳�
void ClippingAndBackCull(vector<Fragment> &render_list);

//tranform vertices from Homo to Screen coordinate
void HomoToScreenCoord(Vector4& vertex);

//////////////////////
// ��ѧ�ࡢ�ṹ�� //
/////////////////////
template <class T>
class Vector2 {
public:
	T x, y;

	Vector2() {
		x = y = 0;
	}

	Vector2(T all) {
		x = y = all;
	}

	Vector2(T _x, T _y) {
		x = _x;
		y = _y;
	}

	Vector2(const Vector2& old) {
		x = old.x;
		y = old.y;
	}

	Vector2<T> operator * (float b) {
		return Vector2<T>(x * b, y * b);
	}
};

/*******************************
Vector 3
���ڱ�ʾ��ά�ռ�ĵ㡢��ת����
*******************************/
class Vector3 {
public:
	//ֵ
	float x, y, z;

	//���캯��
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float _both) {
		x = y = z = _both;
	}
	Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}
	Vector3(const Vector3 &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}
	~Vector3(){}

	//�����Ĺ�һ��
	void VectorUnify();

	//�������
	Vector3 CrossProduct(const Vector3&);

	//�������
	float DotProduct(const Vector3&);

	//���ظ��ݵ�ǰ�������ɵ�ƽ�ƾ���
	Matrix4 GetTransitonMatrix();


	/////////////////////
	//��������ز���  //
	////////////////////

	//3����������3�׾���
	Vector3 operator * (const Matrix3&);
	//3����������4�׾���
	Vector4 operator * (const Matrix4&);

	//�ӵ����������
	Vector3 operator + (const Vector3&);
	//�������������
	Vector3 operator - (const Vector3&);

	//���������
	friend wstringstream& operator << (wstringstream&,  const Vector3&);
};


/****************
Vector 4

������μ��ʿռ����Ӧ����
*******************/

class Vector4 {
public:
	//ֵ
	float x, y, z, w;

	//���캯��
	Vector4() {
		x = y = z = w = 0.0f;
	}
	Vector4(float _both) {
		x = y = z = w = _both;
	}
	Vector4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	Vector4(const Vector4 &copy) {
		x = copy.x;
		y = copy.y;
		z = copy.z;
		w = copy.w;
	}

	//�� �� ���� ת�����������ϵ
	Vector4(const Vector3& old, bool isVertex) {
		x = old.x;
		y = old.y;
		z = old.z;
		w = isVertex ? 1.0f : 0.0f;
	}

	~Vector4() {}

	//�������ϵ�ı任
	Vector4 operator* (const Matrix4& b);

	void VectorUnify();

	//���������
	friend wstringstream &operator << (wstringstream&, const Vector4&);
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

	void SetZero() {
		memset(var, 0, 4 * 4 * sizeof(float));
	}


	/////////////////////////
	// �����ô��Ĺ������ //
	/////////////////////////

	//����ƽ�ƾ���
	Matrix4(const Vector3&);
	Matrix4(float x, float y, float z);

	//������ת����
	//��ת��λΪ ����
	//���� ��90 ��
	//�Ƶ�һ�����ת
	Matrix4(char axis, float degree);

	//���� ���š���ת��ƽ�� ���ɾ���
	Matrix4(Vector3 scale, Vector3 Rotation, Vector3 Position);

	//�������
	Matrix4(Matrix4&, const Matrix4&);

	////////////////�����ǹ��캯��////////////////
	//todo
	//inline

	//������������ƽ�ƾ���
	Matrix4& createTransitionMatrix4(const Vector3&);
	Matrix4& createTransitionMatrix4(float x = 0, float y = 0, float z = 0);

	//��ת����
	Matrix4& createRotationMatrix4(const Vector3&);
	Matrix4& createRotationMatrix4(float x = 0, float y = 0, float z = 0);

	//���ž���
	Matrix4& createScaleMatrix4(const Vector3&);
	Matrix4& createScaleMatrix4(float x = 0, float y = 0, float z = 0);

	//�ڵ�ǰ�����Ͻ��в���
	//����ƽ��
	Matrix4& changePosition(const Vector3&);
	Matrix4& changePosition(float x = 0, float y = 0, float z = 0);

	//������ת
	Matrix4& changeRotationSingleAxis(char axis, float degree);
	Matrix4& changeRotationMultiAxes(const Vector3&);
	Matrix4& changeRotationMultiAxes(float x = 0, float y = 0, float z = 0);

	//��������
	Matrix4& changeScale(const Vector3&);
	Matrix4& changeScale(float x = 0, float y = 0, float z = 0);


	//������ʽ
	float Determinant(const Matrix3&);
	//�������
	Matrix4& Invert();

	////////////////
	// static ���� //
	///////////////

	//todo

	/////////////////////
	//��������ز���  //
	////////////////////

	//���س˷�
	//���� x ����
	Matrix4 operator * (const  Matrix4&);
	//���� x ����
	Matrix4 operator * (const float&);
};

//���һ����Ҫ��Ⱦ��������
typedef struct Fragment_TYPE {
	int state;
	HDC *texture;

	//�任��Ķ���
	array<Vector4, 3> trans_vList;
	//�������ͼ��������
	//ÿ�������� 2 ��������Ϣ
	array<Vector2<float>, 3> uvList;
	//����ķ�����
	Vector3 n;

	Fragment_TYPE(int _state, HDC *_texture) : state(_state), texture(_texture) {}
	~Fragment_TYPE() {
		texture = nullptr;
	}
}Fragment;

#endif
