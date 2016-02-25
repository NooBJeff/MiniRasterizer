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
private:
	//��ǰ����ľ��
	HWND *m_ptr_hwnd;
	//��Ļ���豸������
	HDC m_hdc_screen;
	//��Ⱦ����
	RECT *m_ptr_rect_client;

	//��Ⱦ������
	HDC m_hdc_buffer;
	//���汳��ͼ���Ļ�ˢ
	HBRUSH m_brush_background;


	//�������ָ��
	InputClass *m_ptr_input;
	//ʱ����
	TimeClass m_time;
	//�������
	CameraClass *m_camera;

//˽�к���
private:
	//ViewToHomo ���������������
	Matrix4 m_world_to_view;
	void m_DrawObjects();
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
	void DrawTriangle(const Vector4 p0, const Vector4 p1, const Vector4 p2, COLORREF);
	//����
	void DrawLine(Vector2, Vector2, COLORREF);
	//���õ������ص���ɫ
	void DrawPixel(int, int, COLORREF);

//ģ������
public:
	vector<Object> vector_objects;
};

#endif