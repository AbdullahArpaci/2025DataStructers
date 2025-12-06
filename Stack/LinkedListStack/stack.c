#include <stdio.h>
#include <stdlib.h>


typedef struct MyStack{
    int data;
    struct MyStack *next;
}StackL;




int main(){
    StackL *stack = NULL;

    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);

    peek(stack); 

    stack = pop(stack);   
    peek(stack);

    stack = pop(stack);   
    stack = pop(stack);   
    stack = pop(stack);

    return 0;
}


StackL *push(StackL *top,int value){
    if(top == NULL){
        top = (StackL*)malloc(sizeof(StackL));
        top->data = value;
        top->next = NULL;
        return top;
    }
    StackL *temp =(StackL*)malloc(sizeof(StackL));
    temp->data = value;
    temp->next = top;
    return temp;
}


StackL *pop(StackL *top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return NULL;
    }
    StackL *temp = top->next;
    free(top);
    return temp;
}

void peek(StackL *top){
    if(top == NULL){
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}