#ifndef _list_h
#define _list_h

#include <stdio.h>
#include <stdlib.h>
#include "transformations.h"

void print_list(ElementNode * head);
void freeList( ElementNode* head);
int size(ElementNode * head);
void pushBegining(ElementNode **head, ElementData ** polygonData);
void push(ElementNode ** head, ElementData ** polygonData);
void pop(ElementNode ** head);
void remove_last(ElementNode * head);
void remove_by_index(ElementNode ** head, int n);
ElementNode * getAt (ElementNode ** head, int index);
ElementNode * copy (ElementNode *start1);


#endif /* LIST_H*/
