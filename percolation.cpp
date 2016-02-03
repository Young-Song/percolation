/*  This is a bond percolation simulation. 

	Usage: ./testpercolation <size> <probability>

	where size represents the size of the  n X n lattice and probability is the percolation probability
	for each bond.

 	Within each cell, there are two bonds connecting to its "East" neighbor and "South" neighbor. Each bond has the same though independent probability of being open

	dset, easypng files imported from cs225 data structure course at university of illinois 
*/

#include "percolation.h"
void Percolation:: init(int width,int height,double p)
{
	int probability = (int)(p*100);
	cout<<"probability is: "<<probability<<"%"<<endl;
	srand(time(0));// pseudo random

Width=width;
Height=height;

sites=new site[width*height];

for(int i=0;i<width;i++)
{
	for(int j=0;j<height;j++)
	{
		sites[dsetIndex(i,j)].rightWall=true;	// exist
		sites[dsetIndex(i,j)].downWall=true;
		sites[dsetIndex(i,j)].status=false;
		//sites[dsetIndex(i,j)].dist=0;
		//sites[dsetIndex(i,j)].path=NULL;
	}
}

// the first site--- center
//	sites[dsetIndex(Width/2,0)].rightWall=true;
//	sites[dsetIndex(Width/2,0)].downWall=true;
// the last row:
	for (int i=0;i<Width;i++)
	{
		sites[dsetIndex(i,Height-1)].downWall=false;
		sites[dsetIndex(i,Height-1)].status=false;
	}

//DisjointSets dset;
dset.addelements(width*height);//there are width*height vertices in total

///index of (x,y) in the dset = y*width+x;

int xCur=0;
int yCur=0;


//the first time
for(int i=0;i<width;i++)
{
	for(int j=0;j<height;j++)// (height-1)  and (width-1) because they are on the edge
	{
		sites[dsetIndex(i,j)].x=i;
		sites[dsetIndex(i,j)].y=j;
	if(random()%100<=probability){
		if(j!=height-1){
			sites[dsetIndex(i,j)].downWall=false;//delete the down wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i,j+1));//set union
		}
	}
	if(random()%100<=probability){
		if(i!=width-1){
			sites[dsetIndex(i,j)].rightWall=false;//delete the wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i+1,j));//set union
		
		}
	}
	}
}

//delete the rest
/*
for(int i=0;i<width-1;i++)
{
	for(int j=0;j<height-1;j++)// (height-1)  and (width-1) because they are on the edge
	{

		if(j!=height-1){
		if(dset.find(dsetIndex(i,j))!=dset.find(dsetIndex(i,j+1)))// no cycle after delete down wall
		{
			sites[dsetIndex(i,j)].downWall=false;//delete the down wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i,j+1));//set union
		}
		}

		if(i!=width-1){
		if(dset.find(dsetIndex(i,j))!=dset.find(dsetIndex(i+1,j)))//no cycle after delete right wall
		{
			sites[dsetIndex(i,j)].rightWall=false;//delete the wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i+1,j));//set union
		}
		}
	}
}
*/

}


int Percolation::dsetIndex(int x, int y)
{
return y*Width+x;

}

bool Percolation::canTravel(int x, int y, int dir)
{
//on the edges:
if(x==0 && dir==2)
	return false;
if( y==0 && dir==3)
	return false;
if(x==Width-1 && dir==0)
	return false;
if(y==Height-1 && dir==1)
	return false;

if(dir==0)
{
if(sites[dsetIndex(x,y)].rightWall)
	return false;
}

if(dir==1)
{
if(sites[dsetIndex(x,y)].downWall)
	return false;
}

if(dir==2)
{
if(sites[dsetIndex(x-1,y)].rightWall)
	return false;
}

if(dir==3)
{
if(sites[dsetIndex(x,y-1)].downWall)
	return false;
}


return true;
}


