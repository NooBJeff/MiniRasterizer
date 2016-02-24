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
#include "CameraClass.h"
#include "ObjectClass.h"
#include "InputClass.h"

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
		push((currentClock - previousClock) / CLK_TCK);
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

class RenderClass
{
	////////////////
	// Debug �� //
	///////////////
//public:
	


private:
	//��ǰ����ľ��
	HWND *m_ptr_hwnd;
	//��Ļ���豸������
	HDC m_hdcScreen;
	//��Ⱦ����
	RECT *m_ptr_rectRenderArea;

	//��Ⱦ������
	HDC m_hdcBuffer;
	//���汳��ͼ���Ļ�ˢ
	HBRUSH m_brushBackground;


	//�������ָ��
	InputClass *m_ptr_Input;
	//ʱ����
	TimeClass fps;
	//�������
	CameraClass *m_Camera;

//˽�к���
private:
	//ViewToHomo ���������������
	Matrix4 WorldToView;
	void DrawObjects();
public:
	RenderClass(InputClass*);
	~RenderClass();

	void Initialize(RECT*,HWND*);
	void DeleteResources();
	void Shutdown();

	//��Ⱦһ֡
	void RenderAFrame();

	//�����ڴ�С�仯ʱ
	//�������û�����С�Լ���Ӧ��Դ
	void UpdateSettings();

	//////////////////////////////
	// Canvas Draw Functions //
	/////////////////////////////

	//ǰ��̨���潻��
	void SwapBufferToScreen();

	//��ջ���
	void ClearCanvas();

	//�������
	void OutputText(const wstring&, int linenumber);
	//������������
	void DrawTriangle(const Vector4[], COLORREF);
	//����
	void DrawLine(Vector2, Vector2, COLORREF);
	//���õ������ص���ɫ
	void DrawPixel(int, int, COLORREF);

//ģ������
public:
	vector<Object> RenderObjects;
};

#endif