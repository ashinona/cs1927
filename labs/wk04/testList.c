// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
    printf("Enter some strings\n");
	DLList myList;
	myList = getDLList(stdin);
	putDLList(stdout,myList);
	assert(validDLList(myList));
	
	printf("\n=== Testing Insertion: Before ===\n");
	printf("Original: \n");
	putDLList(stdout,myList);
	printf("Current: %s\n",DLListCurrent(myList));
	printf("List Length: %d\n", DLListLength(myList));
	DLListBefore(myList, "THIS LINE WAS INSERTED BEFORE THE CURRENT NODE");
	printf("\nNewList: \n");
	putDLList(stdout,myList);
	printf("Current: %s\n",DLListCurrent(myList));
	printf("List Length: %d\n", DLListLength(myList));	

	printf("\n=== Testing Insertion: After ===\n");
	printf("Original: \n");
	putDLList(stdout,myList);
	printf("Current: %s\n",DLListCurrent(myList));
	printf("List Length: %d\n", DLListLength(myList));
	DLListAfter(myList,"THIS LINE WAS INSERTED AFTER THE CURRENT NODE");
	printf("\nNewList: \n");
	putDLList(stdout,myList);
	printf("Current: %s\n",DLListCurrent(myList));
	printf("List Length: %d\n", DLListLength(myList));	


	return 0;
}

// DLList.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, August 2014

#ifndef DLLIST_H
#define DLLIST_H

#include <stdio.h>
#include "DLList.h"

// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of strings (i.e. items are strings)

typedef struct DLListRep *DLList;

// create a new empty DLList
DLList newDLList();

// free up all space associated with list
void freeDLList(DLList);

// create an DLList by reading items from a file
// assume that the file is open for reading
DLList getDLList(FILE *);

// display list to file, one item per line
// assumes that the file is open for writing
void putDLList(FILE *, DLList);

// check sanity of a DLList (for testing)
int validDLList(DLList);

// return item at current position
char *DLListCurrent(DLList);

// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
int DLListMove(DLList, int);

// move to specified position in list
// i'th node, assuming first node has i==1
int DLListMoveTo(DLList, int);

// insert an item before current item
// new item becomes current item
void DLListBefore(DLList, char *);

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList, char *);

// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList);

// return number of elements in a list
int DLListLength(DLList);

// is the list empty?
int DLListIsEmpty(DLList);

#endif
