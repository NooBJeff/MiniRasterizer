#ifndef RASTERIZER_SCENEMANAGERCLASS_H
#define RASTERIZER_SCENEMANAGERCLASS_H

#include "ProjectHeader.h"
#include "ObjectClass.h"

//���泡����ʲô����
//�����λ�õȵ�
class SceneManager {
private:
	vector<Object> objects_all;
public:
	//���������б��Թ���Ⱦ
	vector<Object>& getObjectsForRendering();
};

#endif