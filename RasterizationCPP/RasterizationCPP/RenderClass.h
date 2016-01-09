#ifndef RASTERIZER_RENDERCLASS_H
#define RASTERIZER_RENDERCLASS_H

/*
���������Ⱦ��ͼ����Ļ
*/

#include <Windows.h>
#include "Declarations.h"


class RenderClass
{
//˽������
private:
	//��Ļ��
	HDC m_hdcScreen;
	//��Ⱦ������
	HDC m_hdcBuffer;
	//��Ⱦ����
	RECT m_rectRenderArea;

	//���汳��ͼ����λͼ
	HBITMAP m_bmpBackgroundImage;

//˽�к���
//�ظ��Ĺ���������
private:
	void m_UpdateSettings();

//����API
//��ǰ���ʼ�����йغ���
public:
	RenderClass();
	RenderClass(RECT);
	~RenderClass();

	//��ʼ��
	void Initialize(RECT,HDC);
	//�ر�
	void ShutDown();

	//����������Ļ��С�йص���Դȫɾ��
	void DeleteResources();

	//�����ڴ�С�仯ʱ
	//�������û�����С�Լ���Ӧ��Դ
	void UpdateSettings(RECT rectNew);
	void UpdateSettings(int rectRight, int rectBottom);

	//��Ⱦһ֡
	void RenderAFrame();

	//����Ⱦ�õ�ͼƬ��������Ļ��
	inline void SwapBufferToScreen();

//���к���
//�������
public:
	inline void OutputText(wchar_t[]);
};

#endif