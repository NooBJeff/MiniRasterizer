#include "MathComplement.h"

/*
FLOAT3D
*/
Vector3 Vector3::CrossProduct(Vector3 b)
{
	Vector3 output;
	output.x = y*b.z - z*b.y;
	output.y = z*b.x - x*b.z;
	output.z = x*b.y - y*b.x;
	return output;
}

float Vector3::DotProduct(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}

Vector3 Vector3::operator*(const Matrix3 b)
{
	return Vector3(
		x*b.var[0][0] + y*b.var[1][0] + z*b.var[2][0],
		x*b.var[0][1] + y*b.var[1][1] + z*b.var[2][1],
		x*b.var[0][2] + y*b.var[1][2] + z*b.var[2][2]);
}

Vector3 Vector3::operator+(const Vector3 b)
{
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(const Vector3 b)
{
	return Vector3(x - b.x, y - b.y, z - b.z);
}


/*
MARTIX
3 x 3
*/
Matrix3::Matrix3() {
	memset(var, 0, 3 * 3 * sizeof(float));
}

Matrix3::Matrix3(const Matrix3 &old)
{
	memcpy(var, old.var, 3 * 3 * sizeof(float));
}

void Matrix3::SetZero()
{
	memset(var, 0, 3 * 3 * sizeof(float));
}

Matrix3 Matrix3::operator*(const Matrix3 &b)
{
	Matrix3 martix;
	for (int lop = 0; lop < 3; lop++)
	{
		for (int lop2 = 0; lop2 < 3; lop2++)
		{
			martix.var[lop][lop2] =
				(var[lop][0] * b.var[0][lop2]) +
				(var[lop][1] * b.var[1][lop2]) +
				(var[lop][2] * b.var[2][lop2]);
		}
	}
	return martix;
}

Matrix3 Matrix3::operator*(const float &multi)
{
	Matrix3 tmp = *this;
	tmp.var[0][0] *= multi;
	tmp.var[1][1] *= multi;
	tmp.var[2][2] *= multi;

	return tmp;
}

Matrix4::Matrix4()
{
	memset(var, 0, 4 * 4 * sizeof(float));
}

Matrix4::Matrix4(float input)
{
	memset(var, 0, 4 * 4 * sizeof(float));
	var[0][0] = var[1][1] = var[2][2] = var[3][3] = input;
}

Matrix4::Matrix4(const Matrix4 &old)
{
	memcpy(var, old.var, 4 * 4 * sizeof(float));
}

void Matrix4::SetZero()
{
	memset(var, 0, 4 * 4 * sizeof(float));
}

float Matrix4::Determinant(Matrix3 &input)
{
	return
		(input.var[0][0] * input.var[1][1] * input.var[2][2]) +
		(input.var[0][1] * input.var[1][2] * input.var[2][0]) +
		(input.var[0][2] * input.var[1][0] * input.var[2][1]) -
		(input.var[0][2] * input.var[1][1] * input.var[2][0]) -
		(input.var[0][1] * input.var[1][0] * input.var[2][2]) -
		(input.var[0][0] * input.var[1][2] * input.var[2][1]);
}

void Matrix4::Invert()
{
	Matrix4 output;
	//���ڴ���ÿ�ε�����ʽ
	Matrix3 tmp;

	float firstPart ;
	//�����ĸ������
	firstPart =
	(var[0][0] * var[1][1] * var[2][2] * var[3][3]) +
	(var[0][1] * var[1][2] * var[2][3] * var[3][0]) +
	(var[0][2] * var[1][3] * var[2][0] * var[3][1]) +
	(var[0][3] * var[1][0] * var[2][1] * var[3][2]) -
	(var[0][3] * var[1][2] * var[2][1] * var[3][0]) -
	(var[0][2] * var[1][1] * var[2][0] * var[3][3]) -
	(var[0][1] * var[1][0] * var[2][3] * var[3][2]) -
	(var[0][0] * var[1][3] * var[2][2] * var[3][1]);

	//��
	firstPart = 1 / firstPart;


	//������ѭ��
	int x, y;
	//���ڱ�ʶ����ʽ��x y
	int x_tmp, y_tmp;

	for (int lop = 0; lop < 4; lop++)
	{
		for (int lop2 = 0; lop2 < 4; lop2++)
		{
			tmp.SetZero();
			x_tmp = 0;
			y_tmp = 0;
			//Ϊoutput�����Ԫ����ֵ
			for (x = 0; x < 4; x++)
			{
				y_tmp = 0;
				if (x == lop)
				{
					continue;
				}
				for (y = 0; y < 4; y++)
				{
					if (y == lop2)
					{
						continue;
					}
					tmp.var[x_tmp][y_tmp++] = var[x][y];
				}
				x_tmp++;
			}

			output.var[lop2][lop] = Determinant(tmp);

			//��-1
			if ((lop + 1 + lop2 + 1) % 2)
			{
				output.var[lop2][lop] = (-1.0f)*output.var[lop2][lop];
			}
			//output.var[lop2][lop] *= firstPart;
		}
	}
	output = output * firstPart;
	*this = output;
}

Matrix4 Matrix4::operator*(const Matrix4 &b)
{
	Matrix4 martix;
	for (int lop = 0; lop < 4; lop++)
	{
		for (int lop2 = 0; lop2 < 4; lop2++)
		{
			martix.var[lop][lop2] =
				(var[lop][0] * b.var[0][lop2]) +
				(var[lop][1] * b.var[1][lop2]) +
				(var[lop][2] * b.var[2][lop2]) +
				(var[lop][3] * b.var[3][lop2]);
		}
	}
	return martix;
}

Matrix4 Matrix4::operator*(const float &multi)
{
	Matrix4 tmp = *this;
	tmp.var[0][0] *= multi;
	tmp.var[1][1] *= multi;
	tmp.var[2][2] *= multi;
	tmp.var[3][3] *= multi;
	return tmp;
}