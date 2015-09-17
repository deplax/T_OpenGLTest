#include "pch.h"
#include "Rect.h"

GLfloat window_width = 0.0f;
GLfloat window_height = 0.0f;

std::vector<Rect> rects;

void CollisionDetect(std::vector<Rect>& rects, int dt){
	for (auto& rect : rects)
	{
		for (auto& r : rects)
		{
			// �� �ڽ��̸� �׳� �н�.
			if (&rect == &r)
				continue;

			Rect *xfirstBlock;
			Rect *xlastBlock;
			Rect *yfirstBlock;
			Rect *ylastBlock;

			// ���� �� �տ� �ִ� ������ ã�´�.
			if (rect.x > r.x)
			{
				xfirstBlock = &r;
				xlastBlock = &rect;
			}
			else{
				xfirstBlock = &rect;
				xlastBlock = &r;
			}

			if (rect.y > r.y)
			{
				yfirstBlock = &r;
				ylastBlock = &rect;
			}
			else{
				yfirstBlock = &rect;
				ylastBlock = &r;
			}

			// �浹�˻�
			if (xlastBlock->x - (xfirstBlock->x + xfirstBlock->rsize) < 0 && 
				(ylastBlock->y - ylastBlock->prevyStep) - (yfirstBlock->y - yfirstBlock->prevyStep + yfirstBlock->rsize) < 0){
				xlastBlock->x = xfirstBlock->x + xfirstBlock->rsize;
				rect.xstep *= -1;
				r.xstep *= -1;
			}

			if (ylastBlock->y - (yfirstBlock->y + yfirstBlock->rsize) < 0 &&
				(xlastBlock->x - xlastBlock->prevxStep) - (xfirstBlock->x - xfirstBlock->prevxStep + xfirstBlock->rsize) < 0){
				ylastBlock->y = yfirstBlock->y + yfirstBlock->rsize;
				rect.ystep *= -1;
				r.ystep *= -1;	
			}
		}
	}
}

void Update()
{
	// ������ �ӵ��� ���� dt�� ���Ѵ�.
	// 0���� ������ ���� ���̱� ���� �߰�.
	Sleep(5);
	static int prevTime = GetTickCount();
	int curTime = GetTickCount();
	float dt = (float)(curTime - prevTime) / 1000;
	prevTime = curTime;

	// Rect ��ġ ����.
	for (auto& rect : rects)
		rect.Update(dt);

	CollisionDetect(rects, dt);
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

	Rect r1(-100.0f, -100.0f, 50.0f);
	r1.SetColor(1.0f, 0.0f, 0.0f);
	r1.SetSpeed(50.0f, 50.f);

	Rect r2(0.0f, 0.0f, 30.0f);
	r2.SetColor(0.0f, 1.0f, 0.0f);
	r2.SetSpeed(55.0f, 15.f);

	Rect r3(-70.0f, 0.0f, 35.0f);
	r3.SetColor(0.0f, 0.0f, 1.0f);
	r3.SetSpeed(15.0f, 40.f);

	Rect r4(0.0f, 70.0f, 10.0f);
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
		window_height = 100.0f * h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	printf("window_width : %f\t", window_width);
	printf("window_height : %f\n", window_height);
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

