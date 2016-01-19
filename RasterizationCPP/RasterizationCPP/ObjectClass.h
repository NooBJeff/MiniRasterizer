#ifndef RASTERIZER_OBJECTCLASS_H
#define RASTERIZER_OBJECTCLASS_H

#include "ProjectHeader.h"

struct UV {
	float u, v;

	UV(float a, float b) {
		u = a;
		v = b;
	}
	UV() {
		u = v = 0.0f;
	}
};

//һ��Object����һ��������
class Object {
	//�����ε�����
public:
	Vector3 vertex[3];
	Vector4 transformedVertex[3];
	UV vertexUV[3];

	Vector3 Position;
	Vector3 Rotation;

public:
	///////////////
	// ���캯�� //
	///////////////

	Object();
	//����Position
	Object(Vector3);
	//����Pos �� Rotation
	Object(Vector3, Vector3);


	//���Ͼ���
	//todo
	Vector4 Transform(Matrix4);

private:
	void Initial();
};

#endif