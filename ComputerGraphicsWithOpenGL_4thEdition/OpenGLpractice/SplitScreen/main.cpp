/**/

#include <GL\glut.h>

class wcPt2D
{
public:
	GLfloat x, y;
};


void init()
{
	/* set color of display window to white */
	glClearColor(1.0, 1.0, 1.0, 0.0);

	/* set parameters for world-coordinate clipping window */
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);

	/* set mode for contructing geometric transformation matrix */
	glMatrixMode(GL_MODELVIEW);
}

void triangle(wcPt2D *verts)
{
	GLint k;

	glBegin(GL_TRIANGLES);
		for (k = 0; k < 3; ++k)
		{
			glVertex2f(verts[k].x, verts[k].y);
		}
	glEnd();
}

void displayFunc()
{
	/* define initial position for triangle */
	wcPt2D verts[3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0} };

	glClear(GL_COLOR_BUFFER_BIT); // clear display window

	glColor3f(0.0, 0.0, 1.0); // set fill color to blue

	glViewport(0, 0, 300, 300);  // set left viewport
	triangle(verts);

	/* rotates triangle and display in right half of display window */
	glColor3f(1.0, 0.0, 0.0); // set fill color to red
	glViewport(300.0, 0, 300, 300); // set right viewport
	glRotated(90.0, 0.0, 0.0, 1.0); // rotate about z axis
	triangle(verts); // display red rotated triangle

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 300);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("split-screen example");

	init();
	glutDisplayFunc(displayFunc);

	glutMainLoop();
}