
#include <iostream>
#include "dsets.h"
#include "percolation.h"
#include "easypng.h"

int main()
{
    //get input size and probability from user
    int size;
	double probability;
    cout<<"Please enter an integer as size:\n";
    cin>>size;
    cout<<"Please enter a decimal number between 0 and 1 as percolation probability\n";
    cin>>probability;
    if(size<=0 || probability <0 || probability >1)
    {
        cout<<"invalid out put"<<endl;
        return 0;
    }

	//default testing:
	//size= 30;
	//probability=0.5;
   Percolation p;
   p.init(size,size,probability);
   std::cout << "percoaltion init complete" << std::endl;

   PNG* unsolved = p.draw();
   unsolved->writeToFile("BondPercolation.png");
  
   std::cout << "percolation map complete" << std::endl;
  
   // result indicates whether it percolates or not
   bool result = p.percolate(unsolved);
   unsolved->writeToFile("BondPercolationWithPath.png");
   std::cout << "Percolation with path complete" << std::endl;

	delete unsolved;

	if(result)
		cout<<"It does percolate!"<<endl;
	else
		cout<<"It does NOT percolate!"<<endl;

   
   return 0;

}

