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
��Χ 
X,Y ~ [-1, 1]
Z ~ [0, 1]
**********************/


#ifndef RASTERIZER_PROJECTHEADER_H
#define RASTERIZER_PROJECTHEADER_H

//#define DEBUG
#define AFFLINE

/////////////////////
// System Header //
/////////////////////
#include "resource.h"
#include <Windows.h>
#include <assert.h>

///////////////////////////////
// STL and other Libraries //
///////////////////////////////
#include <array>
using std::array;
#include <queue>
using std::queue;
#include <vector>
using std::vector;

#include <string>
using std::wstring;
#include <sstream>
using std::wstringstream;
using std::endl;

#include <ctime>
using std::clock;
#include <cmath>
#include <memory>
using std::memset;

///////////////////
// User Header //
//////////////////
#include "Utility.h"


/////////////
// Macros //
/////////////

//�Ƕ�ת��
#define DEGREE(x) (0.01745f*(x))

//#define ERROR 0
#define OK 1

//Default Color
#define COLOR_BLACK (RGB(0, 0, 0))
#define COLOR_BLUE (RGB(0, 0, 255))
#define COLOR_RED (RGB(255, 0, 0))
#define COLOR_WHITE (RGB(255, 255, 255))


//////////
// Flag //
/////////
#define FRAGMENT_MASK 0x00000001
#define FRAGMENT_GOOD 0x00000000
#define FRAGMENT_DELETED 0x00000001

//32λ int
//��λ16��������ʾ
//x
#define RENDER_MODE_OUTLINE 0x00000000
#define RENDER_MODE_FILL 0x00000001
#define RENDER_MODE_MASK 0x00000001

#endif