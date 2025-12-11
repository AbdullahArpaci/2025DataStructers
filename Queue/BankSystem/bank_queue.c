#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int siraNo;
    char ad[50];
    char islemTipi[20];
}Musteri;

typedef struct MyQueue{
    Musteri data;
    struct MyQueue *next;
}MyQ;

int isEmpty(MyQ *root);
MyQ *enqueue(MyQ *root,char customer_name[],char process_type[],int number);


int main(){
    MyQ *root = NULL;
    return 0;
}



int isEmpty(MyQ *root){
    if(root == NULL){
        return 1;        
    }
    return 0;
}


MyQ *enqueue(MyQ *root,char customer_name[],char process_type[],int number){
    MyQ *temp = (MyQ*)malloc(sizeof(MyQ));
    temp->data.siraNo = number;
    strcpy(temp->data.ad,customer_name);
    strcpy(temp->data.islemTipi,process_type);
    temp->next = NULL;
    

    if(isEmpty(root) == 1){
        root = temp;
        return root;
    }

    MyQ *iter = root;
    while(iter->next != NULL){
        iter = iter->next;
    }

    iter->next = temp;

    return root;

}


MyQ *dequeue(MyQ *root){

}