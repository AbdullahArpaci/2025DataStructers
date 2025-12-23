#include <stdio.h>
#include <stdlib.h>

#define size_of_table 16

typedef struct MyStruct{
    int id;
    char name[20];
    float ortalama;
    struct MyStruct *next;
}MyHS;

int hash_to_idx(int id);
void addStudent(MyHS *studen_list[],MyHS *temp);
void print_hash_table(MyHS **student_table);
void addValue(int id, char name[20], float ortalama, MyHS **student_table);
void deleteValue(MyHS **student_table,int id);


int main() {
    MyHS *student_table[size_of_table];
    for (int i = 0; i < size_of_table; i++) {
        student_table[i] = NULL;
    }

  
    addValue(10, "Ahmet", 3.50, student_table);
    addValue(26, "Mehmet", 2.80, student_table);
    addValue(16, "Mehmet", 2.80, student_table);
    addValue(42, "Ayse", 3.90, student_table);
    addValue(5, "Fatma", 3.20, student_table);
    addValue(1, "Can", 2.45, student_table);
    deleteValue(student_table,16);


    print_hash_table(student_table);

    return 0;
}


void addStudent(MyHS *studen_list[],MyHS *temp){
    if(temp == NULL){
        return;
    }
    int idx;
    idx = hash_to_idx(temp->id);

    if(studen_list[idx] == NULL){
        studen_list[idx] = temp;
    }
    else{
        MyHS *iter = studen_list[idx];
        while(iter->next != NULL){
            iter = iter->next;
        }
        iter->next = temp;
    } 
}
int hash_to_idx(int id) {
   
    unsigned int x = (unsigned int)id;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    
    return x % 16; 
}

void addValue(int id, char name[20], float ortalama, MyHS **student_table){

    MyHS *temp = (MyHS*)malloc(sizeof(MyHS));
    if (temp == NULL) {
        printf("Hata: Bellek ayrilamadi!\n");
        return;
    }


    temp->id = id;
    temp->ortalama = ortalama;
    temp->next = NULL;

    int i = 0;
    while (name[i] != '\0') {
        temp->name[i] = name[i];
        i++;
    }
    temp->name[i] = '\0';
    addStudent(student_table, temp);
}

void print_hash_table(MyHS **student_table){
    MyHS *iter;
    for (int i = 0; i < size_of_table; i++) {
        printf("Index [%d]: ", i);
        iter = student_table[i];

        if (iter == NULL) {
            printf("NULL\n");
            continue;
        }

        while (iter != NULL) { 
            printf("[%d | %s | %.2f] -> ", iter->id, iter->name, iter->ortalama);
            iter = iter->next;
        }
        printf("NULL\n");
    }
}

void deleteValue(MyHS **student_table, int id) {
    int idx = hash_to_idx(id);
    MyHS *curr = student_table[idx];
    MyHS *prev = NULL;

    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) {
                student_table[idx] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}