bool Percolation::percolate(PNG* pic)
{

	queue<site> q;
	q.push(sites[dsetIndex(Width/2,0)]);
	
	site* cur;
	while(!q.empty())	
	{
	
		cur=&q.front();
		q.pop();
		int x=cur->x;
		int y=cur->y;

		if(canTravel(x,y,0) && sites[dsetIndex(x+1,y)].status==false)
		{
			//sites[dsetIndex(x+1,y)].dist=sites[dsetIndex(x,y)].dist+1;
			//sites[dsetIndex(x+1,y)].path=&sites[dsetIndex(x,y)];
			sites[dsetIndex(x+1,y)].status=true;
			q.push(sites[dsetIndex(x+1,y)]);
			//drawSite(pic,x,y,0);
		}	

		if(canTravel(x,y,1) && sites[dsetIndex(x,y+1)].status==false)
		{
			//sites[dsetIndex(x,y+1)].dist=sites[dsetIndex(x,y)].dist+1;
			//sites[dsetIndex(x,y+1)].path=&sites[dsetIndex(x,y)];
			sites[dsetIndex(x,y+1)].status=true;
			q.push(sites[dsetIndex(x,y+1)]);
			//drawSite(pic,x,y,1);
		}	

		if(canTravel(x,y,2) && sites[dsetIndex(x-1,y)].status==false)
		{
			//sites[dsetIndex(x-1,y)].dist=sites[dsetIndex(x,y)].dist+1;
			//sites[dsetIndex(x-1,y)].path=&sites[dsetIndex(x,y)];
			sites[dsetIndex(x-1,y)].status=true;
			q.push(sites[dsetIndex(x-1,y)]);
			//drawSite(pic,x,y,2);
		}	

		if(canTravel(x,y,3) && sites[dsetIndex(x,y-1)].status==false)
		{
			//sites[dsetIndex(x,y-1)].dist=sites[dsetIndex(x,y)].dist+1;
			//sites[dsetIndex(x,y-1)].path=&sites[dsetIndex(x,y)];
			sites[dsetIndex(x,y-1)].status=true;
			q.push(sites[dsetIndex(x,y-1)]);
			//drawSite(pic,x,y,3);
		}	
		sites[dsetIndex(x,y)].status=true;

		
	}//while

	//site* longest;
	//longest=&sites[dsetIndex(0,Height-1)];
	//int best=longest->dist;
	bool result=false;
	
	for(int i=0;i<Width;i++)
	{
		
		if(dset.find(dsetIndex(i,Height-1)) == dset.find(dsetIndex(Width/2,0))  ) 
		{	
			q.push(sites[dsetIndex(i,Height-1)]);
			sites[dsetIndex(i,Height-1)].status=true;
			result= true;
		}
		
	}

	drawColor(pic);
	return result;
}


PNG* Percolation::draw()
{
PNG* result=new PNG(Width*10+1,Height*10+1);

	///frame
	// the first row
	for(int i=0;i<Width*10+1;i++)
	{
		(*result)(i,0)->red=255; 
		(*result)(i,0)->green=255; 
		(*result)(i,0)->blue=255; 
	}

	//two edges 
	for(int j=0;j<Height*10+1;j++)
	{
		(*result)(0,j)->red=0;
		(*result)(0,j)->green=0;
		(*result)(0,j)->blue=0;

		(*result)((Width)*10,j)->red=0;
		(*result)((Width)*10,j)->green=0;
		(*result)((Width)*10,j)->blue=0;
	}

	//sites 
	for(int i=0;i<Width;i++)
	{
		for(int j=0;j<Height;j++)
		{
			if(sites[dsetIndex(i,j)].rightWall)//right bond
			{
				for(int k=0;k<10;k++)
				{
					(*result)( (i+1)*10,j*10+k)->red=0;
					(*result)( (i+1)*10,j*10+k)->green=0;
					(*result)( (i+1)*10,j*10+k)->blue=0;
				}

			}

		
			if(sites[dsetIndex(i,j)].downWall)//down bond
			{
				for(int k=0;k<10;k++)
				{
					(*result)(i*10+k,(j+1)*10)->red=0;
					(*result)(i*10+k,(j+1)*10)->green=0;
					(*result)(i*10+k,(j+1)*10)->blue=0;
				}
			}
		}		
	}

	return result;
}

void Percolation::drawColor(PNG* pic)
{
	for ( int i=0 ;i< Width; i++)
	{	for(int j =0;j<Height; j++)
		{
			for(int k=0;k<4;k++)//k stands for direction  
			{	
				if(canTravel(i,j,k) && dset.find(dsetIndex(i,j))==dset.find(dsetIndex(Width/2,0)) )
					drawSite(pic,i,j,k);

			}
		}
	}


}

void Percolation::drawSite(PNG * pic, int x, int y,int dir)
{

	if(dir==0)
	{
		for(int k=0;k<=5;k++)
		{
			(*pic)(x*10+5+k,y*10+5)->red=255;
			(*pic)(x*10+5+k,y*10+5)->green=0;
			(*pic)(x*10+5+k,y*10+5)->blue=0;
		}	

	}	

	if(dir==1)
	{
		for(int k=0;k<=5;k++)
		{
			(*pic)(x*10+5,y*10+5+k)->red=255;
			(*pic)(x*10+5,y*10+5+k)->green=0;
			(*pic)(x*10+5,y*10+5+k)->blue=0;
		}		

	}	

	if(dir==2)
	{
		for(int k=0;k<=5;k++)
		{
			(*pic)(x*10+5-k,y*10+5)->red=255;
			(*pic)(x*10+5-k,y*10+5)->green=0;
			(*pic)(x*10+5-k,y*10+5)->blue=0;
		}	

	}	

	if(dir==3)
	{
		for(int k=0;k<=5;k++)
		{
			(*pic)(x*10+5,y*10+5-k)->red=255;
			(*pic)(x*10+5,y*10+5-k)->green=0;
			(*pic)(x*10+5,y*10+5-k)->blue=0;
		}		

	}	

}
