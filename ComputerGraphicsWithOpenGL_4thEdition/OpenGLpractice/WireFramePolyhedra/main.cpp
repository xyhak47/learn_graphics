/**/
#include <GL\glut.h>
GLsizei winWidth = 500, winHeight = 500;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void displayWirePolyhedra()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);

	/* set viewing transformation */
	gluLookAt(5.0, 5.0, 5.0, 0, 0, 0, 0, 1, 0);

	/* scale cube and display as wire-frame parallelepiped */
	glScaled(1.5, 2.0, 1.0);
	glutWireCube(1.0);

	/* scale, translate ,and display wire-frame Dodecahedron */
	glScaled(0.8, 0.5, 0.8);
	glTranslated(-6, -5, 0);
	glutWireDodecahedron();

	/* translate and diaplay wire-frame tetrahedron */
	glTranslated(8.6, 8.6, 2.0);
	glutWireTetrahedron();

	/* translate and display wire-frame octahedron */
	glTranslated(-3, -1, 0);
	glutWireOctahedron();

	/* scale , translate , and display wire-frame icosahedron */
	glScaled(0.8, 0.8, 1.0);
	glTranslated(4.3, -2, 0.5);
	glutWireIcosahedron();
	
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1, 1, -1, 1, 2, 20);

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("wire frame polyhedra");

	init();
	glutDisplayFunc(displayWirePolyhedra);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}