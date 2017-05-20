#ifndef _COLLISIONLIST_H_
#define _COLLISIONLIST_H_
#include <vector>


//PandS: Positoin and Size
class PandS
{
public:
	std::string name;
	float x;
	float y;
	int width;
	int height;
};

class CollisonList
{
public:

	std::vector<PandS> fixed;
	std::vector<PandS> changed;
	std::vector<PandS> items;

};

#endif