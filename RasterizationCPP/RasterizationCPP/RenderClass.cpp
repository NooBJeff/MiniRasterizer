#include "RenderClass.h"

void RenderClass::DrawObjects() {
	WorldToView = m_Camera->GetWorldToViewMatrix4();
	Matrix4 LocalToView;
	for (Object object : RenderObjects) {
		vector<Vector4> transformedVertexes;

		LocalToView = Matrix4('A', object.Rotation) * Matrix4(object.Position);
		LocalToView = LocalToView * WorldToView;

		for (int lop = 0; lop < (int)object.vertices.size(); lop++) {
			//Local To View transformation
			transformedVertexes.push_back(object.vertices[lop] * LocalToView);

			//View To Homo transformation
			transformedVertexes[lop] = transformedVertexes[lop] * m_Camera->ViewToHomo;

			float z_depth = transformedVertexes[lop].w;
			transformedVertexes[lop].x /= z_depth;
			transformedVertexes[lop].y /= z_depth;
			transformedVertexes[lop].z /= z_depth;
		}

		//Draw every face of that object
		for (int lop = 0; lop < (int)object.indices.size(); lop += 3) {
			DrawTriangle(transformedVertexes[lop], transformedVertexes[lop + 1], transformedVertexes[lop + 2], COLOR_BLACK);
		}
	}
}

RenderClass::RenderClass(InputClass *input) {
	m_ptr_Input = input;
	m_Camera = NULL;
}

RenderClass::~RenderClass() {
	delete m_Camera;
}

void RenderClass::Initialize(RECT *rectWindow, HWND *hWndScreen) {
	m_ptr_rectRenderArea = rectWindow;
	m_ptr_hwnd = hWndScreen;

	m_hdcScreen = GetDC(*m_ptr_hwnd);

	m_Camera = new CameraClass((float)(rectWindow->right / rectWindow->bottom), 70.0f, m_ptr_Input, &fps);
	m_Camera->Update();

	//��ʼ������
	RenderObjects.push_back(Object());
	RenderObjects.push_back(Object(Vector3(100.f, 100.f, 0), Vector3(0, 0, 180.0f)));
}

void RenderClass::DeleteResources() {
	DeleteDC(m_hdcBuffer);
	DeleteObject(m_brushBackground);
}

void RenderClass::Shutdown() {
	DeleteResources();
	delete m_Camera;
	m_Camera = nullptr;
}

void RenderClass::RenderAFrame() {
	////////////////
	// >ÿ֡���� //
	////////////////
	fps.computeTime();
	GetCursorPos(&m_ptr_Input->rectCursor);
	m_Camera->CameraControl();
	////////////////
	// <ÿ֡���� //
	////////////////

	//if (m_ptr_Input->IsKeyPressed('Z')) {
	//}


	OutputText(fps.getFPSwstring(), 0);

	//
	wstringstream ws;
	ws <<"Resolution : " << m_ptr_rectRenderArea->right << " * " << m_ptr_rectRenderArea->bottom;
	OutputText(ws.str(), 1);

	ws.str(L"");
	ws << "Use W, A, S, D ,Q ,E and Arrow keys to move around";
	OutputText(ws.str(), 2);

	
	////////////////
	// >ÿ֡���� //
	////////////////

	DrawObjects();

	m_ptr_Input->clearFlag();
	SwapBufferToScreen();
	ClearCanvas();
	////////////////
	// <ÿ֡���� //
	////////////////
}

void RenderClass::UpdateSettings()
{
	//��Ϊ��ʱɾ��ԭ������
	if (m_hdcBuffer) {
		DeleteResources();
	}
	//��ʱ��bufferû�д�С
	m_hdcBuffer = CreateCompatibleDC(m_hdcScreen);

	//���뱾�ر���ͼƬ
	HBITMAP bmpBackgroundImage = (HBITMAP)LoadImage(NULL, TEXT("Resources\\Materials\\Background.bmp"), IMAGE_BITMAP,
		m_ptr_rectRenderArea->right, m_ptr_rectRenderArea->bottom, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//�������ʧ��
	//������ɫ����
	if (bmpBackgroundImage == NULL) {
		bmpBackgroundImage = CreateCompatibleBitmap(m_hdcScreen, m_ptr_rectRenderArea->right, m_ptr_rectRenderArea->bottom);

		SelectObject(m_hdcBuffer, bmpBackgroundImage);
		FillRect(m_hdcBuffer, m_ptr_rectRenderArea, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}
	else {
		//ѡ������
		SelectObject(m_hdcBuffer, bmpBackgroundImage);
	}
	//���ݲ�����ͼ��������ˢ
	m_brushBackground = CreatePatternBrush(bmpBackgroundImage);
	//֮�� bmp �Ϳ���ɾ��
	//�Ժ��û�ˢ������
	DeleteObject(bmpBackgroundImage);
	//���ģʽ��Ϊ͸��
	SetBkMode(m_hdcBuffer, TRANSPARENT);

	//���������������
	m_Camera->Update((float)m_ptr_rectRenderArea->right / (float)m_ptr_rectRenderArea->bottom, m_Camera->FOV);
}

void RenderClass::SwapBufferToScreen() {
	BitBlt(m_hdcScreen, 0, 0, m_ptr_rectRenderArea->right, m_ptr_rectRenderArea->bottom, m_hdcBuffer, 0, 0, SRCCOPY);
}

void RenderClass::ClearCanvas() {
	//�ñ�����ˢ��䱳��
	FillRect(m_hdcBuffer, m_ptr_rectRenderArea, m_brushBackground);
}

inline void RenderClass::OutputText(const wstring & text, int line) {
	TextOut(m_hdcBuffer, 0, 20 * line, text.data(), text.size());
}

void RenderClass::DrawTriangle(const Vector4 p0, const Vector4 p1, const Vector4 p2, COLORREF color)
{
	if (triangleBackcull(p0, p1, p2)) {
		return;
	}

	Vector2 vertex[3];
	vertex[0].x = (p0.x + 1.0f) * m_ptr_rectRenderArea->right / 2.0f;
	vertex[0].y = (p0.y + 1.0f) * m_ptr_rectRenderArea->bottom / 2.0f;

	vertex[1].x = (p1.x + 1.0f) * m_ptr_rectRenderArea->right / 2.0f;
	vertex[1].y = (p1.y + 1.0f) * m_ptr_rectRenderArea->bottom / 2.0f;

	vertex[2].x = (p2.x + 1.0f) * m_ptr_rectRenderArea->right / 2.0f;
	vertex[2].y = (p2.y + 1.0f) * m_ptr_rectRenderArea->bottom / 2.0f;

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
			DrawPixel(painter_y, m_ptr_rectRenderArea->bottom - i, color);
		}
		else {
			DrawPixel(i, m_ptr_rectRenderArea->bottom - painter_y, color);
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
	SetPixel(m_hdcBuffer, x, y, color);
}
