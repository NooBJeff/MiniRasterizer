#ifndef RASTERIZER_TIMECLASS_H
#define RASTERIZER_TIMECLASS_H

#include "ProjectHeader.h"

class TimeClass {
private:
	float m_sum_of_queue;
	queue<float> m_queue_delta_time;
	int m_queue_size;
	wstring m_fps_info;

	//���ڼ���֡���Ķ���
	float m_previous_clock;
	float m_current_clock;
	//�ϴ���Ⱦһ֡���ȥ��ʱ��
	float m_delta_time;

private:
	void m_Push(float gap) {
		m_sum_of_queue -= m_queue_delta_time.front();
		m_queue_delta_time.pop();
		m_sum_of_queue += gap;
		m_queue_delta_time.push(gap);
	}

public:
	TimeClass() {
		m_previous_clock = m_current_clock = 0.0f;
		m_delta_time = 1.0f / 60;
		m_queue_size = 60;

		m_sum_of_queue = m_queue_size * m_delta_time;
		for (int lop = 0; lop < m_queue_size; lop++) {
			m_queue_delta_time.push(m_delta_time);
		}
	}

	float GetDeltaTime() {
		return m_delta_time;
	}

	//����ÿ֡�ĺ�ʱ
	void ComputeTime() {
		m_current_clock = (float)clock();
		m_delta_time = (m_current_clock - m_previous_clock) / CLK_TCK;
		m_Push(m_delta_time);
		m_previous_clock = m_current_clock;
	}

	//��õ�ǰ��֡��
	float GetFPS() {
		return ((float)m_queue_size / m_sum_of_queue);
	}

	//���֡�����ַ�����Ϣ
	wstring GetFPSwstring() {
		m_fps_info.clear();

		wstringstream ws;
		ws << TEXT("FPS : ") << GetFPS();
		m_fps_info = ws.str();
		return m_fps_info;
	}
};

#endif