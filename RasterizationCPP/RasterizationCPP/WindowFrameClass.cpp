#include "WindowFrameClass.h"

WindowFrameClass::WindowFrameClass() {
	m_rectRenderScreen.bottom = m_rectRenderScreen.left = m_rectRenderScreen.right = m_rectRenderScreen.top = 0;
	m_centerCursor = false;
	m_quitSoftware = false;
	m_AppName = TEXT("Reasterizer");

	AppHandler = this;
	m_Input = nullptr;
	m_Render = nullptr;
}

WindowFrameClass::~WindowFrameClass() {
	m_AppName = nullptr;
	delete m_Input;
	m_Input = nullptr;

	delete m_Render;
	m_Render = nullptr;
}

void WindowFrameClass::Initialize(int RENDER_X, int RENDER_Y) {
	//�趨��ʼ��Ⱦ����Ĵ�С
	m_rectRenderScreen.top = 0; m_rectRenderScreen.left = 0; m_rectRenderScreen.bottom = RENDER_Y; m_rectRenderScreen.right = RENDER_X;
	m_centerCursor = false;
	m_quitSoftware = false;
	m_Input = new InputClass;

	m_Render = new RenderClass();
}

void WindowFrameClass::ShutDown() {
	m_Render->ShutDown();
}

int WindowFrameClass::RegisterCreateWindow(HINSTANCE hInstance, HINSTANCE hPreinstance, LPSTR lpCmd, int nShowCmd) {
	int m_WINDOW_X = GetSystemMetrics(SM_CXSCREEN);
	int m_WINDOW_Y = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASSEX wnd = { 0 };
	wnd.cbClsExtra = 0;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = NULL;
	wnd.hIconSm = NULL;
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = CustomWinProc;
	wnd.lpszClassName = m_AppName;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_VREDRAW | CS_HREDRAW;

	//ע�ᴰ��
	RegisterClassEx(&wnd);
	//������ʾ����
	m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, m_AppName, m_AppName,
		WS_OVERLAPPEDWINDOW, (m_WINDOW_X - m_rectRenderScreen.right + m_rectRenderScreen.left) / 2, (m_WINDOW_Y - m_rectRenderScreen.bottom + m_rectRenderScreen.top) / 2,
		m_rectRenderScreen.right - m_rectRenderScreen.left, m_rectRenderScreen.bottom - m_rectRenderScreen.top, NULL, NULL, hInstance, NULL);

		if (!m_hWnd) {
			return ERROR;
		}

		//��ʾ����
		ShowWindow(m_hWnd, nShowCmd);
		UpdateWindow(m_hWnd);

		//����ʼ����
		m_Render->Initialize(m_rectRenderScreen, GetDC(m_hWnd));
		m_Input->Initialize(m_hWnd);
		return OK;
}

int WindowFrameClass::Run() {
	MSG msg;
	//�˳�����
	while(!m_quitSoftware) {
		while (1) {
			if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//����һ֡��Ⱦ
		m_Render->RenderAFrame();
	}
	return msg.message;
}

//��Ϣ������
LRESULT CALLBACK WindowFrameClass::WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
	case WM_SIZE:
		//ȡ������Ļ�Ĵ�С
		m_rectRenderScreen.right = LOWORD(lParam);
		m_rectRenderScreen.bottom = HIWORD(lParam);

		m_Render->UpdateSettings(m_rectRenderScreen);
		break;

	case WM_PAINT:
		m_Render->SwapBufferToScreen();
		break;

	case WM_KEYDOWN:
		m_Input->Press(wParam);
		m_Input->ReactToKeyPressed();
		break;
	case WM_KEYUP:
		m_Input->Release(wParam);
		break;

	//�رճ���
	case WM_CLOSE:
	case WM_DESTROY:
		m_quitSoftware = true;
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

//����
LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	return AppHandler->WinProc(hWnd, Msg, wParam, lParam);
}