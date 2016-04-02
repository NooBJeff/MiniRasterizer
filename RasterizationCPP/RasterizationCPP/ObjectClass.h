#ifndef RASTERIZER_OBJECTCLASS_H
#define RASTERIZER_OBJECTCLASS_H

#include "ProjectHeader.h"

//Ŀǰһ��Object����һ��������
class Object {
public:
	vector<Vector3> vertices;
	vector<Vector2<float>> uv;
	vector<Vector2<int>> indices;

	HDC hdc_texture;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
public:
	///////////////
	// ���캯�� //
	///////////////
	Object();
	int Initial(char*, LPCWSTR);
	//����Position
	Object(Vector3);
	//����Pos �� Rotation
	Object(Vector3, Vector3);
};

#endif