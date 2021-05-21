#include <stdio.h>
#include <time.h>

void InsertionSort(int *vetor){
    
}

void SelectionSort(int *vetor){
    
}

void QuickSort(int *vetor){
    
}

void MergeSort(int *vetor){
    
}

void Insere(int *vetor, int dado){
    
}

void Imprime(int *vetor){
    
}

int main(){
    int *vetor = NULL;
    printf("MENU:\n 1.Insertion Sort\n 2.Selection Sort\n 3.Quick Sort\n 4.Merge Sort\n 5.Sair\n");
    do{
        switch(getchar()){
            case '1':
                InsertionSort(vetor);
                break;
            case '2':
                SelectionSort(vetor);
                break;
            case '3':
                QuickSort(vetor);
                break;
            case '4':
                MergeSort(vetor);
                break;
            case '5':
                free(vetor);
                exit(1);
                break;
        }
    }while(getchar()!='5');
    exit(0);
}
