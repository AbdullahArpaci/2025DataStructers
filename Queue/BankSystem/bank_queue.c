#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int siraNo;
    char ad[50];
    char islemTipi[20];
    int priority;
}Musteri;

typedef struct MyQueue{
    Musteri data;
    struct MyQueue *next;
}MyQ;

typedef struct {
    MyQ *front;
    MyQ *rear;
} Queue;


typedef struct {
    Queue normalQueue;
    Queue vipQueue;
    int customerCount;
} BankSystem;



int siraNo = 0;
int isEmpty(MyQ *root);
void enqueue(Queue *q, Musteri *a);
Musteri dequeue(Queue *q);
void addCustomer(BankSystem *bank, Musteri *a);
Musteri *newCustomer();

int main(){
    BankSystem bank;
    bank.normalQueue.front = NULL;
    bank.normalQueue.rear  = NULL;
    bank.vipQueue.front    = NULL;
    bank.vipQueue.rear     = NULL;
    bank.customerCount     = 0;

    int choice;

    while(1){
        printf("\n===== BANKA SISTEMI =====\n");
        printf("1 - Yeni Musteri Ekle\n");
        printf("2 - Siradaki Musteriyi Cagir\n");
        printf("3 - Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        if(choice == 1){
            Musteri *m = newCustomer();
            addCustomer(&bank, m);
            free(m);
        }
        else if(choice == 2){
            Musteri next;

            if(bank.vipQueue.front != NULL){
                next = dequeue(&bank.vipQueue);
                printf("\n[VIP] ");
            }
            else if(bank.normalQueue.front != NULL){
                next = dequeue(&bank.normalQueue);
                printf("\n[Normal] ");
            }
            else{
                printf("\nBekleyen musteri yok.\n");
                continue;
            }

            printf("Sira No: %d | Ad: %s | Islem: %s\n",
                   next.siraNo, next.ad, next.islemTipi);
        }
        else if(choice == 3){
            printf("Sistem kapatiliyor...\n");
            break;
        }
        else{
            printf("Gecersiz secim!\n");
        }
    }

    return 0;
}



int isEmpty(MyQ *root){
    if(root == NULL){
        return 1;        
    }
    return 0;
}


void enqueue(Queue *q, Musteri *a){
    MyQ *temp = malloc(sizeof(MyQ));

    if(temp == NULL){
    printf("Memory allocation failed\n");
    return;
    }
    temp->data = *a;
    temp->next = NULL;

    if(isEmpty(q->front)){
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}



Musteri dequeue(Queue *q){
    if(isEmpty(q->front)==1){
        Musteri empty = {0};
        return empty;
    }
    MyQ *temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    Musteri a = temp->data;
    free(temp);
    return a;
}


Musteri *newCustomer(){
    Musteri *a = (Musteri*)malloc(sizeof(Musteri));
    printf("Fill out the customer form:\n");

    char name[20];
    printf("Customer Name");
    scanf("%s",name);
    strcpy(a->ad,name);

    char islemTipi[20];
    printf("Porcess Type:");
    scanf("%s",islemTipi);
    strcpy(a->islemTipi,islemTipi);

    char priorityType[20];
    printf("Lutfen öncelik durumunuzu belirtiniz");
    scanf("%s",priorityType);
    if(strcmp(priorityType,"VIP") == 0 || strcmp(priorityType,"Engelli") == 0){
        a->priority = 1;
    }
    else{
        a->priority = 0;
    }
    a->siraNo = siraNo;
    siraNo+=1;
    printf("Alinan sira no:%d\nLütfen siraniz gelene kadar bekleyiniz\n", a->siraNo);
    return a;
}


void addCustomer(BankSystem *bank, Musteri *a){
    if(a->priority){
        enqueue(&bank->vipQueue,a);
    } else {
        enqueue(&bank->normalQueue,a);
    }
    bank->customerCount++;
}