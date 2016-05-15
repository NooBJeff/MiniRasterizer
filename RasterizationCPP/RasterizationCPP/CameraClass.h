#ifndef RASTERIZER_CAMERACLASS_H
#define RASTERIZER_CAMERACLASS_H

#include "ProjectHeader.h"

class Camera {
//�������ݳ�Ա
public:
	//����
	Vector3 position;

	//�Ƹ�������ת�ĽǶ�
	//x -> pitch
	//y -> yaw
	//z -> roll
	Vector3 rotation;

	//����ľ��룬��Զ��ʾ�ľ���
	float near_z, far_z;
	//Field of View
	float fov;

	//��Ļ�߿��
	//���ݻ����ֱ�������
	float screen_aspect;

	//������ƶ��ٶ�
	float move_speed;
	float rotate_speed;

	//������ǰ�����
	//���ܸ߿�� �� FOV ��Ӱ��
	Matrix4 view_to_homo;
private:
	//���������ת������μ��ÿռ�����
	//������������Ա仯ʱ��������
	void m_UpdateViewToHomoMatrix4();
public:
	//���캯����������߿��
	Camera(float aspect, float fov);
	~Camera();

	//��������
	//0������
	void Update(float aspect, float fov);
	void Update();

	void CameraControl();
	//��������ת�������������
	//���ӿ�����
	Matrix4 GetWorldToViewMatrix4();
};

#endif