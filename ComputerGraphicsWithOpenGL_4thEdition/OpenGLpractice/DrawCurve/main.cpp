/**/

#include <GL\glut.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>

using namespace std;

struct screenPt
{
	GLint x, y;
	screenPt& operator= (const screenPt& that)
	{
		this->x = that.x;
		this->y = that.y;

		return *this;
	}
};

typedef enum { limacon = 1, cardioid, threeLeaf, fourLeaf, sprial } curveName;

GLsizei winWidth = 600, winHeight = 500;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150);
}

void lineSegment(screenPt pt1, screenPt pt2)
{
	glBegin(GL_LINES);
	glVertex2i(pt1.x, pt1.y);
	glVertex2i(pt2.x, pt2.y);
	glEnd();
}

void drawCurve(GLint curveNum)
{
	const GLdouble twoPi = 6.283185;
	const GLint a = 175, b = 60;

	GLfloat r, theta, dtheta = 1.0 / float(a);
	GLint x0 = 200, y0 = 250; // set an initial screen position
	screenPt curvePt[2];

	glColor3f(0.0, 0.0, 0.0); // set curve color to black

	curvePt[0].x = x0; // initial curve position
	curvePt[0].y = y0;

	switch (curveNum)
	{
	case limacon: curvePt[0].x += a + b; break;
	case cardioid: curvePt[0].x += a + a; break;
	case threeLeaf: curvePt[0].x += a; break;
	case fourLeaf: curvePt[0].x += a; break;
	case sprial: break;
	default: break;
	}

	theta = dtheta;
	while (theta < twoPi)
	{
		switch (curveNum)
		{
		case limacon: r = a * cos(theta) + b; break;
		case cardioid: r = a * (1 + cos(theta)); break;
		case threeLeaf: r = a * cos(3 * theta); break;
		case fourLeaf: r = a * cos(2 * theta); break;
		case sprial: r = a / 4.0 * theta;  break;
		default: break;
		}

		curvePt[1].x = x0 + r * cos(theta);
		curvePt[1].y = y0 + r * sin(theta);
		lineSegment(curvePt[0], curvePt[1]);

		curvePt[0] = curvePt[1];
		theta += dtheta;
	}
}

void displayFunc()
{
	GLint curveNum;

	glClear(GL_COLOR_BUFFER_BIT); // clear display window

	cout << "\nEnter the integer value corresponding to\n";
	cout << "one of the following curve names.\n";
	cout << "Press any other key to exit.\n";
	cout << "\n1-limacon, 2-cardioid, 3-threeLeaf, 4-fourLeaf, 5-sprial:";
	cin >> curveNum;

	if (curveNum < 1 || curveNum > 5)
	{
		exit(0);
	}

	drawCurve(curveNum);

	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));

	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("draw curves");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}