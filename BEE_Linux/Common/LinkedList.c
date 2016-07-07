#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

LinkedList *NewLinkedList()
{
    LinkedList *list;
    LinkedListItem *head;

    list = (LinkedList*)malloc(sizeof(LinkedList));
    head = (LinkedListItem*)malloc(sizeof(LinkedListItem));
    list->head = head;
    head->item = NULL;
    head->next = head;
    head->prev = head;
    list->size = 0;
    return list;
}

void DeleteLinkedList(LinkedList *list)
{
    int i;
    LinkedListItem *next, *e;
	
    e = list->head;
    for(i=0; i<list->size+1; i++){
        next = e->next;
        free(e);
        e = next;
    }
    free(list);
}

unsigned int GetLinkedListSize(LinkedList *list)
{
    return list->size;
}

static LinkedListItem *NewLinkedListItem(void *item, LinkedListItem *next, LinkedListItem *prev)
{
    LinkedListItem *entry;
    entry = (LinkedListItem*)malloc(sizeof(LinkedListItem));
    entry->item = item;
    entry->next = next;
    entry->prev = prev;
    return entry;
}

void AddLinkedListItem(LinkedList *list, void *item)
{
    LinkedListItem *entry;
    entry = NewLinkedListItem(item, list->head, list->head->prev);
    entry->prev->next = entry;
    entry->next->prev = entry;
    list->size++;
}

int RemoveLinkedListItem(LinkedList *list, int index)
{
    int i;
    LinkedListItem *entry;
    if(index >= list->size){
        return -1;
    }

    entry = list->head->next;
    for(i=0; i<index; i++){
        entry = entry->next;
    }
    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;
    list->size--;
    free(entry);
    return 1;
}

void *GetLinkedListItem(LinkedList *list, int index)
{
    int i;
    LinkedListItem *entry;
    if(index >= list->size){
        return NULL;
    }
    
    entry = list->head->next;
    for(i=0; i<index; i++){
        entry = entry->next;
    }
    return entry->item;
}
