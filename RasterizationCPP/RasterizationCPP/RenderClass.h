#ifndef RASTERIZER_RENDERCLASS_H
#define RASTERIZER_RENDERCLASS_H
/*
��Ⱦ��
������ѧ���㲢�����ɵ�ͼ�������Canvas

������:
������
�������

ʱ�������
����ÿ����Ⱦ��ȥ����ʱ��
*/

////////////
// ������ //
////////////
#include "ProjectHeader.h"
#include "CanvasClass.h"
#include "CameraClass.h"
#include "ObjectClass.h"

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

	void computeTime() {
		currentClock = (float)clock();
		push((currentClock - previousClock) / CLK_TCK);
		previousClock = currentClock;
	}

	void push(float gap) {
		sumOfqueue -= qFPS.front();
		qFPS.pop();
		sumOfqueue += gap;
		qFPS.push(gap);
	}

	float getFPS() {
		return ((float)size / sumOfqueue);
	}

	wstring getFPSwstring() {
		InfoFPS.clear();

		wstringstream ws;
		ws << TEXT("FPS : ") << getFPS();
		InfoFPS = ws.str();
		return InfoFPS;
	}
};

class RenderClass
{
private:
	//������
	CanvasClass *m_Canvas;
	//�������
	CameraClass *m_Camera;
	
	TimeClass fps;

	//��ǰ����
	//�����õ��ļ����м�����
private:
	Matrix4 WorldToView;
	//ViewToHomo �����������
	void Draw();
public:
	RenderClass();
	~RenderClass();

	void Initialize(RECT,HDC);
	void Shutdown();

	//���Ļ����������
	void UpdateCanvasSettings(RECT newRect);

	//��Ⱦһ֡
	void RenderAFrame();

	//ģ������
public:
	vector<Object> RenderObjects;
};

#endif