#include "RandomList.h"

std::vector<int> RandomList::randmInt(int n, int m)
{
	std::vector<int> result;
	for (int i = -n; i <= n; i++) 
	{
		
		if (rand() % (n+1 - i)<m) 
		{
			result.push_back(i);
			m--;
		}
	}
	return result;
}