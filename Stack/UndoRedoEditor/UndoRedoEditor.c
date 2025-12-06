//Abdullah Arpacı 23100011033

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStack
{
    char data;
    struct MyStack *next;
} MyS;

char pop(MyS **root);
void push(MyS **root, char data);
void printStack(MyS *root);
void redo(MyS **text, MyS **rootUndo, MyS **rootRedo, int number, int process);
void undo(MyS **text, MyS **rootUndo, MyS **rootRedo, int number, int process);
void delete(MyS **text, MyS **rootUndo, int number);
void append(int number, MyS **text);

int main()
{
    MyS *undoStack = NULL;
    MyS *redoStack = NULL;
    MyS *text = NULL;

    int islem;
    int number[20];
    int process[20];
    int counter = 0;
    while (1)
    {
        printf("Append islemi icin 1 i\n");
        printf("Delete islemi icin 2 yi\n");
        printf("Undo islemi icin 3u \n");
        printf("Redo islemi icin 4u\n");
        printf("Cikmak icin 0 i tuslayiniz\n");
        printf("Seciminiz: ");
        scanf("%d", &islem);

        if (islem == 0)
        {
            printf("Program sonlandi.\n");
            break;
        }
        else if (islem == 1)
        {
            printf("Kac karakter eklemek istiyorsunuz:");
            scanf("%d", &number[counter]);
            append(number[counter], &text);
            process[counter] = 1;
            printf("\n");
            printStack(text);
            printf("\n");
            counter += 1;
        }
        else if (islem == 2)
        {
            printf("Kac karakter silmek istiyorsunuz:");
            scanf("%d", &number[counter]);
            delete(&text, &undoStack, number[counter]);
            process[counter] = 2;
            printf("\n");
            printStack(text);
            printf("\n");
            counter += 1;
        }
        else if (islem == 3)
        {
            counter -= 1;
            undo(&text, &undoStack, &redoStack, number[counter], process[counter]);
            printf("\n");
            printStack(text);
            printf("\n");
        }
        else if (islem == 4)
        {
            redo(&text, &undoStack, &redoStack, number[counter], process[counter]);
            printf("\n");
            printStack(text);
            printf("\n");
            counter += 1;
        }
    }
    return 0;
}

char pop(MyS **root)
{
    if (*root == NULL)
    {
        printf("Bu stack boş");
        return '\0';
    }
    char a;
    MyS *temp = (*root);
    a = (*root)->data;
    (*root) = (*root)->next;
    free(temp);
    return a;
}

void push(MyS **root, char data)
{
    if (*root == NULL)
    {
        *root = (MyS *)malloc(sizeof(MyS));
        (*root)->data = data;
        (*root)->next = NULL;
        return;
    }
    MyS *temp = (MyS *)malloc(sizeof(MyS));
    temp->data = data;
    temp->next = *root;
    *root = temp;
}

void printStack(MyS *root)
{
    if (root == NULL)
    {
        return;
    }
    printStack(root->next);
    printf("%c", root->data);
}

void append(int number, MyS **text)
{
    int i;
    char a;
    for (i = 0; i < number; i++)
    {
        printf("Lutfen girmek istediginiz karakteri giriniz:");
        scanf(" %c", &a);
        push(text, a);
    }
}

void delete(MyS **text, MyS **rootUndo, int number)
{
    int i;
    char a;
    for (i = 0; i < number; i++)
    {
        a = pop(text);
        push(rootUndo, a);
    }
}

void undo(MyS **text, MyS **rootUndo, MyS **rootRedo, int number, int process)
{
    char a;
    if (process == 1)
    {
        for (int i = 0; i < number; i++)
        {
            a = pop(text);
            push(rootRedo, a);
        }
    }
    else
    {
        for (int i = 0; i < number; i++)
        {
            a = pop(rootUndo);
            push(text, a);
        }
    }
}

void redo(MyS **text, MyS **rootUndo, MyS **rootRedo, int number, int process)
{
    char a;
    if (process == 1)
    {
        for (int i = 0; i < number; i++)
        {
            a = pop(rootRedo);
            push(text, a);
        }
    }
    else
    {
        for (int i = 0; i < number; i++)
        {
            a = pop(text);
            push(rootUndo, a);
        }
    }
}
