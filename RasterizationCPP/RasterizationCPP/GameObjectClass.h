#ifndef RASTERIZER_GAMEOBJECTCLASS_H
#define RASTERIZER_GAMEOBJECTCLASS_H

#include "ProjectHeader.h"

#include "ObjectClass.h"

class GameObject : public Object {
public:
	//��������
	Vector3 scale;
	string model;
public:
	GameObject() {}

	/////////
	// �̳� //
	/////////
	void init() {};
	void update() {};
};

#endif