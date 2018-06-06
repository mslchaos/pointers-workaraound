#include "main.h"

struct Node* CreateNode ()
{
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  if (!newNode) {
    printf("Memory didn't allocated, cannot continue\n");
    return NULL;
  }
  newNode->data = 0;
  newNode->prevEntry = NULL;
  newNode->nextEntry = NULL;
  return newNode;
}

struct Node* CreateNodeWithValue (int var)
{
  struct Node* newNode = CreateNode();
  if (!newNode) {
    return NULL;
  }
  newNode->data = var;
  return newNode;
}

struct Node* CreateEmptyNode () // Remove
{
  struct Node* newNode = CreateNode();
  if (!newNode) {
    return NULL;
  }
  return newNode;
}

int insertNodeAtIndex(int var, struct List* list, int indx)
{
  if (indx < 0 || indx > list->listSize) {
    printf("Wrong index provided please use value beetween %d and %d\n", 0, list->listSize);
    return 0;
  }
  struct Node* newNode = CreateNodeWithValue(var);
  if (!newNode) {
    return 0;
  }
  if (list->listSize == 0) {
    list->listHead = newNode;
    list->listTail = newNode;
  } else if (indx == list->listSize) {
    list->listTail->nextEntry = newNode;
    newNode->prevEntry = list->listTail;
    list->listTail = newNode;
  } else {
    struct Node* targetNode = getNodeAtIndex(list, indx);
    if (!targetNode) {
      printf("No node at index cannot proceed\n"); // Memory leak
      return 0;
    }
    if (targetNode->prevEntry) {
      targetNode->prevEntry->nextEntry = newNode;
    }
    if (indx == 0) {
      list->listHead = newNode;
    }
    newNode->prevEntry = targetNode->prevEntry;
    targetNode->prevEntry = newNode;
    newNode->nextEntry = targetNode;
  }
  list->listSize++;
  return 1;
}

int insertAtBegin (int var, struct List* list)
{
  return insertNodeAtIndex(var, list, 0);
}

int insertAtEnd (int var, struct List* list)
{
  return insertNodeAtIndex(var, list, list->listSize);
}

int deleteNodeAtIndex (struct List* list, int indx)
{
  if(indx >= list->listSize) {
    printf("Wrong index provided, nothing to delete\n");
    return 0;
  } else {
    struct Node* head = list->listHead;
    struct Node* tail = list->listTail;
    struct Node* valueToDelete;
    if (head && tail) {
      if (list->listSize != 1) {
        if (indx != 0 && indx != list->listSize - 1) {
          struct Node* iter = head;
          for(int i = 0; i < indx; i++) {
            iter = iter->nextEntry;
          }
          iter->prevEntry->nextEntry = iter->nextEntry;
          iter->nextEntry->prevEntry = iter->prevEntry;
          valueToDelete = iter;
        } else if (indx == 0) {
          list->listHead = head->nextEntry;
          list->listHead->prevEntry = NULL;
          valueToDelete = head;
        } else if (indx == list->listSize - 1) {
          list->listTail = tail->prevEntry;
          list->listTail->nextEntry = NULL;
          valueToDelete = tail;
        }
      } else {
        valueToDelete = head;
        list->listHead = NULL;
        list->listTail = NULL;
      }
      free(valueToDelete);
      if (!valueToDelete) {
        printf("Memory didn't freed, cannot continue\n");
        return 0;
      }
    } else {
      printf("Nothing do delete - list is empty\n");
      return 0;
    }
    list->listSize--;
    return 1;
  }
}

int deleteSpecifiedNode (struct List* list, struct Node* node)
{
  struct Node* head = list->listHead;
  struct Node* tail = list->listHead;
  if (head == node) {
    return deleteNodeAtIndex(list, 0);
  } else if (tail == node) {
    return deleteNodeAtIndex(list, list->listSize - 1);
  } else {
    struct Node* iter = head;
    int nodeIsFound = 0;
    int indx = 0;
    while(!nodeIsFound && indx != list->listSize) {
      if (iter == node) {
        nodeIsFound = 1;
      } else {
        indx++;
        iter=iter->nextEntry;
      }
    }
    if(nodeIsFound) {
      return deleteNodeAtIndex(list, indx);
    } else {
      printf("No such node in list\n");
      return 0;
    }
  }
}

