#ifndef RASTERIZER_WINDOWFRAMECLASS_H
#define RASTERIZER_WINDOWFRAMECLASS_H

#define WIN32_LEAN_AND_MEAN
/*
��Ĺ��ܣ�
�������д��ڽ���ĳ���
*/

#include "ProjectHeader.h"
#include "InputClass.h"
#include "RenderClass.h"

class WindowFrameClass {
private:
	//������
	HWND m_hwnd;

	//��Ⱦ���򣨿ͻ�����ϵ��
	//Rendering area(in client coordinate)
	RECT m_rect_client;

	//�˳�����
	bool m_quit_software;
	//��������
	wchar_t *m_app_name;

//�õ�����
private:
	//��Ⱦ��
	RenderClass *m_renderer;

	//��¼��ǰ���µİ���
	InputClass *m_input;

public:
	WindowFrameClass();
	~WindowFrameClass();

	//��������Ϣ������
	LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	//Initialize parameters
	void Initialize(int,int);
	void Shutdown();

	//��ϵͳ��ע�ᴰ��
	int RegisterCreateWindow(HINSTANCE hInstance, HINSTANCE hPreinstance, LPSTR lpCmd, int nShowCmd);

	//��Ҫ�ĳ���ѭ��
	int Run();
};

//ƭWin����Ϣ������
LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static WindowFrameClass *AppHandler = NULL;

#endif