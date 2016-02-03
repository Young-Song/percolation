#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H


#include <vector>
using namespace std;


//template<int>
class DisjointSets{

public:
	void addelements(int n);
	int find(int n);
	int parent(int n);
	void setunion(int x,int y);
	bool isBigger(int x, int y);

private:
	vector<int> index;






};


//#include "dsets.cpp"
#endif
