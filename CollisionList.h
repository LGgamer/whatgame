#ifndef _COLLISIONLIST_H_
#define _COLLISIONLIST_H_
//#include "cocos2d.h"
#include <vector>

//USING_NS_CC;
//Positoin and Size
class PandS// : public Ref
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
	//CollisonList();
	//~CollisonList();
	
	std::vector<PandS> fixed;
	std::vector<PandS> changed;

};

#endif