
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

const GLfloat twoPi = 6.283185;
GLsizei winWidth = 400, winHeight = 300; // initialize display window size

class scrPt
{
public:
	GLint x, y;
};

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void circleMidpoint(const scrPt& circleCenter, GLfloat radius)
{
	// x = c.x + cos(r);
	// y = c.y + sin(r);
}

void pieChart()
{
	scrPt circCtr, piePt;
	GLint radius = winWidth / 4; // circle radius

	GLdouble sliceAngle, previousSliceAngle = 0.0;

	GLint k, nSlices = 12; // number of slices
	GLfloat dataValues[12] = { 10.0f, 7.0f, 13.0f, 5.0f, 13.0f, 14.0f, 3.0f, 16.0f, 5.0f, 3.0f, 17.0f, 8.0f };
	GLfloat dataSum = 0.0;

	circCtr.x = winWidth / 2;
	circCtr.y = winHeight / 2;
	circleMidpoint(circCtr, radius); // call a midpoint circle-plot routine

	for (k = 0; k < nSlices; k++)
	{
		dataSum += dataValues[k];
	}

	for (k = 0; k < nSlices; k++)
	{
		sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
		piePt.x = circCtr.x + radius * cos(sliceAngle);
		piePt.y = circCtr.y + radius * sin(sliceAngle);
		glBegin(GL_LINES);
		glVertex2i(circCtr.x, circCtr.y);
		glVertex2i(piePt.x, piePt.y);
		glEnd();
		previousSliceAngle = sliceAngle;
	}
}

void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT); // clear dispaly window
	glColor3f(0.0, 0.0, 1.0);
	pieChart();
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));

	glClear(GL_COLOR_BUFFER_BIT);

	/* reset display window size parameters */
	winWidth = newWidth;
	winHeight = newHeight;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("pie chart");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}