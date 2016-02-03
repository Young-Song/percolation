#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "dsets.h"
#include "easypng.h"
#include <stack>
#include <queue>

class Percolation
{
	public:
	class site {
	public:
		bool rightWall;
		bool downWall;
		
		int x;
		int y;

		bool status;
	};

	int Width;
	int Height;

	site* sites;

	DisjointSets dset;

	void init(int width, int height, double p);
	bool canTravel(int x, int y, int dir);
	PNG* draw();
	int dsetIndex(int x, int y);
	void drawSite(PNG* img, int x, int y, int dir);
	bool percolate(PNG* pic);
	void drawColor(PNG* pic);
	//void setWall(int x, int y, int dir, bool exists);
	
};




#endif
