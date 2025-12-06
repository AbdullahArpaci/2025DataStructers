#include <stdio.h>
#include <stdlib.h>



typedef struct CircleLinkedList{
    int val;
    struct CircleLinkedList *next;
}CircleLL;



CircleLL *delValue(CircleLL *head,int value);
CircleLL *addValue(CircleLL *head,int value);
void freeCircleLL(CircleLL *head);
void printCircleLL(CircleLL *head);


int main(void){
    CircleLL *head = NULL;
    head = addValue(head,10);
    head = addValue(head,20);
    head = addValue(head,30);
    head = addValue(head,40);
    printCircleLL(head);
    head = delValue(head,10);
    printCircleLL(head);
    freeCircleLL(head);

}


void printCircleLL(CircleLL *head){
    CircleLL *iter = head;
    while(iter->next!= head){
        printf("[%p:%d]->",iter,iter->val);
        iter = iter->next;
    }
    printf("[%p:%d]",iter,iter->val);
    printf("\n");
}


CircleLL *addValue(CircleLL *head,int value){
    CircleLL *temp = (CircleLL*)malloc(sizeof(CircleLL));
    if(temp == NULL){
        printf("The memory was not allocated");
        return NULL;
    }
    temp->val = value;
    if(head == NULL){
        temp->next = temp;
        return temp;
    }
    CircleLL *iter = head;
    if (value < head->val) {
        while (iter->next != head)
            iter = iter->next;
        iter->next = temp;
        temp->next = head;
        head = temp;
        return head;
    }
    while(iter->next != head && iter->next->val < value){
        iter = iter -> next; 
    }
    temp->next = iter->next;
    iter->next = temp;
    return head;
}

CircleLL *delValue(CircleLL *head,int value){
    if(head == NULL){
        printf("The list is empty");
        return NULL;
    }
    CircleLL *iter = head;
    CircleLL *temp;
    if(head->val == value){
        while(iter->next != head){
            iter = iter->next;
        }
        if(iter == head){
            free(head);
            return NULL;
        }
        iter->next = head->next;
        free(head);
        return iter->next;
    }
    while(iter->next != head && iter->next->val != value){
        iter = iter->next;
    }
    temp = iter->next;
    if(temp == head){
        printf("The value was not found\n");
        return head;
    }
    iter->next = temp->next;
    free(temp);
    return head;
}


void freeCircleLL(CircleLL *head){
    if(head == NULL) return;
    CircleLL *iter = head->next;
    while(iter != head){
        CircleLL *temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(head);
}