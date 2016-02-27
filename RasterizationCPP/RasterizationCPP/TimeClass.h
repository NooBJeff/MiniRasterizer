#ifndef RASTERIZER_TIMECLASS_H
#define RASTERIZER_TIMECLASS_H

#include "ProjectHeader.h"

class Time {
private:
	queue<float> m_queue_delta_time;

	//���ڼ���֡���Ķ���
	float m_previous_clock;
	float m_current_clock;

	///////////
	// static //
	//////////
	static wstring m_fps_info;
	//�ϴ���Ⱦһ֡���ȥ��ʱ��
	static float m_delta_time;
	static int m_queue_size;
	static float m_sum_of_queue;

private:
	void m_Push(float gap);

public:
	Time();

	//����ÿ֡�ĺ�ʱ
	void ComputeTime();

	static float GetDeltaTime();

	//���֡�����ַ�����Ϣ
	static wstring GetFPSwstring();
};

#endif