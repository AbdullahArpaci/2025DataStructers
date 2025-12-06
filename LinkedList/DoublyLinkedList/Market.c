//Abdullah Arpacı 23100011033
#include <stdio.h>
#include <stdlib.h>



typedef struct product{
    char *name;
    int numberOfstock;
    int numberOfsale;
    struct product *next;
    struct product *prev;
}pNode;

pNode *addValue(pNode *head,char*name,int numberOfstock,int numberOfsale);
void printList(pNode*head);
int calculateLength(char *a);
char *strcopy(char *b);
pNode *bagliListeOlustur(pNode *head);
pNode *sorted(pNode *head);
pNode *bubble(pNode *head);
pNode *Search(char *a,pNode *head);
int check(char *a,char *b);
pNode *enterSale(pNode *head);
pNode *enterStock(pNode *head);
void Menu();

int main(){
    pNode *head = NULL;
    while(1){
        Menu();
        int islem;
        scanf("%d",&islem);
        if(islem == 1){
            head = bagliListeOlustur(head);
            printList(head);
        }
        else if(islem == 2){
            head = enterSale(head);
            printList(head);
        }
        else if(islem == 3){
            head  =enterStock(head);
            printList(head);
        }
        else if(islem == 4){
            exit(1);
        }
        else{
            printf("Gecersiz deger girisi");
            continue;
        }
    }
}

pNode *addValue(pNode *head,char*name,int numberOfstock,int numberOfsale){
    if(head == NULL){
        head = (pNode*)malloc(sizeof(pNode));
        head->name = strcopy(name);
        head->numberOfsale = numberOfsale;
        head->numberOfstock = numberOfstock;
        head->next = head;
        head->prev = head;
        return head;
    }
    pNode *temp = (pNode*)malloc(sizeof(pNode));
    temp->name = strcopy(name);
    temp->numberOfsale = numberOfsale;
    temp->numberOfstock = numberOfstock;
    if(head->numberOfsale < numberOfsale){
        head->prev->next = temp;
        temp->prev = head->prev;
        temp->next = head;
        head->prev = temp;
        return temp;
    }
    pNode *iter = head;
    while(iter->next->numberOfsale > numberOfsale && iter->next != head){
        iter = iter->next;
    }
    temp->next = iter->next;
    iter->next->prev = temp;
    temp->prev = iter;
    iter->next = temp;
    return head;
}


void printList(pNode*head){
    pNode *temp = head;
    while(temp->next != head){
        printf("Product = [%s]-Sum of sale=[%d]-Stock:[%d]->",temp->name,temp->numberOfsale,temp->numberOfstock);
        temp = temp->next;
    }
    printf("Product = [%s]-Sum of sale=[%d]-Stock:[%d]\n\n",temp->name,temp->numberOfsale,temp->numberOfstock);
}


char *strcopy(char *b){
    int lengthB = calculateLength(b);
    char *a = malloc(lengthB+1);

    for(int i=0;i<lengthB;i++){
        *(a+i) = *(b+i);
    }

    a[lengthB] = '\0';
    return a;
}

int calculateLength(char *a){
    int i = 0;
    while (*(a+i) != '\0'){
        i++;
    }
    return i;
}


pNode *bagliListeOlustur(pNode *head){
    FILE *dosya;
    dosya = fopen("veri.txt","r");
    char *name = malloc(20);
    int numOfSales = 0;
    int numOfStock = 0;
    while(fscanf(dosya, "%19[^,],%d,%d\n",name,&numOfSales,&numOfStock) == 3){
        head = addValue(head,name,numOfStock,numOfSales);
    }
    return head;
}




pNode *sorted(pNode *head){
    pNode *iter = head;
    while(iter->next != head){
        if(iter->next->numberOfsale > iter->numberOfsale){
            if(iter == head){
                head = iter->next;
            }
            pNode *temp = iter->next;
            temp->next->prev = iter;
            iter->prev->next  = temp;
            temp->prev = iter->prev;
            iter->prev = temp;
            iter->next  =temp->next;
            temp->next  =iter;
        }
        else{
            iter = iter->next;
        }
    }
    return head;
}

pNode *bubble(pNode *head){
    pNode *iter = head;
    pNode *temp = head;
    while(iter->next != head){
        head = sorted(head);
        iter = iter->next;
    }
    return head;
}

pNode *Search(char *a,pNode *head){
    pNode *iter = head;
    while(iter->next != head){
        if(check(a,iter->name) == 1){
            return iter;
        }
        else{
            iter = iter->next;
        }
    }
    if(check(a,iter->name) == 1){
        return iter;
    }
    else{
        return NULL;
    }
}

int check(char *a,char *b){
    int lengthA = calculateLength(a);
    int lengthB = calculateLength(b);
    if(lengthA != lengthB){
        return 0;
    }
    for(int i = 0;i<lengthA;i++){
        if(a[i] == b[i]){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

pNode *enterSale(pNode *head){
    char name[20];
    printf("Lutfen satis bilgisi gireceginiz urunu seciniz\n\n");
    scanf("%s",name);
    pNode *temp = Search(name,head);
    if(temp == NULL){
        printf("Belirtilen urun bulunamamistir\n");
        return head;
    }
    int satis;
    printf("Lutfen %s urununun satis adedini giriniz: ", name);
    scanf("%d",&satis);
    if(temp->numberOfstock < satis){
        printf("Yetersiz Stok\n");
        return head;
    }
    temp->numberOfsale += satis;
    temp->numberOfstock -=satis;
    head = bubble(head);
    return head;
}


pNode *enterStock(pNode *head){
    char name[20];
    printf("Lutfen stok bilgisi gireceginiz urunu seciniz\n\n");
    scanf("%s",name);
    pNode *temp = Search(name,head);
    if(temp == NULL){
        printf("Belirtilen urun bulunamamistir\n");
        return head;
    }
    int stok;
    printf("Lutfen %s urununun stok adedini giriniz: ", name);
    scanf("%d",&stok);
    temp->numberOfstock +=stok;
    return head;
}

void Menu(){
    printf("Lutfen yapmak istediginiz islem tipini seciniz\n\n");
    printf("-Bagli liste olusturmak icin 1 i tuslayiiniz\n");
    printf("-Satis sayisini guncellemek icin 2 yi tuslayiniz\n");
    printf("-Stok sayisi guncellemek icin 3 u tuslayiniz\n");
    printf("-Programi kapatmak icin 4 u tuslayiniz\n");
}