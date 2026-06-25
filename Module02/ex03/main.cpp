#include "Point.hpp"
#include <iostream>

static bool samePoint(Point const point, float x, float y)
{
	return (point.getX() == Fixed(x) && point.getY() == Fixed(y));
}

static char gridChar(Point const a, Point const b, Point const c,
	Point const pointToShow, int x, int y)
{
	Point point((float)x, (float)y);

	if (samePoint(pointToShow, (float)x, (float)y))
		return ('P');
	if (samePoint(a, (float)x, (float)y))
		return ('A');
	if (samePoint(b, (float)x, (float)y))
		return ('B');
	if (samePoint(c, (float)x, (float)y))
		return ('C');
	if (bsp(a, b, c, point))
		return ('*');
	return ('.');
}

static void drawTriangle(Point const a, Point const b, Point const c,
	Point const point)
{
	int x;
	int y;

	std::cout << std::endl;
	std::cout << "Visualisation:" << std::endl;
	for (y = 5; y >= 0; y--)
	{
		std::cout << y << " | ";
		for (x = 0; x <= 5; x++)
			std::cout << gridChar(a, b, c, point, x, y) << ' ';
		std::cout << std::endl;
	}
	std::cout << "    ------------" << std::endl;
	std::cout << "    0 1 2 3 4 5" << std::endl;
	std::cout << std::endl;
	std::cout << "A/B/C = triangle vertices" << std::endl;
	std::cout << "P     = tested point" << std::endl;
	std::cout << "*     = inside according to bsp()" << std::endl;
	std::cout << ".     = outside, edge, or vertex" << std::endl;
	std::cout << std::endl;
}

static const char* boolToBspResult(bool value)
{
	if (value)
		return ("true / inside");
	return ("false / not strictly inside");
}

static void showCase(Point const a, Point const b, Point const c,
	Point const point, const char* subjectCase, const char* reason)
{
	bool result;

	result = bsp(a, b, c, point);
	std::cout << "Case: " << subjectCase << std::endl;
	std::cout << "Point P = (" << point.getX() << ", " << point.getY() << ")"
		<< std::endl;
	std::cout << "Why: " << reason << std::endl;
	std::cout << "bsp(P) = " << boolToBspResult(result) << std::endl;
	drawTriangle(a, b, c, point);
}

int main(void)
{
	Point a(0.0f, 0.0f);
	Point b(5.0f, 0.0f);
	Point c(0.0f, 5.0f);

	std::cout << "Triangle used for all tests:" << std::endl;
	std::cout << "A = (0, 0), B = (5, 0), C = (0, 5)" << std::endl;
	std::cout << std::endl;
	std::cout << "The subject asks these 4 minimum cases:" << std::endl;
	std::cout << "1. true  if the point is inside" << std::endl;
	std::cout << "2. false if the point is outside" << std::endl;
	std::cout << "3. false if the point is on an edge" << std::endl;
	std::cout << "4. false if the point is on a vertex" << std::endl;
	std::cout << std::endl;

	showCase(a, b, c, Point(1.0f, 1.0f),
			"1. point inside the triangle",
			"P is strictly between the three edges.");
	std::cout << std::endl;

	showCase(a, b, c, Point(5.0f, 5.0f),
			"2. point outside the triangle",
			"P is outside the area delimited by A, B and C.");
	std::cout << std::endl;

	showCase(a, b, c, Point(2.0f, 0.0f),
			"3. point on an edge",
			"P is on edge A -> B, so it is not strictly inside.");
	std::cout << std::endl;

	showCase(a, b, c, Point(0.0f, 0.0f),
			"4. point on a vertex",
			"P is exactly on vertex A, so it is not strictly inside.");
	return (0);
}
