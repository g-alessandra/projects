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
    i = iniV; //o i recebe o indice da posicao inicial
    j = fimV; //j recebe o indice da posicao final
    mid = vetor[(iniV + fimV)/2]; //o pivo vai ser o elemento presenter na posição do meio do vetor
    do{                                 //enquato o j for > i;
        while(vetor[i] < mid){ //percorre o vetor incremento i enquanto o elemento no vetor[i] for menor q o pivo incrementando o i
            i++;
        }
        while(mid < vetor[j]){  //depois percorre decrementando j enquanto pivo for menor vetor[j]
            j--;
        }
        if(i <= j) { //caso i seja menor q j, ou seja o pivo ainda n esta ordenado
            aux = vetor[i];          //faz a troca entre eles
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }while(j > i); //quado o pivo estiver no lugar correto sai do laço
    if(iniV < j){ //caso ainda tenha elementos desordenados a esq do pivo entra no 1 if caso seja a esq entra no segundo if
       QuickSort(vetor,iniV,j); //entao é chamada a funçao quick sort novamente, até q tanto o lado esq quanto direto do pivo estejjam ordenados
    }
    if(i < fimV){
       QuickSort(vetor,i,fimV);
    }
}

void merge(int *vetor, int ini, int meio, int fim) { //recebe *vetr, indicie do inicio, meio e do fim
    int i = ini, j = meio+1, comAux = 0, tam = fim-ini+1; //j vai receber meio+1
    int *vetAux;                                    //gera um vetor auxiliar
    vetAux = (int*)malloc(tam * sizeof(int));
    while(i <= meio && j <= fim){   // enquanto as duas metades n chegarem no limite
        if(vetor[i] < vetor[j]) {    //vai testar se v[i] é menor q v[j], e vai copiar o menor deles pro vetor auxiliar 
            vetAux[comAux] = vetor[i];
            i++;
        } else { 
            vetAux[comAux] = vetor[j];
            j++;
        }
        comAux++;
    }
    while(i <= meio){  //se ainda tiver elementos na primeira metade copia eles pro auxiliar
        vetAux[comAux] = vetor[i];
        comAux++;
        i++;
    }
    while(j <= fim) {   //e depois copia os da segunda metade, se houver
        vetAux[comAux] = vetor[j];
        comAux++;
        j++;
    }
    for(comAux = ini; comAux <= fim; comAux++){  //após copia os dados do vetor aux pro vetor
        vetor[comAux] = vetAux[comAux-ini];
    }
    free(vetAux); //e desaloca o vetor auxilar
}

void MergeSort(int *vetor, int ini, int fim){ //recebe *vetor, indice do inicio e fim
    if (ini < fim) { //se inicio for menor q o fim, ou seja tem mais de um elemento
        int meio = (fim+ini)/2; //calcua o meio
        MergeSort(vetor, ini, meio); //e chama merge sort pra primeira metade
        MergeSort(vetor, meio+1, fim); //depois pra segunda metade
        merge(vetor, ini, meio, fim); //e então aciona a função merge
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
