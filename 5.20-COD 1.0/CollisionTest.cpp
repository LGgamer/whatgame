#include "CollisionTest.h"
#include "cocos2d.h"

USING_NS_CC;

bool CollisionTest::isCollision(float x1, float y1, int w1, int h1,
	float x2, float y2, int w2, int h2)
{
	float hw1 = w1*0.5;
	float hw2 = w2*0.5;
	float hh1 = h1*0.5;
	float hh2 = h2*0.5;
	float xAmin = x1 + hw1;
	float xAmax = x1 - hw1;
	float yAmax = y1 + hh1;
	float yAmin = y1 - hh1;

	float xBmin = x2 + hw2;
	float xBmax = x2 - hw2;
	float yBmax = y2 + hh2;
	float yBmin = y2 - hh2;

	float xOverlap = 0;
	float yOverlap = 0;
	float impacetArea = 0;

	float dx = fabs(x1 - x2);
	float dy = fabs(y1 - y2);

	if (hw1 + hw2 >= dx)//A is at RHS of B, vice versa
	{
		xOverlap = fabs(hw1 + hw2 - dx) + 0.1;
		if (hh1 + hh2 > dy)
		{
			yOverlap = fabs(hh1 + hh2 - dy);
		}
		else
		{
			yOverlap = 0;
		}
	}

	impacetArea = fabs(xOverlap * yOverlap);
	if (impacetArea >= threshold)
		return true;
	else
		return false;
}