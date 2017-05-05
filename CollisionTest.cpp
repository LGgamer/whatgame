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

	/*if (xAmax <= xBmax && xAmax >= xBmin)
	{
		log("zuoyou");
		xOverlap = fabs(xAmax - xAmin);
		if (yAmin <= yBmin && yAmax <= yBmax && yBmin <= yAmax)
			yOverlap = fabs(yAmax - yBmin);
		else if (yAmax >= yBmax && yBmin <= yAmin && yBmax >= yAmin)
			yOverlap = fabs(yBmax - yAmin);
		else
			yOverlap = 0;
	}
	else if (xBmin >= xAmin && xBmax <= xAmax )
	{
		log("zuoyou2");
		xOverlap = fabs(xBmax - xBmin);
		if (yBmax <= yAmax && yAmin >= yBmin && yBmax >= yAmin)
			yOverlap = fabs(yBmax - yAmin);
		else if (yAmin <= yBmin && yAmax <= yBmax && yBmin <= yAmax)
			yOverlap = fabs(yAmax - yBmin);
		else
		{
			yOverlap = 0;
		}
	}
	else if (xAmax <= xBmax && xAmin <= xBmin && xAmax >= xBmin)
	{
		log("you");
		xOverlap = fabs(xAmax - xBmin);
		if (yAmax <= yBmax && yAmin <= yBmin && yAmax >= yBmin)
			yOverlap = fabs(yAmax - yBmin);
		else if (yAmax >= yBmax && yAmin >= yBmin && yBmax >= yAmin)
			yOverlap = fabs(yBmax - yAmin);
		else
			yOverlap = 0;
	}
	else if (xAmin >= xBmin && xAmax >= xBmax && xAmin <= xBmax)
	{
		log("zuo");
		xOverlap = fabs(xBmax - xAmin);
		if (yAmax <= yBmax && yAmin <= yBmin && yAmax >= yBmin)
			yOverlap = fabs(yAmax - yBmin);
		else if (yAmax >= yBmax && yAmin >= yBmin && yBmax >= yAmin)
			yOverlap = fabs(yBmax - yAmin);
		else
		{
			
			yOverlap = 0;
		}
	}*/
	impacetArea = fabs(xOverlap * yOverlap);
	log("A: %f", impacetArea);
	if (impacetArea >= threshold)
		return true;
	else
		return false;
}