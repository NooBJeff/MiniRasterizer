#ifndef RASTERIZER_CUSTOMOBJECTS_H
#define RASTERIZER_CUSTOMOBJECTS_H

#include "ProjectHeader.h"

#include "GameObjectClass.h"

//Ϊ��static
#include "SceneManagerClass.h"
#include "TimeClass.h"
#include "InputClass.h"

#include <cmath>
#include <ctime>

//�������0-1֮�����
double random() {
	return (double)std::rand() / RAND_MAX;
}

//���ļ�֮�ⲻ�ɼ�
static int GridLength = 10;

//ÿһ������
class Body : public GameObject {
public:
	int x;
	int y;

	//��ʼ��λ��
	Body(int _x, int _y) {
		x = _x;
		y = _y;
	}

	void init() {
		model = "cube";
		//һ������1��λ��
		scale = Vector3(0.1f);
	}

	//ʲôҲ����
	void update() {

	}
};

//̰���ߵ�����
class Snake : public GameObject {
public:
	//����ÿ����һ��
	//ȫ�ֵ��Ǹ�ҲҪ��Ӧ����һ��
	vector<shared_ptr<Body>> snake;
	vector<shared_ptr<Object>>* reference_objects_all;

public:
	//���캯��
	Snake() {
		reference_objects_all = nullptr;
	}

	void init() {
		auto head = make_shared<Body>((int)(random() * GridLength), (int)(random() * GridLength));
		snake.push_back(head);
		reference_objects_all->push_back(head);

	}

	void update() {

	}

	void moveForward() {

	}
};

//����̰���߳���
class SnakeFrame : public GameObject {
private:
	Snake snake_body;
	
public:
	//��ʼ��Snake
	SnakeFrame() {
		snake_body.reference_objects_all = &SceneManager::s_ptr_scene_manager->objects_all;
	}

	void init() {
		std::srand((unsigned int)std::time(0));
	}

	void update() {

	}
};

#endif