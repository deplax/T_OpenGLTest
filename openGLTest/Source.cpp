#include "pch.h"
#include "Rect.h"

GLfloat window_width = 0.0f;
GLfloat window_height = 0.0f;

std::vector<Rect> rects;

void TimerFunction(int value)
{

	glutTimerFunc(33, TimerFunction, 1);
}

void Update()
{
	// ������ �ӵ��� ���� dt�� ���Ѵ�.
	// 0���� ������ ���� ���̱� ���� �߰�.
	Sleep(5);
	static int prevTime = GetTickCount();
	int curTime = GetTickCount();
	float dt = (float)(curTime - prevTime)/1000;
	prevTime = curTime;

	// Rect ��ġ ����.
	for (auto& rect : rects)
	{
		rect.Update(dt);
	}

	glutPostRedisplay();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& rect : rects)
	{
		rect.Render();
	}
	glutSwapBuffers();
}


void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Rect r1(-100.0f, -100.0f);
	r1.SetColor(1.0f, 0.0f, 0.0f);
	r1.SetSpeed(50.0f, 50.f);

	Rect r2(0.0f, 0.0f);
	r2.SetColor(0.0f, 1.0f, 0.0f);
	r2.SetSpeed(55.0f, 15.f);

	Rect r3(100.0f, 100.0f);
	r3.SetColor(0.0f, 0.0f, 1.0f);
	r3.SetSpeed(15.0f, 40.f);

	Rect r4(200.0f, 100.0f);
	r4.SetColor(0.0f, 1.0f, 1.0f);
	r4.SetSpeed(30.0f, 75.0f);

	rects.push_back(r1);
	rects.push_back(r2);
	rects.push_back(r3);
	rects.push_back(r4);

	//int idx;
	//rects.erase(rects.begin() + idx);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f*h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	// ���� ���� ��� | RGB�÷���� ���.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// ������ ũ�� ����.
	glutInitWindowSize(800, 600);
	// ������ ����.
	glutCreateWindow("BounceRectangle");
	// RenderScene�Լ��� Display Callback �Լ��� ���.
	glutDisplayFunc(RenderScene);
	// ������ ũ�Ⱑ ����� ������ ȣ��Ǵ� �Լ�.
	glutReshapeFunc(ChangeSize);

	glutIdleFunc(Update);

	// timer
	//glutTimerFunc(2000, TimerFunction, 1);
	// �ʱ� setup
	SetupRC();
	//glutMain �Լ�ȣ��, glut�� ���� framework�Լ� ȣ��
	glutMainLoop();
}