struct Node* getNodeAtIndex (struct List* list, int indx)
{
  if (indx >= list->listSize || indx < 0) {
    printf("Wrong index for get\n");
    return NULL;
  }
  struct Node* iter = list->listHead;
  for(int i = 0; i < indx; i++) {
    iter=iter->nextEntry;
  }
  return iter;
}

int deleteNodeAtBegin (struct List* list)
{
  return deleteNodeAtIndex(list, 0);
}

int deleteNodeAtEnd (struct List* list)
{
  int listSize = list->listSize;
  return deleteNodeAtIndex(list, listSize - 1);
}

void printList (struct List* list)
{
  struct Node* head = list->listHead;
  if (!head) {
    printf("Seems to be nothing to print\n");
    return;
  }
  struct Node* iterPtr = head;
  while(iterPtr) {
    printf("%d\n", iterPtr->data);
    iterPtr = iterPtr->nextEntry;
  }
  return;
}

void printListReverse (struct List* list)
{
  struct Node* head = list->listHead;
  if (!head) {
    printf("Seems to be nothing to print\n");
    return;
  }
  // Looking for last node in list
  struct Node* iterPtr = head;
  while(iterPtr->nextEntry) {
    iterPtr = iterPtr->nextEntry;
  }
  // Printing in reverse
  while(iterPtr) {
    printf("%d\n", iterPtr->data);
    iterPtr = iterPtr->prevEntry;
  }
}
struct List* createList () {
  struct List* list = (struct List*)malloc(sizeof(struct List));
  if (!list) {
    printf("Cannot allocate list, exit");
    return NULL;
  }
  list->listHead = NULL;
  list->listTail = NULL;
  list->listSize = 0;
  if (ListsHeadNode) {
    struct List* tailList = ListsHeadNode;
    while(tailList->nextList) {
      tailList = tailList->nextList;
    }
    tailList->nextList = list;
    list->prevList = tailList;
    list->nextList = NULL;
  } else {
    ListsHeadNode = list;
    list->nextList = NULL;
    list->prevList = NULL;
  }
  return list;
}

int main ()
{
  struct List* list = createList();
  printf("current size is %d\n", list->listSize);
  insertAtBegin(0, list);
  printf("current size is %d\n", list->listSize);
  insertAtBegin(2, list);
  printf("current size is %d\n", list->listSize);
  insertAtEnd(3, list);
  printf("current size is %d\n", list->listSize);
  printf("List in usual direction \n");
  printList(list);
  printf("List in reverse direction \n");
  printListReverse(list);
  printf("current size is %d\n", list->listSize);
  deleteNodeAtBegin(list);
  printf("current size is %d\n", list->listSize);
  printList(list);
  deleteNodeAtEnd(list);
  printf("Deleted one node at begin and one at end\n");
  printList(list);
  printf("current size is %d\n", list->listSize);
  deleteNodeAtEnd(list);
  printf("Deleted last node in list\n");
  printf("current size is %d\n", list->listSize);
  printf("Will try ot delete more values that exists\n");
  deleteNodeAtEnd(list);
  printf("current size is %d\n", list->listSize);
  printf("################################\n");
  struct Node* secondNode = getNodeAtIndex(list, 1); // Demonstrate delete at index
  if (secondNode) {
    printf("data of elem at indx 1 is %d\n", secondNode->data);
  } else {
    printf("No data in list\n");  
  }
  insertAtBegin(5, list);
  insertAtBegin(4, list);
  insertAtBegin(3, list);
  insertAtBegin(2, list);
  insertAtBegin(1, list);
  struct Node* thirdNode = getNodeAtIndex(list, 1);
  if (thirdNode) {
    printf("data of elem at indx 3 is %d\n", thirdNode->data);
  } else {
    printf("No data in list\n");  
    exit(1);
  }
  printf("################################\n");
  printf("Printing list in usual direction\n");
  printList(list);
  printf("################################\n");
  printf("Deleting founded node with value - %d\n", thirdNode->data);
  deleteSpecifiedNode(list, thirdNode);
  printf("################################\n");
  printf("Printing list in usual direction\n");
  printList(list);
}