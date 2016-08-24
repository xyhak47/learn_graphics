/**/
#include <GL\glut.h>

class screenPt
{
private:
	GLint x, y;

public:
	screenPt() : x(0), y(0) {}

	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}

	GLint getx() const { return x; }
	GLint gety() const { return y; }

	void incrementx() { x++; }
	void decrementy() { y--; }
};

void setPixel(GLint xCoord, GLint yCoord)
{
	glBegin(GL_POINTS);
		glVertex2i(xCoord, yCoord);
	glEnd();
}

void circleMidPoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius; // initial value for midpoint parameter

	circPt.setCoords(0, radius);

	circlePlotPoints(xc, yc, circPt); // calculate next point and plot in each octant ∞À∑÷‘≤

	while (circPt.getx() < circPt.gety())
	{
		circPt.incrementx();

		if (p < 0)
		{
			p += 2 * circPt.getx() + 1;
		}
		else
		{
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety() + 1);
		}

		circlePlotPoints(xc, yc, circPt);
	}
}

// plot the initial point in each circle quadrant œÛœﬁ
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	// up and down
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());

	// left and right
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}


inline int round(const float a)
{
	return int(a + 0.5);
}

void ellipseMidPoint(int xCenter, int yCenter, int Rx, int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;

	ellipsePlotPoints(xCenter, yCenter, x, y);

	/* region 1 */
	p = round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py)
	{
		x++;
		px += twoRy2;
		if (p < 0)
		{
			p += px + Ry2;
		}
		else
		{
			y--;
			py -= twoRx2;
			p += px - py + Ry2;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	/* region 2 */
	p = round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0)
	{
		y--;
		py -= twoRx2;
		if (p > 0)
		{
			p += -py + Rx2;
		}
		else
		{
			x++;
			px += twoRy2;
			p += px - py + Rx2;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}