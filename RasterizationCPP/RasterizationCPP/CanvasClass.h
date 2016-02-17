#ifndef RASTERIZER_CANVASCLASS_H
#define RASTERIZER_CANVASCLASS_H

/*
���������Ⱦ��ͼ����Ļ
*/

#include "ProjectHeader.h"

class CanvasClass
{
//˽������
private:
	//��Ļ�ľ��
	HDC m_hdcScreen;

	//��Ⱦ������
	HDC m_hdcBuffer;
	//���汳��ͼ���Ļ�ˢ
	HBRUSH m_brushBackground;

	//��Ⱦ����
	RECT m_rectRenderArea;

//����API
//��ǰ���ʼ�����йغ���
public:
	CanvasClass();
	~CanvasClass();

	//��ʼ��
	void Initialize(RECT,HDC);
	//�ر�
	void Shutdown();
	//����������Ļ��С�йص���Դȫɾ��
	void DeleteResources();

	//�����ڴ�С�仯ʱ
	//�������û�����С�Լ���Ӧ��Դ
	void UpdateSettings(RECT rectNew);

	//����Ⱦ�õ�ͼƬ��������Ļ��
	void SwapBufferToScreen();

	//��ջ���
	void ClearCanvas();

//���к���
//�����ڻ����Ͻ�����ʾ�ĺ���
public:
	//���һ���ַ���
	void OutputText(wstring,int line);
	//���õ������ص���ɫ
	void Draw(int, int, COLORREF);
};

#endif