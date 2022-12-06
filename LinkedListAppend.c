// Lab 8: Dynamic array implemented using a linked list.
// UIC CS 211, Fall 2022, Esat Duman 
#include <stdio.h>
#include <stdlib.h>

#define true 1         // Make true a synonym for 1
const int Delta = 3;   // Array growth increment

typedef struct Node *NodePtr;  // NodePtr is a synonym for: struct Node *
struct Node {
    int data;        // The data stored at the node
    int index;       // Index position of this node, when viewed as array
    NodePtr pNext;   // Pointer to the next node
};


//-------------------------------------------------
void displayArray(  NodePtr pCurrent)  // Pointer to the first list Node
{
    // Display the index values stored on the array nodes.
    printf("Array indices: ");
    NodePtr pTemp = pCurrent;    // make a copy, so original can still be used below.
    while( pTemp != NULL) {
      // Don't print the sentinel Node value
      if( pTemp->data != -1) {
        printf("%3d", pTemp->index);
      }
      pTemp = pTemp->pNext;
    }
    printf("\n");
    
    // Display the numbers stored on the array nodes.
    printf("       values: ");
    while( pCurrent != NULL) {
      // Don't print the sentinel Node value
      if( pCurrent->data != -1) {
        printf("%3d", pCurrent->data);
      }
      pCurrent = pCurrent->pNext;
    }
    printf("\n");
} //end displayArray(..)


//----------------------------------------------------
// Find and return the pointer to the nth Node on the list.
// Return NULL if the index value we are searching for is
// not found.
NodePtr findNthNode(
            NodePtr pCurrent,   // Starts at head of list
            int indexToFind)    // Index value we are looking for
{
    // Advance past the sentinel Node to the first Node, if there is one.
    if( pCurrent != NULL && pCurrent->index == -1) {
        pCurrent = pCurrent->pNext;
    }
    
    // Iterate down the list looking for the indexToFind.
    // Make sure we stop at the end of the list, in case indexToFind
    // is larger than the index at the end of the list.
    while( pCurrent != NULL && pCurrent->index < indexToFind) {
        // Advance pCurrent to point to next node
        pCurrent = pCurrent->pNext;
    }
    
    // Return pointer to the Node where index was found, or NULL if not found.
    if( pCurrent != NULL && indexToFind == pCurrent->index) {
        return pCurrent;
    }
    else {
        return NULL;
    }
} //end findNthNode(..)


//----------------------------------------------------
// Add newNumber into array. If index is larger than
// the current array size, then grow the array in groups
// of 3 nodes at a time until index is now in range.
//
// Once this is done, add the new element and update
// the new current size.
//
void addValueAt(  
                 NodePtr pHead, NodePtr pTail, int index, int data, int size
//... parameters here ...
               )    
{    
    // If newNumberIndex is larger than the current number of Nodes on the list,
    // then keep growing the list three nodes at a time until it is in range.
    // ...
  
    //Here we determine the condition that the array is not large enough:
   while (index >= size) {
        NodePtr firstAuto = (NodePtr) malloc( sizeof( struct Node));
        firstAuto->index = size;
        firstAuto->data = 0;
        firstAuto->pNext = NULL;
        pTail -> pNext = firstAuto;
        pTail = firstAuto;

        size++;

        NodePtr secondAuto = (NodePtr) malloc( sizeof( struct Node));
        secondAuto->index = size;
        secondAuto->data = 0;
        secondAuto->pNext = NULL;
        pTail -> pNext = secondAuto;
        pTail = secondAuto;

        size++;
        
        NodePtr thirdAuto = (NodePtr) malloc( sizeof( struct Node));
        thirdAuto->index = size;
        thirdAuto->data = 0;
        thirdAuto->pNext = NULL;
        pTail -> pNext = thirdAuto;
        pTail = thirdAuto;

        size++; 
      }
 
    // List is now large enough to accomodate the newNumberIndex.
    // Find the node where it should go using findNthNode(..);
    // ...

    NodePtr tempNode = findNthNode(pHead, index);
    
    // Add the new element
    // ...
    tempNode->data = data;
} //end addValueAt(...)


//-----------------------------------------------
int main()
{
    int moveNumber = 1;     // Numbers user inputs.
    int maxSize = 3;        // Number of Nodes in storage, not counting the sentinel Node.
    int newNumber = 0;      // User input of new number to be added.
    int newNumberIndex = 0; // User input of index position where new number should go.
    
    // Allocate space for the initial sentinel Node and initialize its values.
    NodePtr pHead = (NodePtr) malloc( sizeof( struct Node));
    pHead->index = -1;
    pHead->data = -1;
    pHead->pNext = NULL;
    NodePtr pTail = pHead;  // Tail initially points to sentinel node
    
    // Allocate the first set of 3 nodes
    // ...

    NodePtr first = (NodePtr) malloc( sizeof( struct Node));
    first->index = 0;
    first->data = 0;
    first->pNext = NULL; 
    pTail->pNext = first;
    pTail = first;

    NodePtr second = (NodePtr) malloc( sizeof( struct Node));
    second->index = 1;
    second->data = 0;
    second->pNext = NULL;
    pTail->pNext = second;
    pTail = second; 

    NodePtr third = (NodePtr) malloc( sizeof( struct Node));
    third->index = 2;
    third->data = 0;
    third->pNext = NULL;
    pTail->pNext = third;
    pTail = third;

  
    // Prompt for, get and store new number
	printf("Give input of -1 to exit the program.\n");
    do {
        printf("%2d. Enter value and index: ", moveNumber);
        scanf("%d", &newNumber);
        if( newNumber == -1) {
            break;   // Exit when -1 is entered
        }
        else {
            // Also scan the index
            scanf("%d", &newNumberIndex);
        }
        
        // Add the new value, growing storage if needed.
        addValueAt(pHead, pTail, newNumberIndex, newNumber, maxSize);
      

        
        // Display the array with this new element
        displayArray( pHead);

        maxSize = pTail->index + 1;
      
        // Increment the moveNumber
        moveNumber++;
     } while( true);

    printf("Done.\n");
    return 0;
}

          //What the output of the program is supposed to look like: 

/* Give input of -1 to exit the program.
 1. Enter value and index: 3 0
Array indices:   0  1  2
       values:   3  0  0
 2. Enter value and index: 5 1
Array indices:   0  1  2
       values:   3  5  0
 3. Enter value and index: 7 0
Array indices:   0  1  2
       values:   7  5  0
 4. Enter value and index: 3 2
Array indices:   0  1  2
       values:   7  5  3
 5. Enter value and index: 2 3
*** Growing array from size 3 to 6
Array indices:   0  1  2  3  4  5
       values:   7  5  3  2  0  0
 6. Enter value and index: 13 6
*** Growing array from size 6 to 9
Array indices:   0  1  2  3  4  5  6  7  8
       values:   7  5  3  2  0  0 13  0  0
 7. Enter value and index: -1
Done.
  */
