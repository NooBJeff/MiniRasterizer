/*
Just Include this single file in every other header
and everything will be just fine !
*/

/************************
��Ŀͨ�ù����壺
����ϵ����������ϵ

�������궨�壺
x�᣺����
y�᣺����
z�᣺����Ļ��

��ת���궨�壺�������෴������ȥ��˳ʱ�뷽��Ϊ ��
x : Pitch
y : Yaw
z : Roll

�������Ԫ�أ�
�����ζ�����Ʒ���˳ʱ�� Ϊ���泯��

��μ��ÿռ䣺
��Χ X,Y,Z ~ [-1, 1]
**********************/


#ifndef RASTERIZER_PROJECTHEADER_H
#define RASTERIZER_PROJECTHEADER_H

/////////////////////
// System Header //
/////////////////////
#include "resource.h"
#include <Windows.h>

//////////////////////////////
// STL and other Libraries //
/////////////////////////////
#include <queue>
using std::queue;
#include <vector>
using std::vector;

#include <string>
using std::wstring;
#include <sstream>
using std::wstringstream;

#include <ctime>
using std::clock;
#include <cmath>
#include <memory>
using std::memset;

///////////////////
// User Header //
//////////////////
#include "MathComplement.h"


/////////////
// Macros //
/////////////

//�Ƕ�ת��
#define DEGREE(x) (0.01745f*(x))

//�����ֵ��Absolute��
#define ABS(x) (((x) >= 0)?(x):-(x))

//#define ERROR 0
#define OK 1
#endif