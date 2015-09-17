#include <gl/glut.h>
#include <windows.h>
#include <math.h>

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);  //add
	glFrontFace(GL_CCW);      //add
	glEnable(GL_CULL_FACE);   //add
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}
void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, fAspect, 1.0f, 500.0f);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -300.0f);

	float s = 50;

	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		//front
		glVertex3f(-s, s, s);
		glVertex3f(-s, -s, s);
		glVertex3f(s, -s, s);
		glVertex3f(s, s, s);
		//right
		glVertex3f(s, s, s);
		glVertex3f(s, -s, s);
		glVertex3f(s, -s, -s);
		glVertex3f(s, s, -s);
		//top
		glVertex3f(-s, s, s);
		glVertex3f(s, s, s);
		glVertex3f(s, s, -s);
		glVertex3f(-s, s, -s);
	glEnd();


	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
