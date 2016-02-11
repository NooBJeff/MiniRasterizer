#ifndef RASTERIZER_RENDERCLASS_H
#define RASTERIZER_RENDERCLASS_H
/*
��Ⱦ��
������ѧ���㲢�����ɵ�ͼ�������Canvas

������:
������
TODO �������
*/

////////////
// ������ //
////////////
#include "ProjectHeader.h"
#include "CanvasClass.h"
#include "CameraClass.h"
#include "ObjectClass.h"

#include <ctime>
using std::clock;
#include <queue>
using std::queue;

class fpsClass {
private:
	float sumOfqueue;
	queue<float> qFPS;
	int size;
	wchar_t charFPS[30];

	//���ڼ���֡���Ķ���
	float previousClock;
	float currentClock;
	float previousRenderTime;
public:
	fpsClass() {
		previousClock = currentClock = previousRenderTime = 0.0f;

		memset(charFPS, 0, sizeof(charFPS));
		sumOfqueue = 0.01f;
		size = 60;
	}

	void computeTime() {
		currentClock = (float)clock();
		push((currentClock - previousClock) / CLK_TCK);
		previousClock = currentClock;
	}

	void push(float gap) {
		if ((int)qFPS.size() > size) {
			sumOfqueue -= qFPS.front();
			qFPS.pop();
		}
		sumOfqueue += gap;
		qFPS.push(gap);
	}

	int getFPS() {
		return (int)((float)size / sumOfqueue);
	}

	wchar_t* getFPSInfo() {
		wsprintf(charFPS, TEXT("FPS : %3d"), getFPS());
		return charFPS;
	}
};

class RenderClass
{
private:
	//������
	CanvasClass *m_Canvas;
	//�������
	CameraClass *m_Camera;
	
	fpsClass fps;
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
	Object Triangle;

//��ǰ����
//�����õ��ļ����м�����
private:
	Matrix4 WorldToView;
	//ViewToHomo �����������
};

#endif