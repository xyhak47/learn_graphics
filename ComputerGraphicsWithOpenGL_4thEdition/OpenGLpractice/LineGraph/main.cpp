

#include <GL/glut.h>

GLsizei winWidth = 600, winHeight = 500; // initial dispaly window mode

GLint xRaster = 25, yRaster = 150; // initialize raster position
GLint dataValue[12] = { 420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438 };

GLubyte label[36] = { 'j','a','n', /**/ 'f','e','b', /**/ 'm','a','r',
					  'a','p','r', /**/ 'm','a','y', /**/ 'j','u','n',
					  'j','u','i', /**/ 'a','u','g', /**/ 's','e','p',
					  'o','c','t', /**/ 'n','o','v', /**/ 'd','e','c' };

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // white dispaly mode
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void lineGraph()
{
	GLint month;
	GLint k;
	GLint x = 30; // initialize x position for chart

	glClear(GL_COLOR_BUFFER_BIT); // clear display window

	// draw line
	glColor3f(0.0, 0.0, 1.0); // set line color to blue
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 12; k++)
	{
		glVertex2i(x + k * 50, dataValue[k]);
	}
	glEnd();

	// draw *
	glColor3f(1.0, 0.0, 0.0);
	for (k = 0; k < 12; k++)
	{
		glRasterPos2i(xRaster + k * 50, dataValue[k] - 4);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	} 

	// draw bar charts
	glColor3f(0.0, 0.0, 0.0);
	for (k = 0; k < 12; k++)
	{
		glRecti(20 + k * 50,  165, 40 + k * 50, dataValue[k]);
	}

	// dray char
	glColor3f(0.0, 0.0, 0.0);
	xRaster = 20;
	for (month = 0; month < 12; month++)
	{
		glRasterPos2i(xRaster, yRaster);
		for (k = 3 * month; k < 3 * month + 3; k++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
		}
		xRaster += 50;
	}

	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);

	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow(" line chart data plot");

	init();
	glutDisplayFunc(lineGraph);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}