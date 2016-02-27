#ifndef RASTERIZER_RENDERCLASS_H
#define RASTERIZER_RENDERCLASS_H

#include "ProjectHeader.h"

class Camera;
class Object;

class Render
{
private:
	//��ǰ����ľ��
	HWND *m_ptr_hwnd;
	//��Ļ���豸������
	HDC m_hdc_screen;

	//��Ⱦ������
	HDC m_hdc_buffer;
	//���汳��ͼ���Ļ�ˢ
	HBRUSH m_brush_background;

	//�������
	Camera *m_ptr_camera;

//˽�к���
private:
	//ViewToHomo ���������������
	Matrix4 m_world_to_view;
	void m_DrawObjects();
public:
	Render();
	~Render();

	void Initialize(HWND*);
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