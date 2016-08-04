/**/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 6.2831853;

/* initial dispaly window size */
GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;
GLuint radius = 150;
GLuint polygonSide = 6;

class ScreenPt
{
public:
	/* default constructor, initializes coordinate position to (0,0) */
	ScreenPt() : x(0), y(0) {}

	void setCoors(GLuint xCoord, GLuint yCoord){ x = xCoord; y = yCoord; }

	GLuint getX() const { return x; }
	GLuint getY() const { return y; }

private:
	GLuint x, y;

};


static void init()
{
	ScreenPt hexVertex, circleCenter;
	GLdouble theta;
	GLuint k;
	/* set circle center coordinates */
	circleCenter.setCoors(winWidth / 2, winHeight / 2);

	glClearColor(1.0, 1.0, 1.0, 1.0); // dispaly window color = white

	/* set up a display list for a red hexagon.
		vertices for the hexagon are six equally spaced points around the circumference of a circle
	*/
	regHex = glGenLists(1); // get an identifier for the display list
	glNewList(regHex, GL_COMPILE);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	for (k = 0; k < polygonSide; k++)
	{
		theta = TWO_PI / polygonSide * k;
		GLuint x = circleCenter.getX() + radius * cos(theta);
		GLuint y = circleCenter.getY() + radius * sin(theta);
		hexVertex.setCoors(x, y);
		glVertex2i(hexVertex.getX(), hexVertex.getY());
	}
	glEnd();

	glEndList();
}

// regular hexagon
void regHexagon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(regHex);
	glFlush();
}

void winReshapeFunc(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("reshape-function & display-list example");

	init();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}