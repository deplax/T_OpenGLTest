#include <gl/glut.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f

GLfloat window_width = 0.0f;
GLfloat window_height = 0.0f;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float dt = 0.0;

void SetupRC()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);   
	glEnable(GL_CULL_FACE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Update()
{
	Sleep(5);
	static int prevTime = GetTickCount();
	int curTime = GetTickCount();
	dt = (float)(curTime - prevTime) / 1000;
	prevTime = curTime;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f * h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 100.0, -100.0);
	}
	else
	{
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 100.0, -100.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void drawCircle(float radius, float x1, float y1)
{
	float angle = 0;
	float x2, y2, cx, cy, fx, fy;
	int cache = 0;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 360; angle += 1.0) {
		float rad_angle = angle * GL_PI / 180;
		x2 = radius * sin((double)rad_angle);
		y2 = radius * cos((double)rad_angle);
		if (cache) {
			glVertex2f(cx, cy);
			glVertex2f(x2, y2);
		}
		else {
			fx = x2;
			fy = y2;
		}
		cache = 1;
		cx = x2;
		cy = y2;
	}
	glVertex2f(x2, y2);
	glVertex2f(fx, fy);
	glEnd();
}

void RenderScene(){
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 모델뷰 행렬을 만들고 초기화.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Center Circle
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor4ub(0, 0, 0, 80);
	drawCircle(50.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect1, 0.0f, 0.0f, 1.0f);
	glTranslatef(50.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(15.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glTranslatef(15.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(10.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glTranslatef(10.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(7.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glTranslatef(7.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(5.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glTranslatef(5.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(3.0f, 0.0f, 0.0f);
	glPushMatrix();

	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glTranslatef(3.0f, 0.0f, -1.0f);
	glColor4ub(255, 0, 0, 80);
	drawCircle(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -1.0f);
	drawCircle(1.0f, 0.0f, 0.0f);
	glPushMatrix();


	GLfloat Minv[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, Minv);
	glLoadIdentity();
	glTranslatef(0.0f, Minv[13], -50.0f);
	glColor4ub(0, 0, 255, 100);
	drawCircle(1.0f, 0.0f, 0.0f);
	glPushMatrix();

	glutSwapBuffers();

	fElect1 = fElect1 + 30.0f * dt;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	fElect2 = fElect2 + 60.0f * dt;
	if (fElect2 > 360.0f)
		fElect2 = 0.0f;
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("custom");
	glutIdleFunc(Update);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}