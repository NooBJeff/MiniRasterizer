#include "RenderClass.h"



RenderClass::RenderClass() {
	m_Canvas = NULL;
}


RenderClass::~RenderClass() {
	m_Canvas = NULL;
}

void RenderClass::Initialize(RECT rectWindow,HDC hdcScreen) {
	m_Canvas = new CanvasClass();
	m_Canvas->Initialize(rectWindow, hdcScreen);
}

void RenderClass::Shutdown() {
	m_Canvas->Shutdown();
	delete m_Canvas;
	m_Canvas = NULL;
}

void RenderClass::UpdateCanvasSettings(RECT newRect) {
	m_Canvas->UpdateSettings(newRect);
}

void RenderClass::RenderAFrame() {
	m_Canvas->ClearCanvas();
	//TODO
	//���������Ϣ
	m_Canvas->OutputText(L"Debug Infomation Here", 0);




	//����̨���潻������Ļ
	m_Canvas->SwapBufferToScreen();
}