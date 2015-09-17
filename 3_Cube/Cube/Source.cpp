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
	GLfloat nRange = 150.0f;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.0f, nRange*2.0f);	//add
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);	//add
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable smooth shading 􏰄 􏰄 􏰄 glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	// Red Apex
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(0.0f, 200.0f, 0.0f);
	// Green on the right bottom corner
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(200.0f, -70.0f, 0.0f);
	// Blue on the left bottom corner
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-200.0f, -70.0f, 0.0f);
	glEnd();
	// Flush drawing commands
	glutSwapBuffers();
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
