#ifndef _CollisionTest_H_
#define _CollisionTest_H_
class CollisionTest
{
public:
	static const int threshold = 2000;

	static bool isCollision(float x1, float y1, int w1, int h1,
		float x2, float y2, int w2, int h2);
};
#endif // !_CollisionTest_H_
