#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float dt = 0.0;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);  //add
	glFrontFace(GL_CCW);      //add
	glEnable(GL_CULL_FACE);   //add

	glEnable(GL_LIGHTING);

	GLfloat amb[] = { 0.3f, 0.3f, 0.3f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat diff[] = { 0.7f, 0.7f, 0.7f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 8);

	// 이게 glTranslatef의 영향을 받지 않음.
	// 원래 -300.f를 줘야 하는데 태양이 꾸리꾸리 보여서 조금 앞으로 당겨놓음.
	GLfloat lightPos[] = { 0.0f, 0.0f, -250.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void Update()
{
	// 균일한 속도를 위해 dt를 구한다.
	// 0으로 빠지는 것을 줄이기 위해 추가.
	Sleep(5);
	static int prevTime = GetTickCount();
	int curTime = GetTickCount();
	dt = (float)(curTime - prevTime) / 1000;
	prevTime = curTime;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, fAspect, 100.0f, 500.0f);
}

void RenderScene() // add – draw 3 sphere 
{
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 모델뷰 행렬을 만들고 초기화.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//sun
	glTranslatef(0.0f, 0.0f, -300.0f);
	glColor3ub(255, 0, 0);
	glutSolidSphere(15.0f, 15, 15);
	glPushMatrix();

	//earth
	glRotatef(fElect2, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(130.0f, 0.0f, 0.0f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(10.0f, 15, 15);
	glPushMatrix();

	//moon
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(1.0f, 15, 15);
	glPopMatrix();
	glPushMatrix();

	fElect1 = fElect1 + 150.0f * dt;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	fElect2 = fElect2 + 10.0f * dt;
	if (fElect2 > 360.0f)
		fElect2 = 0.0f;
	glutSwapBuffers();
}

void main(void)
{
	// 더블 버퍼링 | RGB모드 | Deptn체크
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Atom");
	glutReshapeFunc(ChangeSize);
	//glutTimerFunc(33, TimerFunc, 1);
	glutIdleFunc(Update);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
