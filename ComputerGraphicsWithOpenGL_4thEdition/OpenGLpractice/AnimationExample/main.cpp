/**/

#include <GL\glut.h>
#include <math.h>
#include <stdlib.h>


const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;

class scrPt
{
public:
	GLint x, y;
};


void init()
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 1.0);

	/*
		set up a display list for a red regular hexagon verteces for the
		hexagon are six equally spaced points around the circumference of a circle
	*/

	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			for (k = 0; k < 6; k++)
			{
				hexTheta = TWO_PI * k / 6;
				hexVertex.x = 150 + 100 * cos(hexTheta);
				hexVertex.y = 150 + 100 * sin(hexTheta);
				glVertex2i(hexVertex.x, hexVertex.y);
			}
		glEnd();
	glEndList();
}

void displayHex()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotated(rotTheta, 0.0, 0.0, 1.0);
	glCallList(regHex);
	glPopMatrix();

	glutSwapBuffers();

	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320, 320, -320, 320);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}

void rotateHex()
{
	rotTheta += 3.0;
	if (rotTheta > 360.0)
	{
		rotTheta -= 360.0;
	}

	glutPostRedisplay();
}


void mouseFunc(GLint button, GLint action, GLint x, GLint y)
{
	switch (button)
	{
	case GLUT_MIDDLE_BUTTON:
		if (action == GLUT_DOWN)
		{
			glutIdleFunc(rotateHex);
			break;
		}

	case GLUT_RIGHT_BUTTON:
		if (action == GLUT_DOWN)
		{
			glutIdleFunc(NULL);
			break;
		}
	default:
		break;
	}
}



void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow(" animation example");

	init();
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFunc);
	glutMouseFunc(mouseFunc);

	glutMainLoop();
}