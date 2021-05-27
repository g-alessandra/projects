/*
1- Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
2- O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
3- O programa deve preencher um vetor de tamanho n com números aleatórios. Usar srand(time(NULL)); no inicio do programa.
4- Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.
5- Use a melhor lib para calcular quanto tempo cada algoritmo de ordenação levou para terminar: https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
6- No 1:1 vou perguntar sobre questões de desempenho relacionadas a esse exercício, então pense sobre desempenho, otimizações, avaliação de tempo, complexidade, hardware, etc
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *InsertionSort(int *vetor, int *v, int tam){
    for(int i=0; i<tam; i++){
        vetor[i] = v[i];
    }
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
    return vetor;
}

int *SelectionSort(int *vetor, int *v, int tam){
    for(int i=0; i<tam; i++){
        vetor[i] = v[i];
    }
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
    return vetor;
}

/*          ERRO        */
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
//    return vetor;
}

//int *MergeSort(int *vetor, tam){
//}

int *Insere(int vetor[],int tam){
    srand(time(0));
    for(int i = 0; i < tam; i++){
        vetor[i] = rand()%1000;
    }
    return vetor;
}

void Imprime(int vetor[],int tam){
    for(int i = 0; i < tam; i++){
        printf("%d ", vetor[i]);
    }
}

int main(){
    int *vetor = NULL;
    int *v = NULL;
    int tam;
    do{
        printf("Deseja gerar um novo vetor?\n S. Sim\n N. Não\n");
        if(getchar() == 'S'){
            printf("Qual o tamanho do vetor? ");
            scanf("%d", &tam);
            vetor = (int *)realloc(vetor,(sizeof(int)*(tam+1)));
            v = (int *)realloc(v,(sizeof(int)*(tam+1)));
            v = Insere(v,tam);
            printf(" V: ");
            Imprime(v,tam);
            printf("\n");
            
            printf("IS: ");
            vetor = InsertionSort(vetor,v,tam);
            Imprime(vetor,tam);
            printf("\n");
            
            printf("SS: ");
            vetor = SelectionSort(vetor,v,tam);
            Imprime(vetor,tam);
            printf("\n");
            
            printf("QS: ");
            for(int k=0; k<tam; k++){
                vetor[k] = v[k];
            }
            QuickSort(vetor, vetor[0], vetor[tam-1]);
            Imprime(vetor,tam);
            printf("\n");
            
            printf(" V: ");
            Imprime(v,tam);
            printf("\n");
            
            //relatorio
        }
        else{
            free(vetor);
            free(v);
            exit(1);
        }
    }while(getchar()!='N');
    exit(0);
}
