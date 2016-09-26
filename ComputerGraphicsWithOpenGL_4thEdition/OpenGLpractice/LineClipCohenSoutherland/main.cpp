/**/

#include <GL\glut.h>

struct wcPt2D
{
	GLfloat x, y;
};

const GLint winLeftBitCode = 0x1;	// 0001
const GLint winRightBitCode = 0x2;	// 0010
const GLint winBottomBitCode = 0x4;	// 0100
const GLint winTopBitCode = 0x8;	// 1000

inline GLint accept(GLint code1, GLint code2)
{
	return !(code1 | code2);
}

inline GLint reject(GLint code1, GLint code2)
{
	return code1 & code2;
}

inline GLint inside(GLint code)
{
	return !code;
}

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax)
{
	GLubyte code = 0x00; // 0000

	if (pt.x < winMax.x)	code |= winLeftBitCode;
	if (pt.x > winMax.x)	code |= winRightBitCode;
	if (pt.y < winMin.y)	code |= winBottomBitCode;
	if (pt.y > winMax.y)	code |= winTopBitCode;
	
	return code;
}

void swapPts(wcPt2D* p1, wcPt2D* p2)
{
	wcPt2D tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void swapCode(GLubyte* c1, GLubyte* c2)
{
	GLubyte tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
	GLubyte code1, code2;
	GLint done = false, plotline = false;
	GLfloat m;

	while (!done)
	{
		code1 = encode(p1, winMin, winMax);
		code2 = encode(p2, winMin, winMax);

		if (accept(code1, code2)) // both in 0000
		{
			done = true;
			plotline = true;
		}
		else if (reject(code1, code2)) // both in the same area out side
		{
			done = true;
		}
		else
		{
			/* label the endpoint outside the display window as p1 */
			if (inside(code1))
			{
				swapPts(&p1, &p2);
				swapCode(&code1, &code2);
			}

			/* use slope m to find line-clipEdge intersection */
			if (p2.x != p1.x)
			{
				m = (p2.y - p1.y) / (p2.x - p1.x);
			}

			if (code1 & winLeftBitCode)
			{
				p1.y += (winMin.x - p1.x) * m;
				p1.x = winMin.x;
			}
			else if (code1 & winRightBitCode)
			{
				p1.y += (winMax.x - p1.x) * m;
				p1.x = winMax.x;
			}
			else if (code1 & winBottomBitCode)
			{
				/* need to update p1.x for nonvertical lines only */
				if (p2.x != p1.x)
				{
					p1.x += (winMin.y - p1.y) / m;
				}
				p1.y = winMin.y;
			}
			else  //if (code1 & winTopBitCode)
			{
				if (p2.x != p1.x)
				{
					p1.x += (winMax.y - p1.y) / m;
				}
				p1.y = winMax.y;
			}
		}
	}
}


void main(int argc, char** argv)
{

}
