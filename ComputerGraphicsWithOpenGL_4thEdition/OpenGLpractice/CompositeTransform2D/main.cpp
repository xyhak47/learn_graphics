/**/

#include <GL\glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth = 600, winHeight = 600;

const GLdouble pi = 3.14159;

typedef GLfloat Matrix3x3 [3][3];

Matrix3x3 matComposite;

/* seet range for world coordinates */
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt2D
{
public:
	GLfloat x, y;
};

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void triangle(wcPt2D* verts)
{
	GLint k;

	glBegin(GL_TRIANGLES);
		for (k = 0; k < 3; k++)
		{
			glVertex2f(verts[k].x, verts[k].y);
		}
	glEnd();
}

void matrix3x3SetIndentity(Matrix3x3 matIndent3x3)
{
	GLint row, col;

	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			matIndent3x3[row][col] = (row == col);  // if row == col, return 1, else return 0
		}
	}
}

/* premultiply matrix mi times matrix m2, store result in m2 */
void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row, col;
	Matrix3x3 matTemp;

	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			matTemp[row][col] = m1[row][0] * m2[0][col] +
								m1[row][1] * m2[1][col] +
								m1[row][2] * m2[2][col];
		}
	}

	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			m2[row][col] = matTemp[row][col];
		}
	}
}

void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
	Matrix3x3 matScale;

	matrix3x3SetIndentity(matScale);

	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy) * fixedPt.y;

	/* concatenate matScale with the composite matrix */
	matrix3x3PreMultiply(matScale, matComposite);
}

void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
	Matrix3x3 matRot;

	matrix3x3SetIndentity(matRot);

	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = pivotPt.x * (1 - cos(theta));

	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = pivotPt.y * (1 - sin(theta));

	matrix3x3PreMultiply(matRot, matComposite);
}

void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTransl;

	matrix3x3SetIndentity(matTransl);

	matTransl[0][2] = tx;
	matTransl[1][2] = ty;

	matrix3x3PreMultiply(matTransl, matComposite);
}

/* using the composite matrix, calculate transformed coordinates */
void transformVerts2D(GLint nVerts, wcPt2D* verts)
{
	GLfloat temp;

	for (GLint k = 0; k < nVerts; k++)
	{
		temp =	matComposite[0][0] * verts[k].x +
						matComposite[0][1] * verts[k].y +
						matComposite[0][2];

		verts[k].y =	matComposite[1][0] * verts[k].x +
						matComposite[1][1] * verts[k].y +
						matComposite[1][2];

		verts[k].x = temp;
	}
}

void displayFunc()
{
	/* define initial position for triangle */
	GLint nVerts = 3;
	wcPt2D verts[3] = { { 50.0, 25.0 },{ 150.0, 25.0 },{ 100.0, 100.0 } };

	/* calculate position of triangle centroid */
	wcPt2D centroidPt;

	GLint k, xSum = 0, ySum = 0;

	for (k = 0; k < nVerts; k++)
	{
		xSum += verts[k].x;
		ySum += verts[k].y;
	}
	centroidPt.x = GLfloat(xSum) / GLfloat(nVerts);
	centroidPt.y = GLfloat(ySum) / GLfloat(nVerts);

	/* set geometric transformation parameters */
	wcPt2D pivPt, fixedPt;
	pivPt = centroidPt;
	fixedPt = centroidPt;

	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 0.5, sy = 0.5;
	GLdouble theta = pi / 2.0;

	glClear(GL_COLOR_BUFFER_BIT);  // clear display window

	glColor3f(0.0, 0.0, 1.0); // set initial fill coor to blue
	triangle(verts); // display blue triangle

	/* initialize composite matrix to identity */
	matrix3x3SetIndentity(matComposite); // here will not copy matrix, because it sent a pointer which point to the matrix

	/* construc composite matrix to triangle vertices */
	scale2D(sx, sy, fixedPt);
	rotate2D(pivPt, theta);
	translate2D(tx, ty);

	/* apply composite matrix to triangle verteices*/
	transformVerts2D(nVerts, verts);

	glColor3f(1.0, 0.0, 0.0); // set color for transform triangle
	triangle(verts);			// display red transformed triangle

	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Geometric Transformation Sequence");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}