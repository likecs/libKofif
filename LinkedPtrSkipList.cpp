
/* 
 * =====================================================================================
 *        Class:  LinkedPtrSkipList
 *  Description:  A Linked List implementation, designed to allow a string key associated
 * 		  with a pointer to an object by a specific template specified class. 
 * =====================================================================================
 */


#ifndef  LINKEDPTRSKIPLIST_INC
#define  LINKEDPTRSKIPLIST_INC

#include <cstdlib>
#include <string>;
using namespace std;

const int SKIPLIST_MAX_HEIGHT = 13;

template < class LinkedType >
struct Node
{
	int 			Height;
	string 			Key;
	Node<LinkedType>** 	Next;
	LinkedType* 		Object;
};

template < class LinkedType >
class LinkedPtrSkipList
{
	public:

		LinkedPtrSkipList () 
		{
			this->mHeight=0;
			this->mpHead = NULL;	
		}

		LinkedPtrSkipList ( const LinkedPtrSkipList &other ) 
		{
			this->mHeight=0;
			this->mpHead = NULL;	
		}

		~LinkedPtrSkipList () 
		{

		}

		LinkedPtrSkipList& operator = ( const LinkedPtrSkipList &other )
		{

		}

		void Insert(string Key, LinkedType* Object)
		{
			
			// Find where to insert it	
			Node<LinkedType>** path = this->FindPathToKey(Key);

			// Create a Node
			if(path == NULL) {
				this->init();
				
				// There are no nodes prior to this one
				this->mpHead[0] = CreateNode(Key,Object);
				this->mHeight = 1;
			} else if(path[0]->Next != NULL && path[0]->Next[0]->Key.compare(Key) == 0){
				// The next node has the same key as the vaue we are inerting-
				// replace the object we have with the new one
				path[0]->Next[0]->Object = Object;
			} else {
				this->CreateNode(Key,Object,path);
			}

		}

		LinkedType* Find(string Key) 
		{
			return NULL;
		}
	private:
		void init()
		{
			if(this->mpHead == NULL) {
				// Seed random bit generator
				srand ( time(NULL) );

				// Create head array to hold pointers to nodes
				this->mpHead = new Node<LinkedType>*[10]; //Define default size
				for(int index = 0; index < 10; index++) {
					this->mpHead[index] = NULL;
				}
			}
		}

		Node<LinkedType>* CreateNode(string Key, LinkedType* Object, Node<LinkedType>** Path = NULL)
		{
			Node<LinkedType>* node = new Node<LinkedType>();
			node->Key = Key;
			node->Object = Object;
			if(Path != NULL) {
				// Insert node into list
				int nodeHeight = this->GenerateRandomHeight();

				int recievedPathHeight = this->mHeight;
				if(nodeHeight > this->mHeight) {
					this->mpHead[nodeHeight] = node;
					this->mHeight++;
				}

				node->Next = new Node<LinkedType>*[this->mHeight];
				for(int index = 0; index < recievedPathHeight; index++) {
					node->Next[index] = Path[index];
					Path[index]->Next[index] = node;
				}
			} else {
				node->Next = new Node<LinkedType>*[1];
				node->Next[0] = NULL;
			}
			return node;
		}

		Node<LinkedType>** FindPathToKey(string& Key)
		{
			if(this->mHeight == 0 || this->mpHead == NULL) {
				return NULL;
			}

			Node<LinkedType>** path = new Node<LinkedType>*[this->mHeight];

			Node<LinkedType>* node = this->mpHead[this->mHeight-1]; //Get the heighest node
			if(this->mpHead[0]->Key.compare(Key) < 0) {
				path[0] = this->mpHead[0];
			} else {
				path[0] = NULL;
			}

			for(int index = this->mHeight - 1; ((index >= 0) && (node->Next != NULL)); index--) {
				while(node->Next[index]->Key.compare(Key) < 0) {
					node = node->Next[index];
				}

				path[index-1]=node;

			}
			return path;
	
		}

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  GenerateRandomHeight		 
		 *  Description:  The Linked list's power is rooted in the statistical nature by which
		 *  			new layers are inserted into the linked lists.
		 *  		  This method calculats a random height between 0 and the height of the
		 *  		  list. If its heigher than the current height a new layer will be added.
		 * =====================================================================================
		 */
		int GenerateRandomHeight()
		{
			// initialize the random bits
			static int bitsUpperBd = 0;
			static int bits;

			if (bitsUpperBd == 0) {
				// RAND_MAX is a constant defined in <cstdlib>. 
				// Its default value may vary between implementations but it is granted to be at least 32767.
				bitsUpperBd = RAND_MAX;

				// generate a random int value
				bits = rand();
			}

			// cycle through bits untill we reach a '1' bit, which
			// signifies the end of a cycle or we pass the current height
			int nextLevel = this->mHeight;

			// only allow the next level to be higher than the current highet
			// if we haven't yet reached the maximum height
			if(this->mHeight != SKIPLIST_MAX_HEIGHT) {
				nextLevel = this->mHeight + 1;
			}

			int b = 0;
			int height;
			for(height = 0; height < nextLevel  && b != 1; height++) {
				// compare the first bit. If it is '1' then we will end the loop here
				b = bits & 1;

				// shift the bits in 'bits' & the bits upper bound so that next time
				// we will get a different result
				bits >>= 1;
				bitsUpperBd >>= 1;
			}

			return height;
		}

		int 			mHeight;
		Node<LinkedType>**	mpHead;
}; /* -----  end of template class LinkedPtrSkipList  ----- */


#endif   /* ----- #ifndef LINKEDPTRSKIPLIST_INC  ----- */

