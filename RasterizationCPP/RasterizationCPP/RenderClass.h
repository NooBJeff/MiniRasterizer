#ifndef RASTERIZER_RENDERCLASS_H
#define RASTERIZER_RENDERCLASS_H

/*
���������Ⱦ��ͼ����Ļ
*/

#include <Windows.h>
#include "Declarations.h"

class RenderClass
{
private:
	//��Ļ��
	HDC m_hdcScreen;
	//��Ⱦ������
	HDC m_hdcBuffer;
	//��Ⱦ����
	RECT m_rectRenderArea;

	//���汳��ͼ����λͼ
	HBITMAP m_bmpBackgroundImage;
	//���汳��ͼ���Ļ�ˢ
	HBRUSH m_brushBackgroundImage;
public:
	RenderClass();
	RenderClass(RECT);
	~RenderClass();

	//��ʼ��
	void Initialize(RECT,HDC);

	void ShutDown();

	//����������Ļ��С�йص���Դȫɾ��
	void DeleteResources();

	//�����ڴ�С�仯ʱ
	//�������û�����С֮��
	void UpdateSettings(RECT rectNew);
	void UpdateSettings(int rectRight, int rectBottom);

	//��Ⱦ��ͼ��
	void RenderAFrame();

	//����Ⱦ�õ�ͼƬ��������Ļ��
	inline void SwapBufferToScreen();

//�ظ��Ĺ���������
private:
	void m_UpdateSettings();
};

#endif