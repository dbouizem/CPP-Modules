#include "Point.hpp"

static Fixed areaSign(Point const p1, Point const p2, Point const p3)
{
	return ((p1.getX() - p3.getX()) * (p2.getY() - p3.getY())
		- (p2.getX() - p3.getX()) * (p1.getY() - p3.getY()));
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed sign1;
	Fixed sign2;
	Fixed sign3;
	bool hasNegative;
	bool hasPositive;

	sign1 = areaSign(point, a, b);
	sign2 = areaSign(point, b, c);
	sign3 = areaSign(point, c, a);
	if (sign1 == Fixed(0) || sign2 == Fixed(0) || sign3 == Fixed(0))
		return (false);
	hasNegative = (sign1 < Fixed(0)) || (sign2 < Fixed(0)) || (sign3 < Fixed(0));
	hasPositive = (sign1 > Fixed(0)) || (sign2 > Fixed(0)) || (sign3 > Fixed(0));
	return (!(hasNegative && hasPositive));
}
