#include "RenderClass.h"

#include "CameraClass.h"
#include "TimeClass.h"
#include "ObjectClass.h"
#include "WindowFrameClass.h"

void Render::m_DrawObjects() {
	if (vector_objects.size() == 0) {
		return;
	}
	m_world_to_view = m_ptr_camera->GetWorldToViewMatrix4();
	Matrix4 LocalToView;
	for (auto object : vector_objects) {
		if ((int)object.vertices.size() == 0) {
			continue;
		}
		vector<Vector4> transformed_vertices;

		LocalToView = Matrix4(1.0f) * Matrix4('A', object.rotation) * Matrix4(object.position);
		LocalToView = LocalToView * m_world_to_view;

		for (int lop = 0; lop < (int)object.vertices.size(); lop++) {
			//Local To View transformation
			transformed_vertices.push_back(object.vertices[lop] * LocalToView);

			//View To Homo transformation
			transformed_vertices[lop] = transformed_vertices[lop] * m_ptr_camera->view_to_homo;

			//Perspective Divison
			float z_depth = ABS(transformed_vertices[lop].w);
			transformed_vertices[lop].x /= z_depth;
			transformed_vertices[lop].y /= z_depth;
			transformed_vertices[lop].z /= z_depth;
		}

		//Clipping
		vector<Vector2<int>> tmp_indices;
		Clipping(tmp_indices, transformed_vertices, object.indices);

		if ((WindowFrame::STYLE_CHECKER & RENDER_MODE_MASK) == RENDER_MODE_OUTLINE) {
			DrawTriangles(transformed_vertices, tmp_indices);
		}
		else {
			FillTriangles(transformed_vertices, object.uv, tmp_indices, object.hdc_texture);
		}
	}
}

Render::Render() {
	m_ptr_camera = nullptr;
	m_z_depth_buffer = nullptr;
}

Render::~Render() {
	Shutdown();
}

void Render::Initialize(HWND *hWndScreen) {
	m_ptr_hwnd = hWndScreen;

	m_hdc_screen = GetDC(*m_ptr_hwnd);

	m_ptr_camera = new Camera((float)(WindowFrame::rect_client.right / WindowFrame::rect_client.bottom), 70.0f);
	m_ptr_camera->position.z = -70.f;
	m_ptr_camera->Update();

	//��ʼ������
	vector_objects.push_back(Object());
	if (vector_objects[0].Initial("Resources\\Models\\plane.obj", TEXT("Resources\\Materials\\CheckerboardTexture.bmp")) == ERROR) {
		vector_objects.erase(vector_objects.end() - 1);
	}
	vector_objects[0].rotation = Vector3(0, 180.f, 0);
}

void Render::DeleteResources() {
	DeleteDC(m_hdc_buffer);
	DeleteObject(m_brush_background);
}

void Render::Shutdown() {
	DeleteResources();
	if (m_ptr_camera) {
		delete m_ptr_camera;
		m_ptr_camera = nullptr;
	}
	if (m_z_depth_buffer) {
		delete m_z_depth_buffer;
		m_z_depth_buffer = nullptr;
	}
}

void Render::RenderAFrame() {
	////////////////
	// >ÿ֡���� //
	////////////////
	m_ptr_camera->CameraControl();
	m_DrawObjects();
	////////////////
	// <ÿ֡���� //
	////////////////


	OutputText(Time::GetFPSwstring(), 0);

	wstringstream ws;
	ws <<"Resolution : " << WindowFrame::rect_client.right << " * " << WindowFrame::rect_client.bottom;
	OutputText(ws.str(), 1);

	ws.str(L"");
	ws << m_ptr_camera->position << m_ptr_camera->rotation;
	OutputText(ws.str(), 2);

	////////////////
	// >ÿ֡���� //
	////////////////
	SwapBufferToScreen();
	ClearCanvas();
	////////////////
	// <ÿ֡���� //
	////////////////
}

