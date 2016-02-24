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
#include "TimeClass.h"

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