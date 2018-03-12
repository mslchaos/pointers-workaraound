#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* nextEntry;
  struct Node* prevEntry;
};

struct List {
  struct Node* listHead;
  struct Node* listTail;  
  unsigned listSize; 
  struct List* nextList;
  struct List* prevList;
};

// Needed for cleanup
struct List* ListsHeadNode;

void cleanup();

struct Node* CreateNode ();
struct Node* CreateNodeWithValue (int var);
struct Node* CreateEmptyNode ();
int insertNodeAtIndex(int var, struct List* list, int indx);
int insertAtBegin (int var, struct List* list);
int insertAtEnd (int var, struct List* list);
int deleteNodeAtIndex (struct List* list, int indx);
int deleteSpecifiedNode (struct List* list, struct Node* node);
struct Node* getNodeAtIndex (struct List* list, int indx);
int deleteNodeAtBegin (struct List* list);
int deleteNodeAtEnd (struct List* list);
void printList (struct List* list);
void printListReverse (struct List* list);
struct List* createList ();
int main ();