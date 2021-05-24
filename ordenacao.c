/*
1- Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
2- O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
3- O programa deve preencher um vetor de tamanho n com números aleatórios. Usar srand(time(NULL)); no inicio do programa.
4- Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.
5- Use a melhor lib para calcular quanto tempo cada algoritmo de ordenação levou para terminar: https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
6- No 1:1 vou perguntar sobre questões de desempenho relacionadas a esse exercício, então pense sobre desempenho, otimizações, avaliação de tempo, complexidade, hardware, etc
*/

#include <stdio.h>
#include <time.h>

int *InsertionSort(int *vetor, int tam){
    int j, aux;
    for(int i = 1; i < tam; i++){
        j = i - 1;
        aux = vetor[i];
        while((j >= 0) && (aux < vetor[i])){
            vetor[i+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
    return vetor;
}

void SelectionSort(int vetor[], int tam){
    int j, min, min_id, aux = 0; 
    for (int i = 0; i < tam -1; i++){ 
        min = i; 
        for (j = i+1; j < tam; j++){ 
            if (vetor[j] < vetor[min]){
                min = vetor[j];
                min_id = j;
            }
        }
        aux = vetor[i];
        vetor[i] = vetor[min_id];
        vetor[min_id] = aux;
        min_id = i+1;
    } 
}

void QuickSort(int vetor[], left, right){
    int mid,tmp, i, j;
    i = left;
    j = right;
    mid = data[(left+ right)/2]; 
    do{ 
        while(data[i] < mid){ 
            i++;
        }
        while(mid< data[j]){ 
            j--;
        }
        if(i <= j) {
            tmp= data[i];
            data[i] = data[j];
            data[j] = tmp;
            i++;
            j--;
        }
    }while(i <= j);
    if(left< j){
        Quicksort(data,left,j);
    }
    if(i < right){
        Quicksort(data,i,right);
    }
}

int *MergeSort(int *vetor, tam){
        
}

int *Insere(int *vetor){
    for(int i = 0; i < tam; i++){
        
    }
}

void Imprime(int *vetor){
    
}

int main(){
    int *vetor = NULL;
    int tam;
    printf("MENU:\n 1.Gerar vetor\n 2.Sair\n");
    do{
        switch(getchar()){
            case '1':
                printf("Qual o tamanho do vetor? ");
                scanf("%d", tam);
                vetor = Insere(vetor, tam);
                InsertionSort(vetor,tam);
                Imprime(vetor);
                break;
            case '2':
                free(vetor);
                free(ordenar);
                exit(1);
                break;
        }
    }while(getchar()!='5');
    exit(0);
}
