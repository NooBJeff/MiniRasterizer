/*
������Ĺ�դ����Ⱦ������
��Ŀ��ʼʱ��
2016/1/3

--Jeff
*/

#include "WindowFrameClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreinstance, LPSTR lpCmd, int nShowCmd) {
	WindowFrame *mainWindow = new WindowFrame(RENDER_MODE_OUTLINE);

	//��ʼ��
	mainWindow->Initialize(800, 600);
	//ע�ᴰ��
	if (ERROR == mainWindow->RegisterCreateWindow(hInstance, hPreinstance, lpCmd, nShowCmd)) {
		return ERROR;
	}

	//������ѭ��
	mainWindow->Run();

	//�ر�
	mainWindow->Shutdown();

	//�ƺ���
	delete mainWindow;
	mainWindow = NULL;

	return OK;
}