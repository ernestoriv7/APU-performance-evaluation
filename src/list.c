#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void print_list(ElementNode * head) {
    ElementNode * current = head;
    while (current != NULL) {
        //printf("(%LF,%LF)\n", current->x,current->y);
        current = current->next;
    }
}

void freeList( ElementNode* head)
{
   struct ElementNode* tmp;
   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int size(ElementNode * head){
    int size = 0;
    ElementNode * current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void pushBegining(ElementNode **head, ElementData ** polygonData) {
    ElementNode * new_node = malloc(sizeof(ElementNode));
    new_node->data = *polygonData;
    new_node->next = *head;
    *head = new_node;
}

void push(ElementNode ** head, ElementData ** polygonData) {       
    if(*head == NULL){
        pushBegining(head,polygonData);
    } else {       
        ElementNode * current = *head;
        while (current->next != NULL) {
            current = current->next;               
        }
        /* now we can add a new variable */
        current->next = malloc(sizeof(ElementNode));
        current->next->data = *polygonData ;
        current->next->next = NULL;
    }
}

void pop(ElementNode ** head) {
    ElementNode * next_node = NULL;

    if (*head == NULL) {
        return;
    }

    next_node = (*head)->next;
    free(*head);
    *head = next_node;

    return;
}

void remove_last(ElementNode * head) {
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        free(head);
        return;
    }

    /* get to the last node in the list */
    ElementNode * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the last item of the list, so let's remove current->next */
    free(current->next);
    current->next = NULL;
    return;
}

void remove_by_index(ElementNode ** head, int n) {
    ElementNode * current = *head;
    ElementNode * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }
    int i;
    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);
    return;
}

ElementNode * getAt(ElementNode ** head, int index){
    int i = 0;
    ElementNode * current = *head;
    if(index == 0){
        return *head;
    } else {
        while(i < index){
            current = current->next;
            i++;
        }
        return current;
    }

}

ElementNode *copy(ElementNode *start1)
{
    ElementNode *start2=NULL,*previous=NULL;

    while(start1!=NULL)
    {
        ElementNode * temp = malloc(sizeof(ElementNode));
        temp->data = start1->data;
        temp->next = NULL;
        if(start2==NULL)
        {
            start2=temp;
            previous=temp;
        }
        else
        {
            previous->next=temp;
            previous=temp;          
        }
        start1=start1->next;
    }
    return start2;
}
