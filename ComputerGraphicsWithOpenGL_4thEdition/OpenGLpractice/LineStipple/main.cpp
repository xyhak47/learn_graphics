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
	/***************draw line ******************/
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


	/********************draw 3 colors triangles ************************/
	glShadeModel(GL_SMOOTH); // default is GL_SMOOTH
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(50, 50);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(150, 50);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(75, 150);
	glEnd();

	/********************draw  POLYGON triangles ************************/
	GLuint polyginlist0 = glGenLists(1);
	glNewList(polyginlist0, GL_COMPILE);
		glBegin(GL_POLYGON);
			glVertex2i(250, 50);
			glVertex2i(300, 50);
			glVertex2i(330, 70);
			glVertex2i(280, 100);
			glVertex2i(230, 70);
		glEnd();
	glEndList();

	glColor3f(0.0, 1.0, 0.0);
	glCallList(polyginlist0);

	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glCallList(polyginlist0);


	glPolygonMode(GL_FRONT, GL_FILL);
	GLuint polyginlist1 = glGenLists(1);
	glNewList(polyginlist1, GL_COMPILE);
		glBegin(GL_POLYGON);
			glVertex2i(350, 50);
			glVertex2i(400, 50);
			glVertex2i(430, 70);
			glVertex2i(380, 100);
			glVertex2i(330, 70);
		glEnd();
	glEndList();

	glColor3f(0.0, 1.0, 0.0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glCallList(polyginlist1);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glCallList(polyginlist1);

	/* **********draw edge flag **********/
	glBegin(GL_POLYGON);
		glVertex2i(250, 150);
		glEdgeFlag(true);
		glVertex2i(300, 150);
		glEdgeFlag(true);
		glVertex2i(330, 170);
	glEnd();


	glFlush();
}

void drawPolygon5()
{

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