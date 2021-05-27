/*
1- Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
2- O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
3- O programa deve preencher um vetor de tamanho n com números aleatórios. Usar srand(time(NULL)); no inicio do programa.
4- Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.
5- Use a melhor lib para calcular quanto tempo cada algoritmo de ordenação levou para terminar:
https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
6- No 1:1 vou perguntar sobre questões de desempenho relacionadas a esse exercício, então pense sobre desempenho, otimizações, avaliação de tempo, complexidade, hardware, etc
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Insere(int *vetor,int tam){
    srand(time(0));
    for(int i = 0; i < tam; i++){
        vetor[i] = rand()%1000;
    }
}

void Imprime(int *vetor,int tam){
    for(int i = 0; i < tam; i++){
        printf("%d ", vetor[i]);
    }
}

void Copia(int *vetor, int *v, int tam){
    for(int i=0; i<tam; i++){
        vetor[i] = v[i];
    }
}

void InsertionSort(int *vetor, int tam){
    int j, aux;
    for(int i = 1; i < tam; i++){
        j = i - 1;
        aux = vetor[i];
        while((j >= 0) && (aux < vetor[j])){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
}

void SelectionSort(int *vetor, int tam){
    int j, min, aux = 0; 
    for (int i = 0; i < tam -1; i++){ 
        min = i; 
        for (j = i+1; j < tam; j++){ 
            if (vetor[j] < vetor[min]){
                min = j;
            }
        }
        if(i != min){
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
}

void QuickSort(int *vetor, int iniV, int fimV){
    int mid, aux, i, j;
    i = iniV;
    j = fimV;
    mid = vetor[(iniV + fimV)/2]; 
    do{ 
        while(vetor[i] < mid){ 
            i++;
        }
        while(mid < vetor[j]){ 
            j--;
        }
        if(i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }while(j > i);
    if(iniV < j){
       QuickSort(vetor,iniV,j);
    }
    if(i < fimV){
       QuickSort(vetor,i,fimV);
    }
}

void merge(int *vetor, int ini, int meio, int fim) {
    int i = ini, j = meio+1, comAux = 0, tam = fim-ini+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(i <= meio && j <= fim){
        if(vetor[i] < vetor[j]) {
            vetAux[comAux] = vetor[i];
            i++;
        } else {
            vetAux[comAux] = vetor[j];
            j++;
        }
        comAux++;
    }
    while(i <= meio){  //tem elementos na primeira metade
        vetAux[comAux] = vetor[i];
        comAux++;
        i++;
    }
    while(j <= fim) {   //tem elementos na segunda metade
        vetAux[comAux] = vetor[j];
        comAux++;
        j++;
    }
    for(comAux = ini; comAux <= fim; comAux++){  
        vetor[comAux] = vetAux[comAux-ini];
    }
    free(vetAux);
}

void MergeSort(int *vetor, int ini, int fim){
    if (ini < fim) {
        int meio = (fim+ini)/2;

        MergeSort(vetor, ini, meio);
        MergeSort(vetor, meio+1, fim);
        merge(vetor, ini, meio, fim);
    }
}

void Tempo(){
    
}

int main(){
    int tam;
    do{
        printf("Deseja gerar um novo vetor?\n S. Sim\n N. Não\n");
        switch(getchar()){
            case 'S':
                printf("Qual o tamanho do vetor? ");
                scanf("%d", &tam);
                int *vetor = (int *)malloc((sizeof(int)*(tam+1)));
                int *v = (int *)malloc((sizeof(int)*(tam+1)));    
                Insere(v,tam);
                
                printf("\nVetor Original: ");
                Imprime(v,tam);
                
                printf("\n\nInsertion Sort: ");
                Copia(vetor,v,tam);
                InsertionSort(vetor,tam);
                Imprime(vetor,tam);
//                printf("Tempo de execução: %f\n", );
                
                printf("\nSelection Sort: ");
                Copia(vetor,v,tam);
                SelectionSort(vetor,tam);
                Imprime(vetor,tam);
//                printf("Tempo de execução: %f\n", );
                
                printf("\nQuick Sort: ");
                Copia(vetor,v,tam);
                QuickSort(vetor, 0, tam-1);
                Imprime(vetor,tam);
//                printf("Tempo de execução: %f\n", );

                printf("\nMerge Sort: ");
                Copia(vetor,v,tam);
                MergeSort(vetor, 0, tam-1);                
                Imprime(vetor,tam);
//                printf("Tempo de execução: %f\n", );
                
                free(vetor);
                free(v);
                break;
            case 'N':
                exit(1);    
            default:
                printf("Opção inválida!\n");
        }
        printf("\n");
    }while(getchar());
    exit(0);
}
