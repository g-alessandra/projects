#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void Insere(int *vetor,int tam){ //recebe o ponteiro pro vetor e o tamanho do vetor
    srand(time(0));
    for(int i = 0; i < tam; i++){ //preenche o vetor usando valores aleatorios
        vetor[i] = rand()%1000;
    }
}

void Imprime(int *vetor,int tam){//recebe o ponteiro pro vetor e o tamanho do vetor
    for(int i = 0; i < tam; i++){ //percorre o vetor imprimimindo o valor presente na
        printf("%d ", vetor[i]);
    }
}

void Copia(int *vetor, int *v, int tam){ //para garantir que o vetor orignal nao fosse alterado nas ordenações foi criada a função copia, que ira gera um novo vetor
    for(int i=0; i<tam; i++){                   //igual ao gerado pela função inserir
        vetor[i] = v[i];
    }
}

void Verifica(int *vetor, int tam) {//vai percorrer o vetor verificando se ele ta em ordem crescente, para isso vai comparar o elemento atual com seu anterior
    int erro = 0;
    for(int i = 1; i < tam; i++) {
        if(vetor[i-1] > vetor[i]){
            erro = 1;
        }
    }
    if(erro == 0){ //e informar se o resultado esta correto
        printf("\nO resultado está correto!\n");
    }
    else{ 
        printf("\nO resultado está incorreto!\n");
    }
}

void InsertionSort(int *vetor, int tam){ //ele percorre um vetor de elementos da esquerda para a direita e à medida que avança os elementos mais à esquerda ficam ordenados. 
    int j, aux;
    for(int i = 1; i < tam; i++){ //para isso a cada posição a partir da segunda é comparada com os elementos anteriores e colocada na posição correta. 
        j = i - 1;
        aux = vetor[i];
        while((j >= 0) && (aux < vetor[j])){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
}

void SelectionSort(int *vetor, int tam){ //consiste em selecionar o menor item e colocar na primeira posição, selecionar o segundo menor item e colocar na segunda posição, 
    int j, min, aux = 0;                     // segue estes passos até que reste um único elemento.
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

int main(){
    int tam;
    struct timeval begin, end;
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
                gettimeofday(&begin, 0); //inicio get time
                InsertionSort(vetor,tam);
                gettimeofday(&end, 0); //fim get time
                Imprime(vetor,tam);
                Verifica(vetor,tam);
                printf("Time measured: %f seconds.\n", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6);

                printf("\nSelection Sort: ");
                Copia(vetor,v,tam);
                gettimeofday(&begin, 0); //inicio get time
                SelectionSort(vetor,tam);
                gettimeofday(&end, 0); //fim get time
                Imprime(vetor,tam);
                Verifica(vetor,tam);
                printf("Time measured: %f seconds.\n", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6);
                
                printf("\nQuick Sort: ");
                Copia(vetor,v,tam);
                gettimeofday(&begin, 0); //inicio get time
                QuickSort(vetor, 0, tam-1);
                gettimeofday(&end, 0); //fim get time
                Imprime(vetor,tam);                
                Verifica(vetor,tam);
                printf("Time measured: %f seconds.\n", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6);

                printf("\nMerge Sort: ");
                Copia(vetor,v,tam);
                gettimeofday(&begin, 0); //inicio get time
                MergeSort(vetor, 0, tam-1);
                gettimeofday(&end, 0); //fim get time
                Imprime(vetor,tam); 
                Verifica(vetor,tam);
                printf("Time measured: %f seconds.\n", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6);

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
