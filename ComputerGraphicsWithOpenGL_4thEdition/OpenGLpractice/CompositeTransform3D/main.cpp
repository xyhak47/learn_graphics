/**/

#include <GL\glut.h>
#include <math.h>

struct wcPt3D
{
	GLfloat x, y, z;
};

typedef float Matrix4x4[4][4];

Matrix4x4 matComposite;

/* construct the 4x4 indentity matrix */
void matrix4X4SetIndentity(Matrix4x4 matIndent4x4)
{
	GLint row, col;

	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			matIndent4x4[row][col] = (row == col);
		}
	}
}

/* premultiply matrix m1 by matrix m2, store result in m2 */
void matrix4x4PreMultity(Matrix4x4 m1, Matrix4x4 m2)
{
	GLint row, col;
	Matrix4x4 matTemp;

	for (row = 0; row < 4; row++)
	{
		for (col = 0; row < 4; row++)
		{
			matTemp[row][col] = 
				m1[row][0] * m2[0][col] +
				m1[row][1] * m2[1][col] +
				m1[row][2] * m2[2][col] +
				m1[row][3] * m2[3][col];
		}
	}

	for (row = 0; row < 4; row++)
	{
		for (col = 0; row < 4; row++)
		{
			m2[row][col] = matTemp[row][col];
		}
	}
}

/* procedure for generating 3D translation matrix */
void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	Matrix4x4 matTransl3D;

	/* initialize translate matrix to identity */
	matrix4X4SetIndentity(matTransl3D);

	matTransl3D[0][3] = tx;
	matTransl3D[1][3] = ty;
	matTransl3D[2][3] = tz;

	/* concatenate matTransl3D with composite matrix */
	matrix4x4PreMultity(matTransl3D, matComposite);
}

/* procedure for generating a quaternion rotation matrix */
void rotate3D(wcPt3D p1, wcPt3D p2, float radianAngle)
{
	Matrix4x4 matQuatRot;

	float axisVectLength = sqrt(
		(p2.x - p1.x) * (p2.x - p1.x) +
		(p2.y - p1.y) * (p2.y - p1.y) +
		(p2.z - p1.z) * (p2.z - p1.z));

	float cosA = cosf(radianAngle);
	float oneC = 1 - cosA;
	float sinA = sinf(radianAngle);
	float ux = (p2.x - p1.x) / axisVectLength;
	float uy = (p2.y - p1.y) / axisVectLength;
	float uz = (p2.z - p1.z) / axisVectLength;


	/* set up translation matrix for moving p1 to origin and concatenate translation matrix with matComposite */
	translate3D(-p1.x, -p1.y, -p1.z);

	/* initialize maQuatRot identity matrix */
	matrix4X4SetIndentity(matQuatRot);

	matQuatRot[0][0] = ux*ux*oneC + cosA;
	matQuatRot[0][1] = ux*ux*oneC - uz*sinA;
	matQuatRot[0][2] = ux*ux*oneC + uy*sinA;
	matQuatRot[1][0] = ux*ux*oneC + uz*sinA;
	matQuatRot[1][1] = ux*ux*oneC + cosA;
	matQuatRot[1][2] = ux*ux*oneC - uz*sinA;
	matQuatRot[2][0] = ux*ux*oneC - uy*sinA;
	matQuatRot[2][1] = ux*ux*oneC + ux*sinA;
	matQuatRot[2][2] = ux*ux*oneC + cosA;

	/* concatenate matQuatRot with composite matrix */
	matrix4x4PreMultity(matQuatRot, matComposite);

	/* construct inverse translation matrix for p1 and concatenate with composite matrix */
	translate3D(p1.x, p1.y, p2.z);
}

/* procedure for generation a 3D scaling matrix */
void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
	Matrix4x4 matScale3D;

	/* initialize scaling matrix to identity */
	matrix4X4SetIndentity(matScale3D);

	matScale3D[0][0] = sx;
	matScale3D[0][3] = (1 - sx) * fixedPt.x;
	matScale3D[1][1] = sy;
	matScale3D[1][3] = (1 - sy) * fixedPt.y;
	matScale3D[2][2] = sz;
	matScale3D[2][3] = (1 - sz) * fixedPt.z;

	/* concatenate matScale3D with composite matrix */
	matrix4x4PreMultity(matScale3D, matComposite);
}

void displayFunc()
{
	/* input object description */
	/* input translation, rotation and scaling parameters */

	/* set up 3D viewing-transformation routines */

	/* initialize matComposite to indenity matrix */
	matrix4X4SetIndentity(matComposite);

	/* invoke transformation routines in the order they are to be applied */
	//rotate3D(p1, p2, radianAngle);
	//scale3D(sx, sy, sz, fixedPt);
	//translate3D(tx, ty, tz);
}

void main(int argc, char** argv)
{

}