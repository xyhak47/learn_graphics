/**/

#include <GL\glut.h>
#include <math.h>
#include <stdlib.h>

GLsizei winWidth = 500, winHeight = 600;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINT);
	glVertex2i(x, y);
	glEnd();
}

// line DDA
inline int round(const float a) { return int(a + 0.5); }

void lineDDA(GLint x0, GLint y0, GLint xEnd, GLint yEnd)
{

}

// line Bresenham, |m| < 1.0
void lineBres(GLint x0, GLint y0, GLint xEnd, GLint yEnd)
{
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;

	// determine which endpoint to use as start position
	if (x0 > xEnd)
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else
	{
		x = x0;
		y = y0;
	}

	setPixel(x, y);

	while (x < xEnd)
	{
		x++;
		if (p < 0)
		{
			p += twoDy;
		}
		else
		{
			p += twoDyMinusDx;
			y++;
		}
		setPixel(x, y);
	}
}

void dispalyFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1.0, 0.0, 0.0, 1.0);
	lineBres(100, 100, 600, 600);

	glFlush();

}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, newWidth, 0.0, newHeight);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);

	glutDisplayFunc(dispalyFunc);
	//glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}