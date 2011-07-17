

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include "LinkedPtrSkipList.hpp"

class MyObj
{
	public:
	int ID;
};


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	LinkedPtrSkipList<MyObj>* list = new LinkedPtrSkipList<MyObj>();
	MyObj* obj = new MyObj();
	obj->ID = 1;
	string keyA = "A";
	list->Find(keyA);
	list->Insert(keyA,obj);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
