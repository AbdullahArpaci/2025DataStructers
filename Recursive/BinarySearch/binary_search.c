#include <stdio.h>
#include <stdlib.h>



void _binary_search(int number,int numbers[],int left,int right);


int main(){
    int numbers[10] = {5,8,9,10,11,15,16,19,20,85};
    int target = 90;
    _binary_search(target,numbers,0,9);
    return 0;
}



void _binary_search(int number,int numbers[],int left,int right){
    if(left > right){
        printf("Aranan eleman bulunamadi\n");
        return;
    }

    int middle;
    middle = (right + left)/2;

    if(number>numbers[middle]){
        _binary_search(number,numbers,middle+1,right);
    }
    else if(number < numbers[middle]){
        _binary_search(number,numbers,left,middle-1);
    }
    else{
        printf("Aranan numara bulundu");
    }
}