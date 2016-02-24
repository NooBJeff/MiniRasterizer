#include "ObjectClass.h"

Object::Object() {
	Initial();

	Position.x = Position.y = Position.z = 0.0f;
	Rotation.x = Rotation.y = Rotation.z = 0.0f;
}

Object::Object(Vector3 Pos) {
	Initial();

	Position = Pos;
	Rotation.x = Rotation.y = Rotation.z = 0.0f;
}

Object::Object(Vector3 Pos, Vector3 rotation) {
	Initial();

	Position = Pos;
	Rotation = rotation;
}

void Object::Initial() {
	//�����ε�������
	vertices.push_back(Vector3(0.0f));
	vertices.push_back(Vector3(0.f, 100.0f, 0.f));
	vertices.push_back(Vector3(100.f, 0.f, 0.f));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	
	//�������������UV����
	/*
	vertexUV[0].u = 0.0f; vertexUV[0].v = 0.0f;
	vertexUV[1].u = 512.0f; vertexUV[1].v = 512.0f;
	vertexUV[2].u = 0.0f; vertexUV[2].v = 512.0f;
	*/
}