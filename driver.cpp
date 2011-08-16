

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
	return obj;
}

string randString() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int size = (rand() % 10 ) + 1;
    string value = "";
    for (int i = 0; i < size; ++i) {
        value += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return value;
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
	list->Insert("Ded",CreateTestObj());
	list->Insert("Debil",CreateTestObj());
	list->Insert("Hello",CreateTestObj());
	list->Insert("Gambit",CreateTestObj());
	list->Insert("Zong$",CreateTestObj());
	list->Insert("zed",CreateTestObj());

	for(int n = 0; n < 10; n++) {

		list->Insert(randString(),CreateTestObj());
	}

	list->DebugPrint();

	MyObj* bag = list->Find("Bag");
	cout << endl << "Found the ID under the key Bag is:" << bag->ID;

	MyObj* gidi = list->Find("Gidi");
	if(gidi == NULL) {

		cout << endl << "Couldn't find anything under the Key Gidi." << endl;
	} else {
		cout << endl << "Found the ID under the key Gid is:" << gidi->ID << endl;
	}

	cout << endl << "Remove Debil" << endl;

	MyObj* ded = list->Remove("Debil",false);
	if(ded != NULL) {
		cout << endl << "Remove returned node " << ded->ID << endl;
	} else {
		cout << endl << "Ded wan't found!" << endl;
	}
	list->DebugPrint();

	if(list->Exists("Aag")) {
		cout << endl << "Aag exists!" << endl;
	} else {
		cout << endl << "Aag doesn't exist..." << endl;
	}
	
	if(list->Exists("Debil")) {
		cout << endl << "Debil exists!" << endl;
	} else {
		cout << endl << "Debil doesn't exist..." << endl;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
