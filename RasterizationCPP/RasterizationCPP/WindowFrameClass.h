#ifndef RASTERIZER_WINDOWFRAMECLASS_H
#define RASTERIZER_WINDOWFRAMECLASS_H

#define WIN32_LEAN_AND_MEAN
/*
��Ĺ��ܣ�
�������д��ڽ���ĳ���
*/

#include "ProjectHeader.h"

class Render;
class SceneManager;
class Input;
class Time;

class WindowFrame {
public:	
	//������
	HWND m_hwnd;
	//��Ⱦ���򣨿ͻ�����ϵ��
	//Rendering area(in client coordinate)
	static RECT rect_client;

	///////////
	// FLAG //
	///////////
	//32 bit
	//16 ^ 8 == 2^32 == long
	//8 number each
	//0x00000000L
	static DWORD STYLE_CHECKER;
private:


	//�˳�����
	bool m_quit_software;
	//��������
	wchar_t *m_app_name;

	//��������
	//��Ⱦ��
	Render *m_ptr_renderer;
	//����������
	SceneManager *m_ptr_manager;
	//ʱ����
	Time *m_ptr_time;
	//��¼��ǰ���µİ���
	Input *m_ptr_input;

public:
	WindowFrame(DWORD checker =  RENDER_MODE_FILL);
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