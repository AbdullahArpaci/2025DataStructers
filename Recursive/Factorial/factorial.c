#include <stdio.h>
#include <stdlib.h>

int fact(int n);

int main(void){
    printf("%d\n", fact(5));
    return 0;
}

int fact(int n){
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fact(n - 1);
}