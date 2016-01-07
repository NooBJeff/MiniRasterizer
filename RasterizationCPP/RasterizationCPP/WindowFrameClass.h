#ifndef RASTERIZER_WINDOWFRAMECLASS_H
#define RASTERIZER_WINDOWFRAMECLASS_H

#define WIN32_LEAN_AND_MEAN
/*
Class Function :
Create and display window
*/

#include <Windows.h>
#include "Declarations.h"
#include "RenderClass.h"
#include "InputClass.h"

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
	//������Ⱦ����
	RenderClass *m_Render;

	//��¼��ǰ���µİ���
	InputClass *m_Input;

public:
	WindowFrameClass();
	~WindowFrameClass();

	//��������Ϣ������
	LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	//Initialize parameters
	void Initialize(int,int);
	void ShutDown();

	//��ϵͳ��ע�ᴰ��
	int RegisterCreateWindow(HINSTANCE hInstance, HINSTANCE hPreinstance, LPSTR lpCmd, int nShowCmd);

	//��Ҫ�ĳ���ѭ��
	int Run();
};

//ƭWin����Ϣ������
LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static WindowFrameClass *AppHandler = nullptr;

#endif