#include <stdio.h>
#include <stdlib.h>



typedef struct Student{
    int no;
    int not;
    struct Student *next;
}Sinfo;

void printList(Sinfo *head);
Sinfo *addValue(int no,int not,Sinfo *head);
Sinfo *status[2];
int main(){
    Sinfo *head = NULL;
    head = addValue(5,10,head);
    head = addValue(10,20,head);
    head = addValue(75,30,head);
    head = addValue(100,50,head);
    printList(head);
    return 1;
}




Sinfo *addValue(int no,int not,Sinfo *head){
    if(head == NULL){
        head = (Sinfo*)malloc(sizeof(Sinfo*));
        head->no = no;
        head->not = not;
        head->next = NULL;
        return head;
    }
    Sinfo *temp = (Sinfo*)malloc(sizeof(Sinfo));
    temp->no = no;
    temp->not = not;
    if(head->no < no){
        temp->next = head;
        return temp;
    }
    Sinfo *iter = head;
    while(iter->next->no>no && iter->next != NULL){
        iter = iter->next;
    }
    if(iter->next == NULL){
        temp->next = NULL;
        iter->next = temp;
        return head;
    }
    temp->next = iter->next;
    iter->next = temp;
    return head;
}

void printList(Sinfo *head){
    while(head->next != NULL){
        printf("[%p][%d][%d]",head,head->no,head->not);
        head = head->next;
    }
    printf("[%p][%d][%d]",head,head->no,head->not);
}


int ortHesapla(Sinfo *head){
    int sum;
    int ogrSayisi;
    while(head = NULL){
        ogrSayisi+=1;
        sum += head->not;
        head = head->next;
    }
    return sum/ogrSayisi;
}

