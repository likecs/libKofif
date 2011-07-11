
/* 
 * =====================================================================================
 *        Class:  LinkedPtrSkipList
 *  Description:  A Linked List implementation, designed to allow a string key associated
 * 		  with a pointer to an object by a specific template specified class. 
 * =====================================================================================
 */


#ifndef  LINKEDPTRSKIPLIST_INC
#define  LINKEDPTRSKIPLIST_INC

#include <string>;
using namespace std;

template < class LinkedType >
struct Node
{
	int 			Height;
	string 			Key;
	Node<LinkedType>* 	Next[];
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
				// There are no nodes prior to this one
				this->mpHead = CreateNode(Key,Object,path);
				this->mHeight = 1;
			} else if(path[0]->Next != NULL && path[0]->Next[0]->Key.compare(Key) == 0){
				// The next node has the same key as the vaue we are inerting-
				// replace the object we have with the new one
				path[0]->Next[0]->Object = Object;
			} else {
				CreateNode(&Key,Object,path);
			}

		}

		LinkedType* Find(string Key) 
		{
			return NULL;
		}
	private:
		Node<LinkedType>* CreateNode(string Key, LinkedType* Object, Node<LinkedType>** Path)
		{
			Node<LinkedType>* node = new Node<LinkedType>;
			node->Key = &Key;
			node->Object = Object;
			if(Path != NULL) {
				Node<LinkedType>** nextPath[this->mHeight];
				for(int index = 0; index < this->mHeight; index++) {
					nextPath[index] = Path[index];
					Path[index]->Next[index] = node;
				}

				node.Next = nextPath;
			} else {
				node.Next = NULL;
			}
			return node;
		}

		Node<LinkedType>** FindPathToKey(string& Key)
		{
			if(this->mHeight == 0 || this->mpHead == NULL) {
				return NULL;
			}

			Node<LinkedType>* path[this->mHeight];

			Node<LinkedType>* node = this->mpHead;
			for(int index = this->mHeight; ((index > 0) && (node->Next != NULL)); index--) {
				while(node->Key.compare(node->Next[index]->Key) > 0) {
					node = node->Next[index];
				}

				path[index-1]=node;

			}
			return NULL;
	
		}

		int 	mHeight;
		Node<LinkedType>*	mpHead;
}; /* -----  end of template class LinkedPtrSkipList  ----- */


#endif   /* ----- #ifndef LINKEDPTRSKIPLIST_INC  ----- */

