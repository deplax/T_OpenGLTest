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
	// 균일한 속도를 위해 dt를 구한다.
	// 0으로 빠지는 것을 줄이기 위해 추가.
	Sleep(5);
	static int prevTime = GetTickCount();
	int curTime = GetTickCount();
	float dt = (float)(curTime - prevTime)/1000;
	prevTime = curTime;

	// Rect 위치 갱신.
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
	// 더블 버퍼 사용 | RGB컬러모드 사용.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// 윈도우 크기 지정.
	glutInitWindowSize(800, 600);
	// 윈도우 생성.
	glutCreateWindow("BounceRectangle");
	// RenderScene함수를 Display Callback 함수로 사용.
	glutDisplayFunc(RenderScene);
	// 윈도우 크기가 변경될 때마다 호출되는 함수.
	glutReshapeFunc(ChangeSize);

	glutIdleFunc(Update);

	// timer
	//glutTimerFunc(2000, TimerFunction, 1);
	// 초기 setup
	SetupRC();
	//glutMain 함수호출, glut의 메인 framework함수 호출
	glutMainLoop();
}

