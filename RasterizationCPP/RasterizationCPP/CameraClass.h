#ifndef RASTERIZER_CAMERACLASS_H
#define RASTERIZER_CAMERACLASS_H

#include "ProjectHeader.h"
#include "InputClass.h"

class CameraClass {
//�������ݳ�Ա
public:
	//����
	Vector3 Position;

	Vector3 Rotation;
	//x -> pitch
	//y -> yaw
	//z -> roll

	//����ľ��룬��Զ��ʾ�ľ���
	float NearZ, FarZ;
	//Field of View
	float FOV;

	//��Ļ�߿��
	//���ݻ����ֱ�������
	float screenAspect;

	//������ƶ��ٶ�
	float moveSpeed;
	float rotateSpeed;

	//������ǰ�����
	//���ܸ߿�� �� FOV ��Ӱ��
	Matrix4 ViewToHomo;
private:
	InputClass *m_ptr_Input;
	//���������ת������μ��ʿռ�����
	//������������Ա仯ʱ��������
	//������λ�ú���ת�ı仯
	void GetViewToHomoMatrix4();
public:
	//��������߿��
	CameraClass(float aspect, float fov, InputClass *);
	~CameraClass();

	//��������
	//0������
	void Update(float newAspect, float newFOV);
	void Update();

	void CameraControl();
	//��������ת�������������
	//���ӿ�����
	Matrix4 GetWorldToViewMatrix4();
};

#endif