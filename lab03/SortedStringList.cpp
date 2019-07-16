// SortedStringList.cpp  -- Implementation file for ADT SortedList (Pointer-based implementation)
// Revised 2019-02-14


#include "SortedStringList.h"
#include <iostream>
#include <exception>

using namespace std;

// Constructor

SortedStringList::SortedStringList() 
{
	header = new DListNode;
	trailer = new DListNode;
	header->prev = NULL;
	header->next = trailer;
	trailer->prev = header;
	trailer->next = NULL;
	numItems = 0;
	header->item = "!!-Header node";
	trailer->item = "~~-Trailer node";
} // end (Default) Constructor

// List Operations:

bool SortedStringList::isEmpty() const
// Returns true is the list is empty
{
	return bool(size() == 0);
} // end isEmpty


int SortedStringList::size() const
// Returns the number of items in the list
{
	return numItems;
} // end size


void SortedStringList::add(ListItemType newItem) //not working
//                         IN
// Inserts newItem into its proper position in a sorted list.
{
	// use locateIndex to find the index of where newItem should go
	int index = locateIndex(newItem);
	// use find to return a pointer to the proper insertion point
	DListNode *curr = find(index);

	struct DListNode *newNode = new DListNode(); //creating the new node
	newNode->item = newItem;
	//move pointers around
	curr->prev->next = newNode; 
	newNode->prev = curr->prev;
	curr->prev = newNode;
	newNode->next = curr;

	// update the size of the list
	numItems++;
	
} // end insert


void SortedStringList::remove(int index)
//                            IN
// Removes the item at position index of a sorted list,
//     if 1 <= index <= size(); otherwise, throws an exception
{
	if ((index>=1) && (index<=size()))
	{
		// use find to return a pointer to node to delete
		DListNode *badNode = find(index);
		// update the pointers and delete the node
		badNode->prev->next = badNode->next;
		badNode->next->prev = badNode->prev;
		badNode->next = nullptr;
		badNode->prev = nullptr;
		delete badNode;
		// update the size of the list
		numItems--;
	}
	else
	{
		throw "Bad index or List empty on remove()";
	}
}
// end remove

void SortedStringList::get(int index, ListItemType& dataItem) const // DO THIS
//                         IN         OUT
// Retrieves the item at position index of a sorted list,
// if 1 <= index <= size(); otherwise, throws an exception
	
{

	if ((index>=1) && (index<=size()))
	{
		// use find to return a pointer to the node
		DListNode *node = find(index);
		dataItem = node->item;
	}
	else
		throw "Bad index or List empty on get()";
} // end get

void SortedStringList::removeAll() // DO THIS
// Removes all the items in the list.
{
	int iterations = numItems;
	// iterate through the list, removing the items one at a time
	for(int i = 0; i < iterations; i++)
	{
		remove(1);
	}
	//then remove the head
	delete header;
	header = nullptr;


} // end remove

int SortedStringList::locateIndex(ListItemType item)	const
 // Returns the position where the item belongs or exists in a sorted list.
{

	DListNode *nodePtr = header;
	int index = 0;
	do
	{
		nodePtr = nodePtr->next;
		index++;
	} 	while( nodePtr != trailer && (item.compare(nodePtr->item) > 0));
	return index;
	
} // end locateIndex

// Private function:

SortedStringList::DListNode *SortedStringList::find(int index)const 
{
	// This function returns a pointer to the node at the referenced index.
	// If used in an insertion, the pointer is to the node which will become the successor.
	DListNode *nodePtr;

	if (index >= 1 && index <= size()+1)
	{
		nodePtr = header->next;
		for (int i=1; i < index; i++)
		{
			nodePtr = nodePtr->next;
		}
		return nodePtr;
	}
	else
	{
		throw "not found";
	}		
} // end find

// This function is not in the specifications, but you may find it useful for debugging purposes.
void SortedStringList::display() const
{
	DListNode *p = header;
	while (p != NULL)
	{
		cout << p->item << endl;
		p = p->next;
	}
}

// End of implementation file.