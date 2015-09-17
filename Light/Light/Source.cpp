#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/gltools.h> // // gltools library link ( Normal 을 구하는 함수 구현 )

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;
void SetupRC()
{
	// Light values and coordinates
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f };
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // 내부 폴리곤 연산 off (backface culling) 
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb); 
	glEnable(GL_COLOR_MATERIAL); 
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void DrawJet()
{
	//... Drawjet.c
}
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Save the matrix state
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); 
	glRotatef(yRot, 0.0f, 1.0f, 0.0f); 
	glTranslatef(0.0f, 0.0f, zDistance);
	DrawJet(); // geometry to draw jet
	glPopMatrix();
	glutSwapBuffers();
}

void ContorolKey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN) xRot += 5.0f;
	if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT) yRot += 5.0f;
	if (key == GLUT_KEY_HOME) zDistance += 5.0f;
	if (key == GLUT_KEY_END) zDistance -= 5.0f;
	glutPostRedisplay();
}
void ChangeSize(int w, int h) {
	GLfloat fAspect;
	GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	//light position
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h; 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 1.0f, 255.0f); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//light position
	glTranslatef(0.0f, 0.0f, -150.0f);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Light Jet");
	glutReshapeFunc(ChangeSize); 
	glutSpecialFunc(ContorolKey); 
	glutDisplayFunc(RenderScene); 
	SetupRC();
	glutMainLoop();
}