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

#include "Declarations.h"
#include "MathCollection.h"
#include "CanvasClass.h"

class RenderClass
{
private:
	//������
	CanvasClass *m_Canvas;

public:
	RenderClass();
	~RenderClass();

	void Initialize(RECT,HDC);
	void Shutdown();

	//���Ļ����������
	void UpdateCanvasSettings(RECT newRect);

	//��Ⱦһ֡
	void RenderAFrame();
};

#endif