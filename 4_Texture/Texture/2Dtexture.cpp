#include <windows.h>
#include <math.h>
#include <gl/glut.h>
#include "glaux.h"

#define GL_PI 3.14159f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;
float dt = 0.0;

GLfloat amb [] = { 0.3f, 0.3f, 0.3f, 1.0f};
GLfloat dif [] = { 0.8f, 0.8f, 0.8f, 1.0f}; 
GLfloat	lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f};

AUX_RGBImageRec * texRec[3]; //add 
GLuint texID[2];

void TextureInit(){
	texRec[0] = auxDIBImageLoad("sun.bmp"); //add
	texRec[1] = auxDIBImageLoad("earth.bmp"); //add
	texRec[2] = auxDIBImageLoad("moon.bmp"); //add

	glGenTextures(3, texID); // 두 개의 멀티 텍스쳐 ID 배열 설정
	for (int i = 0; i < 2; i++) //add ///////////////////////////////////////////
	{
		glBindTexture(GL_TEXTURE_2D, texID[i]); // 사용할 텍스쳐 ID 지정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, texRec[i]->data);
	}


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	TextureInit();
}

void RenderScene()
{
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -50.0f);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f); 
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f); 
	glTranslatef(0.0f, 0.0f, zDistance);

	//sun
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	glTranslatef(0.0f, 0.0f, 0.0f);
	GLUquadric *quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 5.0f, 50.0f, 50.0f);
	glPushMatrix();

	//earth
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glRotatef(fElect1, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(13.0f, 0.0f, 0.0f);
	gluSphere(quad, 2.0f, 50.0f, 50.0f);
	glPushMatrix();

	//moon
	glBindTexture(GL_TEXTURE_2D, texID[2]);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	gluSphere(quad, 0.5f, 50.0f, 50.0f);
	glPushMatrix();

	fElect1 = fElect1 + 10.0f * dt;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	fElect2 = fElect2 + 150.0f * dt;
	if (fElect2 > 360.0f)
		fElect2 = 0.0f;

	glutSwapBuffers();
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
    
	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; // Window의 종횡비 계산

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,500.0f); //(FOV,종횡비,near,far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-50.0f);
		
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2D texture");
	glutIdleFunc(Update);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
	
}