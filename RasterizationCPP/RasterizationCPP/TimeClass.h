#ifndef RASTERIZER_TIMECLASS_H
#define RASTERIZER_TIMECLASS_H

#include "ProjectHeader.h"

class TimeClass {
private:
	float sumOfqueue;
	queue<float> qFPS;
	int size;
	wstring InfoFPS;

	//���ڼ���֡���Ķ���
	float previousClock;
	float currentClock;
	//�ϴ���Ⱦһ֡���ȥ��ʱ��
	float deltaTime;
public:
	TimeClass() {
		previousClock = currentClock = 0.0f;
		deltaTime = 1.0f / 60;
		size = 60;

		sumOfqueue = size * deltaTime;
		for (int lop = 0; lop < size; lop++) {
			qFPS.push(deltaTime);
		}
	}

	float getDeltaTime() {
		return deltaTime;
	}

	//����ÿ֡�ĺ�ʱ
	void computeTime() {
		currentClock = (float)clock();
		deltaTime = (currentClock - previousClock) / CLK_TCK;
		push(deltaTime);
		previousClock = currentClock;
	}

	void push(float gap) {
		sumOfqueue -= qFPS.front();
		qFPS.pop();
		sumOfqueue += gap;
		qFPS.push(gap);
	}

	//��õ�ǰ��֡��
	float getFPS() {
		return ((float)size / sumOfqueue);
	}

	//���֡�����ַ�����Ϣ
	wstring getFPSwstring() {
		InfoFPS.clear();

		wstringstream ws;
		ws << TEXT("FPS : ") << getFPS();
		InfoFPS = ws.str();
		return InfoFPS;
	}
};


#endif