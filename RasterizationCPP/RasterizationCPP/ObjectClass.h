#ifndef RASTERIZER_OBJECTCLASS_H
#define RASTERIZER_OBJECTCLASS_H

#include "ProjectHeader.h"

#include "jsonparser\jsonxx.h"
#include <fstream>
using std::ifstream;

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

//Ŀǰһ��Object����һ��������
class ObjectClass {
	//�����ε�����
public:
	vector<Vector3> vertices;
	vector<int> indices;

	Vector3 position;
	Vector3 rotation;

public:
	///////////////
	// ���캯�� //
	///////////////
	ObjectClass();
	//todo
	void Initial(char*);
	//����Position
	ObjectClass(Vector3);
	//����Pos �� Rotation
	ObjectClass(Vector3, Vector3);
};

#endif