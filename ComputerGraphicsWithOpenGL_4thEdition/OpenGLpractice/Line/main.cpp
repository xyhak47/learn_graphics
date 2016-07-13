

#include <GL/glut.h>

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set display-window color to white
	
	glMatrixMode(GL_PROJECTION); // set projection parameters
	gluOrtho2D(0.0, 200, 0.0, 150);
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);  // clear display window

	glColor3f(0.0, 0.4, 0.2); // set line segment color to green
	glBegin(GL_LINES);
		glVertex2i(180, 15);  // specify line-segment geometry
		glVertex2i(10, 145);
	glEnd();

	glFlush(); // process all opengl routines as quickly as possible
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); 	// Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowPosition(50, 100); // set top-left display window position
	glutInitWindowSize(400, 300); // set display window width and height
	glutCreateWindow(" line "); // create display window

	init();   // execute initialization procedure
	glutDisplayFunc(lineSegment); // send graphics to display window
	glutMainLoop(); // display everything and wait
}