void Render::UpdateSettings()
{
	//�ı�z����Ĵ�С
	if (m_z_depth_buffer) {
		delete m_z_depth_buffer;
		m_z_depth_buffer = nullptr;
	}

	m_z_depth_buffer = new float[WindowFrame::rect_client.right  * WindowFrame::rect_client.bottom];

	//��Ϊ��ʱɾ��ԭ������
	if (m_hdc_buffer) {
		DeleteResources();
	}
	//��ʱ��bufferû�д�С
	m_hdc_buffer = CreateCompatibleDC(m_hdc_screen);

	//���뱾�ر���ͼƬ
	HBITMAP bmpBackgroundImage = (HBITMAP)LoadImage(NULL, NULL/*TEXT("Resources\\Materials\\Background.bmp")*/, IMAGE_BITMAP,
		WindowFrame::rect_client.right, WindowFrame::rect_client.bottom, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//�������ʧ��
	//������ɫ����
	if (bmpBackgroundImage == NULL) {
		bmpBackgroundImage = CreateCompatibleBitmap(m_hdc_screen, WindowFrame::rect_client.right, WindowFrame::rect_client.bottom);

		SelectObject(m_hdc_buffer, bmpBackgroundImage);
		FillRect(m_hdc_buffer, &WindowFrame::rect_client, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}
	else {
		//ѡ������
		SelectObject(m_hdc_buffer, bmpBackgroundImage);
	}
	//���ݲ�����ͼ��������ˢ
	m_brush_background = CreatePatternBrush(bmpBackgroundImage);
	//֮�� bmp �Ϳ���ɾ��
	//�Ժ��û�ˢ������
	DeleteObject(bmpBackgroundImage);
	//���ģʽ��Ϊ͸��
	SetBkMode(m_hdc_buffer, TRANSPARENT);

	//���������������
	m_ptr_camera->Update((float)WindowFrame::rect_client.right / (float)WindowFrame::rect_client.bottom, m_ptr_camera->fov);
}

void Render::SwapBufferToScreen() {
	//BitBlt(m_hdc_screen, 0, 0, WindowFrame::rect_client.right, WindowFrame::rect_client.bottom, vector_objects[0].hdc_texture, 0, 0, SRCCOPY);
	BitBlt(m_hdc_screen, 0, 0, WindowFrame::rect_client.right, WindowFrame::rect_client.bottom, m_hdc_buffer, 0, 0, SRCCOPY);
}

void Render::ClearCanvas() {
	std::fill(m_z_depth_buffer, m_z_depth_buffer + WindowFrame::rect_client.right  * WindowFrame::rect_client.bottom, -1.0f);
	//�ñ�����ˢ��䱳��
	FillRect(m_hdc_buffer, &WindowFrame::rect_client, m_brush_background);
}

inline void Render::OutputText(const wstring & text, int line) {
	TextOut(m_hdc_buffer, 0, 20 * line, text.data(), text.size());
}

///////////////////
// Fill Triangles //
///////////////////
void Render::FillTriangles(vector<Vector4>& vertices,vector<Vector2<float>>& UVs, vector<Vector2<int>>& indices, HDC texture)
{
	for (int lop = 0; lop < (int)indices.size(); lop += 3) {
		//һ�������ε���������
		Vector4 a = vertices[indices[lop].x];
		Vector4 b = vertices[indices[lop + 1].x];
		Vector4 c = vertices[indices[lop + 2].x];

		if (TriangleBackcull(a, b, c)) {
			continue;
		}

		//һ�����������������uv
		Vector2<float> uv_a = UVs[indices[lop].y];
		Vector2<float> uv_b = UVs[indices[lop + 1].y];
		Vector2<float> uv_c = UVs[indices[lop + 2].y];

		uv_a.x = uv_a.x * 512.0f;
		uv_a.y = uv_a.y * 512.0f;

		uv_b.x = uv_b.x * 512.0f;
		uv_b.y = uv_b.y * 512.0f;

		uv_c.x = uv_c.x * 512.0f;
		uv_c.y = uv_c.y * 512.0f;

		//�����������㰴�մ��ϵ���ABC��˳����������
		//A��������
		if (a.y > b.y && a.y > c.y) {
			if (b.y < c.y) {
				swap<Vector4>(b, c);
				swap<Vector2<float>>(uv_b, uv_c);
			}
		}
		else if (b.y > a.y && b.y > c.y) {
			//B ������
			//A B ����
			swap<Vector4>(a, b);
			swap<Vector2<float>>(uv_a, uv_b);
			if (b.y < c.y) {
				swap<Vector4>(b, c);
				swap<Vector2<float>>(uv_b, uv_c);
			}
		}
		else if (c.y > a.y && c.y > b.y) {
			//C ������
			//A C ����
			swap<Vector4>(a, c);
			swap<Vector2<float>>(uv_a, uv_c);
			if (b.y < c.y) {
				swap<Vector4>(b, c);
				swap<Vector2<float>>(uv_b, uv_c);
			}
		}

		Vector4 d;
		Vector2<float> uv_d;

		float t_BYAYCYAY = (b.y - a.y) / (c.y - a.y);
		d.x = t_BYAYCYAY * (c.x - a.x) + a.x;
		d.y = b.y;
		d.z = t_BYAYCYAY * (c.z - a.z) + a.z;
		d.w = 1 / (t_BYAYCYAY * (1 / c.w - 1 / a.w) + 1 / a.w);

		float oneoverz = t_BYAYCYAY * (1 / c.w - 1 / a.w) + 1 / a.w;
		float uvoverz = t_BYAYCYAY * (uv_c.x / c.w - uv_a.x / a.w) + uv_a.x / a.w;
		uv_d.x = uvoverz / oneoverz;
		uvoverz = t_BYAYCYAY * (uv_c.y / c.w - uv_a.y / a.w) + uv_a.y / a.w;
		uv_d.y = uvoverz / oneoverz;

		//����μ��ÿռ�ĵ�ת�����ӿڿռ�
		HomoToScreenCoord(a);
		HomoToScreenCoord(b);
		HomoToScreenCoord(c);
		HomoToScreenCoord(d);

		//����¸�������D����B�����
		if (d.x < b.x)
		{
			FillTriangleTopFlat(d, uv_d, b, uv_b, c, uv_c, texture);
			FillTriangleBottomFlat(a, uv_a, b, uv_b, d, uv_d, texture);
		}
		else {
			FillTriangleTopFlat(b, uv_b, d, uv_d, c, uv_c, texture);
			FillTriangleBottomFlat(a, uv_a, d, uv_d, b, uv_b, texture);
		}
	}
}

void Render::FillTriangleTopFlat(Vector4 a, Vector2<float> uv_a, Vector4 b, Vector2<float> uv_b, Vector4 c, Vector2<float> uv_c, HDC texture) {
	const float &x1 = a.x;
	const float &x2 = b.x;
	const float &x3 = c.x;

	const float &y1 = a.y;
	const float &y2 = b.y;
	const float &y3 = c.y;

	//ȷ�������εķ�Χ
	int miny = (int)y3;
	int maxy = (int)y1;

	//���������UV����
	//��Χ [0, 512]
	int u, v;
	//x����������
	float xLeft, xRight;


	//͸����ȷ�Ĳ�ֵ����
	float oneoverz_Left, oneoverz_Right;
	float oneoverz_Top, oneoverz_Bottom;
	float oneoverz, oneoverz_Step;
	//UV �� 1/z
	float uoverz_Top, uoverz_Bottom;
	float uoverz_Left, uoverz_Right;
	float voverz_Top, voverz_Bottom;
	float voverz_Left, voverz_Right;

	float uoverz, uoverz_Step;
	float voverz, voverz_Step;


	//(y - y1) / (y3 - y1)
	float t_YAYCYAY;
	// (y - y2) / (y3 - y2)
	float t_YBYCYBY;

	//˫��ѭ��
	for (int y = miny; y <= maxy; y++)
	{
		//������õ��������������
		t_YAYCYAY = (y - y1) / (y3 - y1);
		t_YBYCYBY = (y - y2) / (y3 - y2);

		xLeft = t_YAYCYAY * (x3 - x1) + x1;
		xRight = t_YBYCYBY* (x3 - x2) + x2;

		//͸����ȷ�Ĳ�ֵ ֵ�ļ���
		//1 / z
		oneoverz_Top = 1 / a.w;
		oneoverz_Bottom = 1 / c.w;
		oneoverz_Left = t_YAYCYAY* (oneoverz_Bottom - oneoverz_Top) + oneoverz_Top;
		oneoverz_Top = 1 / b.w;
		oneoverz_Right = t_YBYCYBY * (oneoverz_Bottom - oneoverz_Top) + oneoverz_Top;
		oneoverz_Step = (oneoverz_Right - oneoverz_Left) / (xRight - xLeft);
		//U / z
		uoverz_Top = uv_a.x / a.w;
		uoverz_Bottom = uv_c.x / c.w;
		uoverz_Left = t_YAYCYAY* (uoverz_Bottom - uoverz_Top) + uoverz_Top;
		uoverz_Top = uv_b.x / b.w;
		uoverz_Right = t_YBYCYBY* (uoverz_Bottom - uoverz_Top) + uoverz_Top;
		uoverz_Step = (uoverz_Right - uoverz_Left) / (xRight - xLeft);
		//V / z
		voverz_Top = uv_a.y / a.w;
		voverz_Bottom = uv_c.y / c.w;
		voverz_Left = t_YAYCYAY * (voverz_Bottom - voverz_Top) + voverz_Top;
		voverz_Top = uv_b.y / b.w;
		voverz_Right = t_YBYCYBY* (voverz_Bottom - voverz_Top) + voverz_Top;
		voverz_Step = (voverz_Right - voverz_Left) / (xRight - xLeft);


		int x = 0;
		for (x = (int)xLeft, oneoverz = oneoverz_Left, uoverz = uoverz_Left, voverz = voverz_Left; x <= xRight; x++, oneoverz += oneoverz_Step, uoverz += uoverz_Step, voverz += voverz_Step) {
			u = (int)(uoverz / oneoverz);
			v = (int)(voverz / oneoverz);

			int _x = x;
			int _y = WindowFrame::rect_client.bottom - y;
			int _index = (_y - 1) * WindowFrame::rect_client.right + x;

			//û�г����������ķ�Χ
			if (_index < WindowFrame::rect_client.right * WindowFrame::rect_client.bottom && _index >= 0) {
				float &_z = m_z_depth_buffer[_index];
				if (oneoverz > _z) {
#ifdef DEBUG
					//debug
					assert(u != 512);
					assert(v != 512);
#endif
					DrawPixel(_x, _y, GetPixel(texture, u, v));
					_z = oneoverz;
				}
			}
		}
	}
}

void Render::FillTriangleBottomFlat(Vector4 a, Vector2<float> uv_a, Vector4 b, Vector2<float> uv_b, Vector4 c, Vector2<float> uv_c, HDC texture) {
	const float &x1 = a.x;
	const float &x2 = b.x;
	const float &x3 = c.x;

	const float &y1 = a.y;
	const float &y2 = b.y;
	const float &y3 = c.y;

	//ȷ�������εķ�Χ
	int miny = (int)y2;
	int maxy = (int)y1;

	//����ֱ�Ӵ���������������UV����
	int u, v;
	//��������� x ��Χ
	float xLeft, xRight;

	//͸����ȷ�Ĳ�ֵ
	float oneoverz_Left, oneoverz_Right;
	float oneoverz_Top, oneoverz_Bottom;
	float oneoverz, oneoverz_Step;
	//UV �� 1/z
	float uoverz_Top, uoverz_Bottom;
	float uoverz_Left, uoverz_Right;
	float voverz_Top, voverz_Bottom;
	float voverz_Left, voverz_Right;

	float uoverz, uoverz_Step;
	float voverz, voverz_Step;

	//(y - a.y) / (c.y - a.y)
	float t_YAYCYAY;
	//(y - a.y) / (b.y - a.y)
	float t_YAYBYAY;

	//˫��ѭ��
	//һ��һ�е���Ⱦ
	for (int y = miny; y <= maxy; y++)
	{
		//������õ��������������
		t_YAYCYAY = (y - y1) / (y3 - y1);
		t_YAYBYAY = (y - y1) / (y2 - y1);

		//��ǰ�е����Ҷ˵�
		xLeft = t_YAYCYAY * (x3 - x1) + x1;
		xRight = t_YAYBYAY * (x2 - x1) + x1;

		//͸����ȷ�Ĳ�ֵ ֵ�ļ���
		//1 / z
		oneoverz_Top = 1 / a.w;
		oneoverz_Bottom = 1 / c.w;
		oneoverz_Left = t_YAYCYAY * (oneoverz_Bottom - oneoverz_Top) + oneoverz_Top;
		oneoverz_Bottom = 1 / b.w;
		oneoverz_Right = t_YAYBYAY * (oneoverz_Bottom - oneoverz_Top) + oneoverz_Top;
		oneoverz_Step = (oneoverz_Right - oneoverz_Left) / (xRight - xLeft);
		//U / z
		uoverz_Top = uv_a.x / a.w;
		uoverz_Bottom = uv_c.x / c.w;
		uoverz_Left = t_YAYCYAY * (uoverz_Bottom - uoverz_Top) + uoverz_Top;
		uoverz_Bottom = uv_b.x / b.w;
		uoverz_Right = t_YAYBYAY * (uoverz_Bottom - uoverz_Top) + uoverz_Top;
		uoverz_Step = (uoverz_Right - uoverz_Left) / (xRight - xLeft);
		//V / z
		voverz_Top = uv_a.y / a.w;
		voverz_Bottom = uv_c.y / c.w;
		voverz_Left = t_YAYCYAY * (voverz_Bottom - voverz_Top) + voverz_Top;
		voverz_Bottom = uv_b.y / b.w;
		voverz_Right = t_YAYBYAY * (voverz_Bottom - voverz_Top) + voverz_Top;
		voverz_Step = (voverz_Right - voverz_Left) / (xRight - xLeft);


		int x = 0;
		for (x = (int)xLeft, oneoverz = oneoverz_Left, uoverz = uoverz_Left, voverz = voverz_Left; x < xRight; x++, oneoverz += oneoverz_Step, uoverz += uoverz_Step, voverz += voverz_Step) {
			u = (int)(uoverz / oneoverz);
			v = (int)(voverz / oneoverz);

			int _x = x;
			int _y = WindowFrame::rect_client.bottom - y;
			int _index = (_y - 1) * WindowFrame::rect_client.right + x;

			if (_index < WindowFrame::rect_client.right * WindowFrame::rect_client.bottom && _index >= 0) {
				float &_z = m_z_depth_buffer[_index];
				if (oneoverz > _z) {
#ifdef DEBUG
					//debug
					assert(u != 512);
					assert(v != 512);
#endif
					DrawPixel(_x, _y, GetPixel(texture, u, v));
					_z = oneoverz;
				}
			}
		}
	}
}

/////////////////
// Draw Lines //
/////////////////

void Render::DrawTriangles(vector<Vector4>& vertices, vector<Vector2<int>>& indices)
{
	//Draw every face of that object
	int indice_count = (int)indices.size();
	for (int lop = 0; lop < indice_count; lop += 3) {
		DrawTriangle(
			vertices[(int)indices[lop].x],
			vertices[(int)indices[lop + 1].x],
			vertices[(int)indices[lop + 2].x],
			COLOR_BLACK);
	}
}

void Render::DrawTriangle(const Vector4 p0, const Vector4 p1, const Vector4 p2, COLORREF color)
{
	if (TriangleBackcull(p0, p1, p2)) {
		return;
	}

	Vector2<float> vertex[3];
	vertex[0].x = (p0.x + 1.0f) * WindowFrame::rect_client.right / 2.0f;
	vertex[0].y = (p0.y + 1.0f) * WindowFrame::rect_client.bottom / 2.0f;

	vertex[1].x = (p1.x + 1.0f) * WindowFrame::rect_client.right / 2.0f;
	vertex[1].y = (p1.y + 1.0f) * WindowFrame::rect_client.bottom / 2.0f;

	vertex[2].x = (p2.x + 1.0f) * WindowFrame::rect_client.right / 2.0f;
	vertex[2].y = (p2.y + 1.0f) * WindowFrame::rect_client.bottom / 2.0f;

	DrawLine(vertex[0], vertex[1], color);
	DrawLine(vertex[1], vertex[2], color);
	DrawLine(vertex[2], vertex[0], color);
}

void Render::DrawLine(Vector2<float> p0, Vector2<float> p1, COLORREF color)
{
	//ֱ��б���Ƿ����1
	BOOL steep = ABS(p1.y - p0.y) > ABS(p1.x - p0.x);
	//�������1
	//��ֱ���� y=x ��ת���
	if (steep) {
		swap<float>(p0.x, p0.y);
		swap<float>(p1.x, p1.y);
	}
	if (p0.x > p1.x) {
		swap<float>(p0.x, p1.x);
		swap<float>(p0.y, p1.y);
	}
	int dx = (int)(p1.x - p0.x);
	int dy = (int)ABS(p1.y - p0.y);

	int err = dx / 2;

	//y������
	int ystep = (p0.y < p1.y) ? 1 : -1;
	//���ڻ滭�� y ��ֵ
	int painter_y = (int)p0.y;

	for (int i = (int)p0.x; i <= p1.x; i++) {
		if (steep) {
			DrawPixel(painter_y, WindowFrame::rect_client.bottom - i, color);
		}
		else {
			DrawPixel(i, WindowFrame::rect_client.bottom - painter_y, color);
		}
		err -= dy;
		if (err < 0) {
			painter_y += ystep;
			err += dx;
		}
	}
}

inline void Render::DrawPixel(int x, int y, COLORREF color)
{
	SetPixel(m_hdc_buffer, x, y, color);
}
