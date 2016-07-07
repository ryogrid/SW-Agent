#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct _LinkedListItem
{
    void *item;
    struct _LinkedListItem *next;
    struct _LinkedListItem *prev;
}LinkedListItem;

typedef struct _LinkedList
{
    LinkedListItem *head;
    int size;
} LinkedList;

LinkedList *NewLinkedList();
void DeleteLinkedList(LinkedList *list);
unsigned int GetLinkedListSize(LinkedList *list);

void AddLinkedListItem(LinkedList *list, void *item);
int RemoveLinkedListItem(LinkedList *list, int index);

void *GetLinkedListItem(LinkedList *list, int index);

#endif
