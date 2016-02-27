#ifndef RASTERIZER_WINDOWFRAMECLASS_H
#define RASTERIZER_WINDOWFRAMECLASS_H

#define WIN32_LEAN_AND_MEAN
/*
��Ĺ��ܣ�
�������д��ڽ���ĳ���
*/

#include "ProjectHeader.h"

class Render;
class Input;
class Time;

class WindowFrame {
public:
	//��Ⱦ���򣨿ͻ�����ϵ��
	//Rendering area(in client coordinate)
	static RECT rect_client;
private:
	//������
	HWND m_hwnd;

	//�˳�����
	bool m_quit_software;
	//��������
	wchar_t *m_app_name;

//�õ�����
private:
	//��Ⱦ��
	Render *m_ptr_renderer;
	//ʱ����
	Time *m_ptr_time;
	//��¼��ǰ���µİ���
	Input *m_ptr_input;

public:
	WindowFrame();
	~WindowFrame();

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
static WindowFrame *AppHandler = NULL;

#endif