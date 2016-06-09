#ifndef RASTERIZER_OBJECTCLASS_H
#define RASTERIZER_OBJECTCLASS_H

#include "ProjectHeader.h"

//��������Ļ���
class Object {
public:
	bool active;
	//��������
	//����
	string tag;
	//����λ��
	Vector3 position;
	//������ת���
	Vector3 rotation;

public:
	//���캯��
	//�����������
	Object() { active = true; }
	Object(string _name) :tag(_name) {};

	//ÿ֡����
	virtual void update() = 0;
	//����ʱ����
	virtual void init() = 0;
};

#endif