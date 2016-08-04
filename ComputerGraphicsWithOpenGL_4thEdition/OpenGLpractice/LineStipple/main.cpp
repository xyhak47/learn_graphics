/**/

#include <GL\glut.h>

/* define a two-demensional world-coordinate data type */
GLsizei winWidth = 500, winHeight = 600;

struct wcPt2D
{
	wcPt2D(GLfloat _x, GLfloat _y) : x(_x), y(_y) {}
	GLfloat x, y; 
};

wcPt2D dataPts[5] = { wcPt2D(10, 10), wcPt2D(20, 20), wcPt2D(30, 30), wcPt2D(40, 40), wcPt2D(50, 50) };


void init()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void winReshapeFunc(GLint newWidh, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidh), 0.0, GLdouble(newHeight));

	glClear(GL_COLOR_BUFFER_BIT);
}

void linePlot(wcPt2D dataPts[5], GLfloat offsety)
{
	int k;

	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 5; k++)
	{
		glVertex2f(dataPts[k].x * 10, (dataPts[k].y + offsety) * 10);
	}
	glEnd();
	glFlush();
}

void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);

	/* invoke a procedure here to draw coordinate axes */
	glEnable(GL_LINE_STIPPLE);


	glLineStipple(1, 0x1C47);
	linePlot(dataPts,0);

	glLineStipple(1, 0x00FF);
	glLineWidth(2.0);
	linePlot(dataPts,10);

	glLineStipple(1, 0x0101);
	glLineWidth(3.0);
	linePlot(dataPts,20);


	glDisable(GL_LINE_STIPPLE);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("line stipple");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}