#pragma once
#ifndef _RANDOMLIST_H_
#define _RANDOMLIST_H_
/*
*To get m number from -n to n without repetition
*/
#include "cocos2d.h"
class RandomList
{
public:
	static std::vector<int> randmInt(int n, int m);
};
#endif // !_RANDOMLIST_H_
