//Abdullah Arpacı 23100011033

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct CircelLL{
    char *name;
    char *surname;
    char *phoneNumber;
    struct CircelLL *next;
}CircelLL;

int checkList(char *number,CircelLL *head);
int calculateLength(char *a);
void copy(char *a,char *b);
CircelLL *addValue(CircelLL *head,char *name,char*surname,char*phoneNumber);
char *compareWord(char *a,char *b);
CircelLL *compareNode(CircelLL *a,CircelLL *b);
void printList(CircelLL *head);
CircelLL *readFILE(FILE *dosya);
CircelLL *reverse(CircelLL *head);
void Menu();

int main(void){
    CircelLL *head = NULL;
    FILE *dosya;
    int islem;
    while(1){
        Menu();
        printf("Lutfen islem tipini giriniz");
        scanf("%d",&islem);
        printf("\n\n\n");
        if(islem == 1){
            dosya = fopen("PhoneBook.txt","r");
            head = readFILE(dosya);
            printList(head);
            fclose(dosya);
        }
        else if(islem == 2){
            head = reverse(head);
            printList(head);
        }
        else{
            break;
        }
    }
    return 0;
}



CircelLL *addValue(CircelLL *head,char *name,char*surname,char*phoneNumber){
    CircelLL *temp = (CircelLL*)malloc(sizeof(CircelLL));
    temp->name = malloc(calculateLength(name)+1);
    temp->surname = malloc(calculateLength(surname)+1);
    temp->phoneNumber = malloc(calculateLength(phoneNumber)+1);
    temp->next = NULL;
    copy(temp->name,name);
    copy(temp->surname,surname);
    copy(temp->phoneNumber,phoneNumber);
    //İlk değer olabilir
    if(head == NULL){
        temp->next = temp;
        return temp;
    }

    //Numarayı kontrol etme kısmı
    if (checkList(phoneNumber,head) == 1){
        return head;
    }

    CircelLL *iter = head;
    if(compareNode(head,temp) == temp){
        temp->next = head;
        while(iter->next != head){
            iter = iter->next;
        }
        iter->next = temp;
        return temp;
    }
    iter  = head;
    while(iter->next != head){
        if(compareNode(iter->next,temp) == temp){
            temp->next = iter->next->next;
            iter->next = temp;
            return head;
        }
        else{
            iter = iter->next;
        }
    }
    temp->next = head;
    iter->next = temp;
    return head;
}

void printList(CircelLL *head){
    CircelLL *iter = head;
    while(iter->next != head){
        printf("[%d:%s,%s,%s]->",iter,iter->name,iter->surname,iter->phoneNumber);
        iter = iter->next;
    }
    printf("[%d:%s,%s,%s]\n",iter,iter->name,iter->surname,iter->phoneNumber);
}



int checkList(char *number,CircelLL *head){
    CircelLL *temp = head;
    if(compareWord(head->phoneNumber,number) == NULL){
        return 1;
    }
    while(temp->next != head){
        if(compareWord(temp->next->phoneNumber,number) == NULL){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

char* compareWord(char *a, char *b) {
    int lengthA = calculateLength(a);
    int lengthB = calculateLength(b);
    int minLength;
    if(lengthA < lengthB){
        minLength = lengthA;        
    }
    else{
        minLength = lengthB;
    }

    for (int i = 0; i < minLength; i++) {
        if (a[i] < b[i]) {
            return a;
        } else if (a[i] > b[i]) {
            return b;
        }
    }

    if (lengthA < lengthB) {
        return a;
    } else if (lengthB < lengthA) {
        return b;
    } else {
        return NULL;
    }
}


CircelLL *compareNode(CircelLL *a,CircelLL *b){
    char *word = compareWord(a->name,b->name);
    if(word != NULL){
        if(compareWord(a->name,word) == NULL){
            return a;
        }
        else{
            return b;
        }
    }
    else{
        char *word = compareWord(a->surname,b->surname);
        if(word != NULL){
            if(compareWord(a->surname,word) == NULL){
                return a;
            }
            else{
                return b;
            }
        }
    }
    return a;
}


CircelLL *readFILE(FILE *dosya){
    char *name = malloc(20);
    char *surname =  malloc(20);
    char *phoneNumber  = malloc(20);
    CircelLL *head = NULL;
    while (fscanf(dosya, " { %49[^,] , %49[^,] , %49[^}] }%*[, ]", name, surname, phoneNumber) == 3) {
        head = addValue(head, name, surname, phoneNumber);
    }
    return head;
}

void copy(char *a, char *b) {
    int lengthB = calculateLength(b);
    for (int i = 0; i < lengthB; i++) {
        a[i] = b[i];
    }
    a[lengthB] = '\0';
}

int calculateLength(char *a){
    int i = 0;
    while(*(a+i) != '\0'){
        i+=1;
    }
    return i;
}

CircelLL *reverse(CircelLL *head){
    CircelLL *prev,*now,*sonraki;
    prev = head;
    now = head->next;
    while(now->next != head){
        sonraki = now->next;
        now->next = prev;
        prev = now;
        now = sonraki;
    }
    head->next = now;
    now->next = prev;
    return now;
}



void Menu(){
    printf("Dosyayi okumak ve Dairesel listeye eklemek icin 1 i tuslayiniz\n");
    printf("Listeyi ters cevirmek icin 2 yi tuslayiniz\n");
    printf("Cikis yapmak icin 3 ü tuslayiniz\n");
}