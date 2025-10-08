/*Ad Soyad = Abdullah Arpacı 
Numara = 23100011033*/


#include <stdio.h>
#include <stdlib.h>



typedef struct LinkedList{
    int number;
    struct LinkedList*next;
}LinkedList;

int Menu();
void dosyaoku(char *dosyaAdi,LinkedList *listeler[],int LengthList[]); 
int satirSayisi(char *dosya);
LinkedList *allocation(int value);
LinkedList *addValue(LinkedList *a, int value);
LinkedList* bubbleSort(LinkedList* head, int n);
LinkedList *Sort(LinkedList * head);
LinkedList *deleteAndMerge(LinkedList *list1,LinkedList **list2,int length);
void freeLL(LinkedList *head);
void yazdir(LinkedList *listeler[],int satir_sayisi);


int main(void){
    char *dosyaAdi = "deneme.txt";
    int satir_Sayisi = satirSayisi(dosyaAdi);
    LinkedList *listeler[satir_Sayisi];
    int LengthList[satir_Sayisi];
    int islem;
    while(islem != 3){
        islem = Menu();
        if(islem == 1){
            dosyaoku(dosyaAdi,listeler,LengthList);
        }
        else if(islem == 2){
            listeler[0] = bubbleSort(listeler[0],LengthList[0]);
            for(int i = 1;i<satir_Sayisi;i++){
                listeler[0] = deleteAndMerge(listeler[0],&listeler[i],LengthList[i]);
            }
            yazdir(listeler,satir_Sayisi);
        }
        else{
            for(int i = 0;i<satir_Sayisi;i++){          
                freeLL(listeler[i]);
            }
            break;
        }
    }
}


void dosyaoku(char *dosyaAdi,LinkedList *listeler[],int LengthList[]){
    FILE *dosya;
    int satir_Sayisi = 0;
    int number;
    char zero = '0';
    dosya = fopen(dosyaAdi,"r");
    satir_Sayisi = satirSayisi(dosyaAdi);
    for(int i = 0;i<satir_Sayisi;i++){
        listeler[i] = NULL;
        LengthList[i] = 0;
        while((number = fgetc(dosya)) != EOF){
            if (number == '\n'){
                break;
            }
            else if(number != ','){
                number = number - zero;
                listeler[i] = addValue(listeler[i],number);
                LengthList[i] += 1;
            }
            else{
                continue;
            }
        }
    }
    yazdir(listeler,satir_Sayisi);
}

int satirSayisi(char *dosyaAdi){
    FILE *dosya;
    dosya = fopen(dosyaAdi, "r");
    char satir[200];
    int satir_Sayisi = 0;
    while(fgets(satir,sizeof(satir),dosya)){
        satir_Sayisi++;
    }
    rewind(dosya);
    return satir_Sayisi;
}


LinkedList *allocation(int value){
    LinkedList*temp = (LinkedList*)malloc(sizeof(LinkedList));
    if (temp == NULL){
        printf("The memory was not allocated");
        return 0;
    }
    temp->number = value;
    temp->next = NULL;
    return temp;
}

LinkedList* addValue(LinkedList *a, int value){
    if(a == NULL){
        return allocation(value);
    }

    LinkedList *temp = a;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = allocation(value);
    return a;
}

void yazdir(LinkedList *listeler[],int satir_sayisi){
    LinkedList *temp;
    for(int i = 0;i<satir_sayisi;i++){
        temp = listeler[i];
        printf("%d LinkedList = ",i+1);
        while(temp !=NULL){
            if(temp->next == NULL){}
            printf("[%d:%d]->", (void*)temp, temp->number);
            temp = temp->next;
        }
        printf("\n");
    }
}


LinkedList *Sort(LinkedList * head){
    if(head->next == NULL){
        return head;
    }
    LinkedList *a = head;
    LinkedList *b = a->next;
    LinkedList *previsunValue = NULL; 
    while(a->next != 0){
        b = a->next;
        if(a->number > b->number){
                a->next = b->next;
                b->next = a;
                if(previsunValue == NULL){
                    head = b;
                }
                else{
                    previsunValue->next = b;
                }
                previsunValue = b;
        }
        else{
            previsunValue = a;
            a = a->next;
        }
    }
    return head;
}


LinkedList* bubbleSort(LinkedList* head, int n) {
    int j = 0;
    for(int i = 0;i<n-j;i++){
        head = Sort(head);
    }
    return head;
}

LinkedList *deleteAndMerge(LinkedList *list1,LinkedList **list2,int length){
    LinkedList *prev = NULL;
    LinkedList *a = list1;
    LinkedList *b;
    for(int i = 0;i<length;i++){
        a = list1;
        b = *list2;
        *list2  = (*list2)->next;
        prev = NULL;
        b->next = NULL;
        while(a != NULL){
            if(a->number > b->number){
                b->next = a;
                if(prev == NULL){
                    list1 = b;
                }
                else{
                    prev->next = b;
                }
                prev = b;
                break;
            }
            else if(a->next == NULL){
                a->next = b;
                break;
            }
            else{
                prev = a;
                a = a->next;
            }
        }
    }
    return list1;
}


int Menu() {
    int secim;
    printf("\nMENU\n");
    printf("dosyayi okuma islemi icin 1i tuslayiniz\n");
    printf("siralama ve birlestirme islemi icin 2 yi tuslayiniz\n");
    printf("cikmak icin 3 u tuslayiniz\n");
    scanf("%d", &secim);
    return secim;
}



void freeLL(LinkedList *head){
    if(head == NULL) return;
    LinkedList *iter = head->next;
    while(iter != NULL){
        LinkedList *temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(head);
}