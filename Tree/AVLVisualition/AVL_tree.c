#include <stdio.h>
#include <stdlib.h>



typedef struct Tree{
    int data;
    int height;
    struct Tree *right;
    struct Tree *left;
}MyBTree;

int calculate_height(MyBTree *left,MyBTree *right);
MyBTree *addTree(int data, MyBTree *root);
void pre_order(MyBTree *root);
void in_order(MyBTree *root);
void post_order(MyBTree *root);
MyBTree *delete_tree(MyBTree *root,int data);
int height(MyBTree *n);
MyBTree *rightRotation(MyBTree *root);
MyBTree *leftRotation(MyBTree *root);
int getBalance(MyBTree *n);
void printTree(MyBTree *root, int space);


int main(){
    MyBTree *root = NULL;
    int secim, deger;

    while(1){
        printf("\n===== AVL TREE MENU =====\n");
        printf("1. Eleman Ekle\n");
        printf("2. Eleman Sil\n");
        printf("3. Agaci Goster\n");
        printf("4. Preorder\n");
        printf("5. Inorder\n");
        printf("6. Postorder\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if(secim == 1){
            printf("Eklenecek deger: ");
            scanf("%d", &deger);
            root = addTree(deger, root);
            printf("\nAVL Tree:\n");
            printTree(root, 0);
        }
        else if(secim == 2){
            printf("Silinecek deger: ");
            scanf("%d", &deger);
            root = delete_tree(root, deger);
            printf("\nAVL Tree:\n");
            printTree(root, 0);
        }
        else if(secim == 3){
            printTree(root, 0);
        }
        else if(secim == 4){
            pre_order(root);
        }
        else if(secim == 5){
            in_order(root);
        }
        else if(secim == 6){
            post_order(root);
        }
        else if(secim == 0){
            printf("Cikis yapiliyor...\n");
            break;
        }
        else{
            printf("Gecersiz secim!\n");
        }
    }
    return 0;
}



MyBTree *addTree(int data, MyBTree *root){
    if (root == NULL) {
        root = (MyBTree*)malloc(sizeof(MyBTree));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
        return root;
    }
    else if (data >= root->data) {
        root->right = addTree(data, root->right);
    }
    else {
        root->left = addTree(data,root->left);
    }
    root->height = calculate_height(root->left, root->right); 
    int balance = getBalance(root);
    if (balance > 1) {
        if (getBalance(root->left) >= 0){
            return rightRotation(root);
        } 
        else{
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0){
            return leftRotation(root);
        }
        else{
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    return root;
}

void pre_order(MyBTree *root){
    if(root == NULL){
        return;
    }
    printf("%d |height: %d\n", root->data, root->height);
    pre_order(root->left);
    pre_order(root->right);
}

void in_order(MyBTree *root){
    if(root == NULL){
        return;
    }
    in_order(root->left);
    printf("%d |height: %d\n", root->data, root->height);
    in_order(root->right);
}

void post_order(MyBTree *root){
    if(root == NULL){
        return;
    }
    post_order(root->left);
    post_order(root->right);
    printf("%d |height: %d\n", root->data, root->height);

}

int getBalance(MyBTree *n){
    if (n == NULL) 
        return 0;
    return height(n->left) - height(n->right);
}

MyBTree *delete_tree(MyBTree *root, int data) {
    if (root == NULL){
        return root;
    }
    if (data < root->data) {
        root->left = delete_tree(root->left, data);
    } 
    else if (data > root->data) {
        root->right = delete_tree(root->right, data);
    } 
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            MyBTree *temp;
            if(root->left != NULL){
                temp = root->left;
            }
            else if(root->right != NULL){
                temp = root->right;
            }
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
            else{
                *root = *temp; 
            }
            free(temp);
        } else {
            MyBTree *iter = root->right;
            while (iter->left != NULL) {
                iter = iter->left;
            }
            root->data = iter->data;
            root->right = delete_tree(root->right, iter->data);
        }
    }

    if (root == NULL) return root;
    root->height = calculate_height(root->left, root->right); 
    int balance = getBalance(root);
    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rightRotation(root);
        } else {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return leftRotation(root);
        } else {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    return root;
}

int height(MyBTree *n){
    if(n == NULL){
        return -1;
    }
    return n->height;
}
    
MyBTree *rightRotation(MyBTree *root){
    MyBTree *A = root->left;
    MyBTree *B = A->right;

    root->left = B;
    A->right = root;

    root->height = calculate_height(root->left,root->right);
    A->height = calculate_height(A->left,A->right);

    return A;
}

MyBTree *leftRotation(MyBTree *root){
    MyBTree *A = root->right;
    MyBTree *B = A->left;

    root->right = B;
    A->left = root;

    root->height = calculate_height(root->left,root->right);
    A->height = calculate_height(A->left,A->right);

    return A;
}

int calculate_height(MyBTree *left,MyBTree *right){
    if(height(left) > height(right)){
        return height(left) + 1;
    }
    else{
        return height(right) + 1;
    }
}

void printTree(MyBTree *root, int space){
    if(root == NULL){
        return;
    }

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for(int i = 5; i < space; i++){
        printf(" ");
    }
    printf("%d(h=%d)\n", root->data, root->height);

    printTree(root->left, space);
}