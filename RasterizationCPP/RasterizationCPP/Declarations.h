#ifndef RASTERIZER_DECLARATIONS_H
#define RASTERIZER_DECLARATIONS_H

/********************************
������Ŀ�����壺
����ϵ����������ϵ

�������궨�壺
x�᣺����
y�᣺����
z�᣺����Ļ��

��ת���궨�壺�������෴������ȥ��˳ʱ�뷽��Ϊ ��
x : Pitch
y : Yaw
z : Roll

���壺
�����ζ�����Ʒ���˳ʱ�� Ϊ�������ӵ�

��μ��ÿռ䣺
��Χ X,Y,Z ~ [-1, 1]
**********************/

/////////////
// Header //
/////////////
#include "resource.h"
#include <Windows.h>

#include "MathComplement.h"

/////////
//�궨��//
/////////

//�Ƕ�ת��
#define DEGREE(x) (0.01745f*(x))

//�����ֵ��Absolute��
#define ABS(x) (((x) >= 0)?(x):-(x))
//������Ϣ
//#define ERROR 0
#define OK 1

#endif