/*
������Ĺ�դ����Ⱦ������
��Ŀ��ʼʱ��
2016/1/3

--Jeff
*/

#include "WindowFrameClass.h"

//������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreinstance, LPSTR lpCmd, int nShowCmd) {
	WindowFrameClass *mainWindow = new WindowFrameClass;

	//��ʼ��
	mainWindow->Initialize(800, 600);
	//ע�ᴰ��
	if (ERROR == mainWindow->RegisterCreateWindow(hInstance, hPreinstance, lpCmd, nShowCmd)) {
		return ERROR;
	}

	//������ѭ��
	mainWindow->Run();

	//�ر�
	mainWindow->ShutDown();

	//�ƺ���
	delete mainWindow;
	mainWindow = nullptr;

	return OK;
}