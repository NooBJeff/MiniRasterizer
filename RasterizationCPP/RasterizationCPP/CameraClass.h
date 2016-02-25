#ifndef RASTERIZER_CAMERACLASS_H
#define RASTERIZER_CAMERACLASS_H

#include "ProjectHeader.h"
#include "InputClass.h"
#include "TimeClass.h"

class CameraClass {
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
	TimeClass *m_ptr_time;
	InputClass *m_ptr_Input;
	//���������ת������μ��ʿռ�����
	//������������Ա仯ʱ��������
	//������λ�ú���ת�ı仯
	void m_UpdateViewToHomoMatrix4();
public:
	//��������߿��
	CameraClass(float aspect, float fov, InputClass *, TimeClass*);
	~CameraClass();

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