

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include "LinkedPtrSkipList.cpp"

class MyObj
{
	public:
	int ID;
};

MyObj* CreateTestObj() {
	static int counter = 0;

	MyObj* obj = new MyObj();
	obj->ID = counter++;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	LinkedPtrSkipList<MyObj>* list = new LinkedPtrSkipList<MyObj>();
	list->Insert("A",CreateTestObj());
	list->Insert("B",CreateTestObj());
	list->Insert("C",CreateTestObj());
	list->Insert("E",CreateTestObj());
	list->Insert("D",CreateTestObj());
	list->Insert("Bag",CreateTestObj());
	list->Insert("Aag",CreateTestObj());
	list->Insert("ded",CreateTestObj());
	list->Insert("Ded",CreateTestObj());
	list->Insert("zed",CreateTestObj());


	list->DebugPrint();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
