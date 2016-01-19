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
	HWND m_hWnd;

	//��Ⱦ���򣨿ͻ�����ϵ��
	//Rendering area(in client coordinate)
	RECT m_rectRenderScreen;

	//��������ʾ
	bool m_centerCursor;
	//�˳�����
	bool m_quitSoftware;
	//��������
	wchar_t *m_AppName;

//�õ�����
private:
	//��Ⱦ��
	RenderClass *m_MainRenderer;

	//��¼��ǰ���µİ���
	InputClass *m_Input;

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