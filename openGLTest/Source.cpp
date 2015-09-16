#include <windows.h>
#include <gl\glut.h>
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLsizei rsize = 50.0f;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
GLfloat window_width;
GLfloat window_height;



//class Rect{
//public:
//	GLfloat x = 0.0f;
//	GLfloat y = 0.0f;
//	GLsizei rsize = 50.0f;
//	GLfloat xstep = 1.0f;
//	GLfloat ystep = 1.0f;
//public:
//	Rect(GLfloat _x, GLfloat _y){
//		x = _x;
//		y = _y;
//	}
//
//	static void TimerFunction(int value)
//	{
//		if (x > window_width - rsize || x < -window_width)
//			xstep = -xstep;
//		if (y>window_height - rsize || y< -window_height)
//			ystep = -ystep;
//		if (x > window_width - rsize)
//			x = window_width - rsize - 1;
//		if (y > window_height - rsize)
//			y = window_height - rsize - 1;
//		x += xstep;
//		y += ystep;
//		glutPostRedisplay();
//		glutTimerFunc(33, TimerFunction, 1);
//	}
//};

void TimerFunction(int value)
{
	if (x1> window_width - rsize || x1 < -window_width)
		xstep = -xstep;
	if (y1>window_height - rsize || y1< -window_height)
		ystep = -ystep;
	if (x1 > window_width - rsize)
		x1 = window_width - rsize - 1;
	if (y1 >window_height - rsize)
		y1 = window_height - rsize - 1;
	x1 += xstep;
	y1 += ystep;
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x1 + rsize, y1 + rsize);
	glutSwapBuffers();
}


void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
	// timer
	glutTimerFunc(2000, TimerFunction, 1);
	// �ʱ� setup
	SetupRC();
	//glutMain �Լ�ȣ��, glut�� ���� framework�Լ� ȣ��
	glutMainLoop();
}

