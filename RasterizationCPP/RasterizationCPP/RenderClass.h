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

class RenderClass
{
private:
	//������
	CanvasClass *m_Canvas;
	//�������
	CameraClass *m_Camera;
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