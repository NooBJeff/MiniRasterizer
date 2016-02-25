#include "RenderClass.h"

void RenderClass::m_DrawObjects() {
	m_world_to_view = m_ptr_camera->GetWorldToViewMatrix4();
	Matrix4 LocalToView;
	for (auto object : vector_objects) {
		vector<Vector4> transformed_vertices;

		LocalToView = Matrix4('A', object.rotation) * Matrix4(object.position);
		LocalToView = LocalToView * m_world_to_view;

		for (int lop = 0; lop < (int)object.vertices.size(); lop++) {
			//Local To View transformation
			transformed_vertices.push_back(object.vertices[lop] * LocalToView);

			//View To Homo transformation
			transformed_vertices[lop] = transformed_vertices[lop] * m_ptr_camera->view_to_homo;

			float z_depth = transformed_vertices[lop].w;
			transformed_vertices[lop].x /= z_depth;
			transformed_vertices[lop].y /= z_depth;
			transformed_vertices[lop].z /= z_depth;
		}

		//Draw every face of that object
		for (int lop = 0; lop < (int)object.indices.size(); lop += 3) {
			DrawTriangle(transformed_vertices[lop], transformed_vertices[lop + 1], transformed_vertices[lop + 2], COLOR_BLACK);
		}
	}
}

RenderClass::RenderClass(InputClass *input) {
	m_ptr_input = input;
	m_ptr_camera = NULL;
}

RenderClass::~RenderClass() {
	delete m_ptr_camera;
}

void RenderClass::Initialize(RECT *rectWindow, HWND *hWndScreen) {
	m_ptr_rect_client = rectWindow;
	m_ptr_hwnd = hWndScreen;

	m_hdc_screen = GetDC(*m_ptr_hwnd);

	m_ptr_camera = new CameraClass((float)(rectWindow->right / rectWindow->bottom), 70.0f, m_ptr_input, &m_time);
	m_ptr_camera->Update();

	//��ʼ������
	vector_objects.push_back(ObjectClass());
	vector_objects.push_back(ObjectClass(Vector3(100.f, 100.f, 0), Vector3(0, 0, 180.0f)));
}

void RenderClass::DeleteResources() {
	DeleteDC(m_hdc_buffer);
	DeleteObject(m_brush_background);
}

void RenderClass::Shutdown() {
	DeleteResources();
	delete m_ptr_camera;
	m_ptr_camera = nullptr;
}

void RenderClass::RenderAFrame() {
	////////////////
	// >ÿ֡���� //
	////////////////
	m_time.ComputeTime();
	GetCursorPos(&m_ptr_input->point_cursor_current);
	m_ptr_camera->CameraControl();
	////////////////
	// <ÿ֡���� //
	////////////////
	OutputText(m_time.GetFPSwstring(), 0);

	wstringstream ws;
	ws <<"Resolution : " << m_ptr_rect_client->right << " * " << m_ptr_rect_client->bottom;
	OutputText(ws.str(), 1);

	ws.str(L"");
	ws << "Use W, A, S, D ,Q ,E and Arrow keys to move around";
	OutputText(ws.str(), 2);

	////////////////
	// >ÿ֡���� //
	////////////////

	m_DrawObjects();

	m_ptr_input->ClearFlag();
	SwapBufferToScreen();
	ClearCanvas();
	////////////////
	// <ÿ֡���� //
	////////////////
}

void RenderClass::UpdateSettings()
{
	//��Ϊ��ʱɾ��ԭ������
	if (m_hdc_buffer) {
		DeleteResources();
	}
	//��ʱ��bufferû�д�С
	m_hdc_buffer = CreateCompatibleDC(m_hdc_screen);

	//���뱾�ر���ͼƬ
	HBITMAP bmpBackgroundImage = (HBITMAP)LoadImage(NULL, TEXT("Resources\\Materials\\Background.bmp"), IMAGE_BITMAP,
		m_ptr_rect_client->right, m_ptr_rect_client->bottom, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//�������ʧ��
	//������ɫ����
	if (bmpBackgroundImage == NULL) {
		bmpBackgroundImage = CreateCompatibleBitmap(m_hdc_screen, m_ptr_rect_client->right, m_ptr_rect_client->bottom);

		SelectObject(m_hdc_buffer, bmpBackgroundImage);
		FillRect(m_hdc_buffer, m_ptr_rect_client, (HBRUSH)GetStockObject(GRAY_BRUSH));
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
	m_ptr_camera->Update((float)m_ptr_rect_client->right / (float)m_ptr_rect_client->bottom, m_ptr_camera->fov);
}

void RenderClass::SwapBufferToScreen() {
	BitBlt(m_hdc_screen, 0, 0, m_ptr_rect_client->right, m_ptr_rect_client->bottom, m_hdc_buffer, 0, 0, SRCCOPY);
}

void RenderClass::ClearCanvas() {
	//�ñ�����ˢ��䱳��
	FillRect(m_hdc_buffer, m_ptr_rect_client, m_brush_background);
}

inline void RenderClass::OutputText(const wstring & text, int line) {
	TextOut(m_hdc_buffer, 0, 20 * line, text.data(), text.size());
}

void RenderClass::DrawTriangle(const Vector4 p0, const Vector4 p1, const Vector4 p2, COLORREF color)
{
	if (triangleBackcull(p0, p1, p2)) {
		return;
	}

	Vector2 vertex[3];
	vertex[0].x = (p0.x + 1.0f) * m_ptr_rect_client->right / 2.0f;
	vertex[0].y = (p0.y + 1.0f) * m_ptr_rect_client->bottom / 2.0f;

	vertex[1].x = (p1.x + 1.0f) * m_ptr_rect_client->right / 2.0f;
	vertex[1].y = (p1.y + 1.0f) * m_ptr_rect_client->bottom / 2.0f;

	vertex[2].x = (p2.x + 1.0f) * m_ptr_rect_client->right / 2.0f;
	vertex[2].y = (p2.y + 1.0f) * m_ptr_rect_client->bottom / 2.0f;

	DrawLine(vertex[0], vertex[1], color);
	DrawLine(vertex[1], vertex[2], color);
	DrawLine(vertex[2], vertex[0], color);
}

void RenderClass::DrawLine(Vector2 p0, Vector2 p1, COLORREF color)
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
			DrawPixel(painter_y, m_ptr_rect_client->bottom - i, color);
		}
		else {
			DrawPixel(i, m_ptr_rect_client->bottom - painter_y, color);
		}
		err -= dy;
		if (err < 0) {
			painter_y += ystep;
			err += dx;
		}
	}
}

inline void RenderClass::DrawPixel(int x, int y, COLORREF color)
{
	SetPixel(m_hdc_buffer, x, y, color);
}
