
#ifndef  LINKEDPTRSKIPLIST_INC
#define  LINKEDPTRSKIPLIST_INC

#define	DEBUGSKIPLIST1

#include <cstdlib>
#include <string>;
#include <iostream>;
using namespace std;

// The Maximum number of layers the skip list can reach
const int SKIPLIST_MAX_HEIGHT = 13;

/*
 * =====================================================================================
 *       Struct:  Node
 *  Description:  This struct represents a single object stored in the Skiplist.
 *  		  Each Object has:
 *  		  1. Next: An array of pointers to other nodes, each cell in the 
 *  		  array representing a single corisponding layer.
 *  		  2. Height: The height of the layer array.
 *  		  3. Key: The string key representing this object.
 *  		  4. Object: The actual Object pointer
 * =====================================================================================
 */
template < class LinkedType >
struct Node
{
	int 			Height;
	string 			Key;
	Node<LinkedType>** 	Next;
	LinkedType* 		Object;
};

/*
 * =====================================================================================
 *        Class: LinkedPtrSkipList
 *  Description: A Linked List implementation, designed to allow a string key associated
 *               with a pointer to an object by a specific template specified class. 
 * =====================================================================================
 */
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
			// If this is the first node ever - just create it and insert it
			if(this->mHeight == 0) {

				this->init();
				
				// There are no nodes prior to this one
				this->mpHead[0] = CreateNode(Key,Object);
				this->mHeight = 1;
			} else {
			
				// Temporary array to hold pointers to the nodes leading the path to the node that needs insertion
				Node<LinkedType>** nodePath = new Node<LinkedType>*[this->mHeight];

				Node<LinkedType>* currentNode = NULL;
				int layerIndex = this->mHeight-1;
				while(currentNode == NULL && layerIndex >= 0) {
					if(this->mpHead[layerIndex] != NULL) {
						int currentKeyComparison = this->mpHead[layerIndex]->Key.compare(Key);
#ifdef DEBUGSKIPLIST
						cout << this->mpHead[layerIndex]->Key << " compareed to " << Key << " is " << currentKeyComparison << endl;
#endif
						if(currentKeyComparison < 0) {
							// the first node in this layer is smaller than the Key
							currentNode = this->mpHead[layerIndex];
							nodePath[layerIndex] = currentNode;
						} else if(currentKeyComparison == 0) {
							// found another node with the same Key - replace it's Object and call it a day
							this->mpHead[layerIndex]->Object = Object;
							return;
						} else {
							// the first node in the layer is larger and the new Node should be inserted before it
							// We will place NULL in the path's index to signify that this layer should point at the
							// new node once it is inserted.
							nodePath[layerIndex] = NULL;
							
							// move down one layer and keep on searching for a value smaler than what we are inserting
							layerIndex--;
						}
					}

				}

				// find the path to the new node's proper place
				// Note that this loop uses the previously set layerIndex which will already point
				// to the layer index that contains the currentNote
				for(; layerIndex >= 0 && currentNode != NULL; layerIndex--) {
					while(currentNode->Next[layerIndex] != NULL && currentNode->Next[layerIndex]->Key.compare(Key) < 0) {
#ifdef DEBUGSKIPLIST
						cout << currentNode->Next[layerIndex]->Key << " is smaller than " << Key << endl;
#endif
						currentNode = currentNode->Next[layerIndex];
					}
					nodePath[layerIndex] = currentNode;
				}

				Node<LinkedType>* node = this->CreateNode(Key,Object,GenerateRandomHeight());
				
				int numberOfLayersToCopyFromPath = node->Height;
				if(node->Height > this->mHeight) {
					// this node has started a new layer in the skip list
					this->mpHead[this->mHeight] = node;
					this->mHeight++;
					numberOfLayersToCopyFromPath--; // don't exceed the size of the path array
				}

				
				for(layerIndex = 0; layerIndex < numberOfLayersToCopyFromPath; layerIndex++) {
					if(nodePath[layerIndex] == NULL) {
						// insert the node before any other node in the current layer
						node->Next[layerIndex] = this->mpHead[layerIndex];
						this->mpHead[layerIndex] = node;
					} else {
						node->Next[layerIndex] = nodePath[layerIndex]->Next[layerIndex];
						nodePath[layerIndex]->Next[layerIndex] = node;
					}
				}
			}
		}

		LinkedType* Find(string Key) 
		{
			return NULL;
		}

		void DebugPrint()
		{
			for(int n = this->mHeight-1; n >= 0; n--) {
				Node<LinkedType>* node = this->mpHead[n];
				cout << "|" << (n+1) << "|";
				while(node != NULL) {
					cout << "->" << node->Key;
					node = node->Next[n];
				}

				cout << "-|" << endl;
			}
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

		Node<LinkedType>* CreateNode(string Key, LinkedType* Object, int Height = 1) {
			Node<LinkedType>* node = new Node<LinkedType>();
			node->Key = Key;
			node->Object = Object;
			node->Height = Height;
			node->Next = new Node<LinkedType>*[Height];
			for(int skipLayer = 0; skipLayer < Height; skipLayer++) {
				node->Next[skipLayer] = NULL;
			}

#ifdef DEBUGSKIPLIST
			cout << "Create " << Key << " with height " << Height << endl;
#endif
			return node;
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

