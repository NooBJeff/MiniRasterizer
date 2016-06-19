#ifndef RASTERIZER_MODELINFO_H
#define RASTERIZER_MODELINFO_H

#include "ProjectHeader.h"

//���ģ����Ϣ
class ModelInfo {
public:
	//����� x y z
	vector<Vector3> vertices;
	//����� UV
	vector<Vector2<float>> uv;
	//ÿ������ x -> ����, y -> UV
	vector<Vector2<int>> indices;

	//����
	HDC hdc_texture;

public:
	ModelInfo() {};
	~ModelInfo() {};

	int LoadModel(const char *fileName, LPCWSTR texturename);
};

#endif