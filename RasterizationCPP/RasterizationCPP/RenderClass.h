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
#include <vector>
using std::vector;

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
		previousClock = currentClock = 0.0f;
		previousRenderTime = 1.0f / 60;
		size = 60;

		memset(charFPS, 0, sizeof(charFPS));
		sumOfqueue = size * previousRenderTime;
		for (int lop = 0; lop < size; lop++) {
			qFPS.push(previousRenderTime);
		}
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

	//��ǰ����
	//�����õ��ļ����м�����
private:
	Matrix4 WorldToView;
	//ViewToHomo �����������
	//todo
	Vector4 SingleVertexFromLocalToHomo(Vector3 vertex, Vector3 rotation, Vector3 transition);
	void DrawObjects();
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