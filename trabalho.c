/******************************************************************************
Nenhuma variável pode ser declarado em todo o programa, somente ponteiros que apontam para dentro do pBuffer.
Todos os dados do programa devem ser guardados dentro do pBuffer.
O usuário escolhe um parâmetro de ordenação e uma fila ordenada é criada e depois imprime
--Implementar a base de dados da agenda usando lista duplamente ligada
--Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[10];
    int idade;
    int telefone;
}Dados;

typedef struct nodo{ //estrutura do NodoPessoa = Nodo
    Dados dados;
    struct nodo *prox;
    struct nodo *anterior;
}Nodo;

typedef struct{
    int contador, encontrar, i;
    char nomeProcurado[10];
    Nodo *inicio;
    Nodo *fim;
    Nodo *percorrer;
    Nodo *ordenada;
    Nodo *aux;
    Nodo *aux2;
}Controle;

void incluir(Controle *pBuffer){ //insere no inicio da lista
    Nodo *novoNodo;
    novoNodo = (Nodo *)malloc(sizeof(Nodo));
    novoNodo->prox = NULL;

    if(novoNodo == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }
    
    printf("Digite os dados do usuário que deseja adicionar:\nNome: "); 
    getchar(); 
    scanf("%[^\n]", novoNodo->dados.nome); 
    printf("Idade: "); 
    getchar(); 
    scanf("%d", &novoNodo->dados.idade); 
    printf("Telefone: "); 
    getchar(); 
    scanf("%d", &novoNodo->dados.telefone);       
    

    if(pBuffer->inicio == NULL){
        pBuffer->inicio = novoNodo;
        pBuffer->inicio->anterior = NULL;
    }
    else{
        novoNodo->anterior = pBuffer->fim;
        pBuffer->fim->prox = novoNodo;
    }
    
    pBuffer->fim = novoNodo;
    
    pBuffer->contador += 1; //contador
}


void apagar(Controle *pBuffer){
    if(pBuffer->contador == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("Digite o nome do usuário que deseja apagar: "); 
        getchar();
        scanf("%[^\n]", pBuffer->nomeProcurado);

        pBuffer->encontrar = 0; //encontrar
        
        pBuffer->percorrer = pBuffer->inicio;
    
        for(pBuffer->i = 0; pBuffer->i < pBuffer->contador; pBuffer->i+=1){
            
            if(strcmp(pBuffer->percorrer->dados.nome, pBuffer->nomeProcurado) == 0){
                if(pBuffer->contador == 1){ //se eh o unico elemento
                    pBuffer->inicio = NULL;
                    pBuffer->fim = NULL;
                }
                else{
                    if(pBuffer->percorrer == pBuffer->inicio){ //eh o primeiro
                        pBuffer->percorrer = pBuffer->percorrer->prox;
                        pBuffer->percorrer->anterior = NULL;
                        
                        pBuffer->inicio = pBuffer->percorrer;
                    }
                    else{
                        if(pBuffer->percorrer == pBuffer->fim){ //eh o ultimo
                            pBuffer->percorrer = pBuffer->percorrer->anterior;
                            pBuffer->percorrer->prox = NULL;
                            
                            pBuffer->fim = pBuffer->percorrer;
                        }
                        else{ //ta no meio
                            pBuffer->aux = pBuffer->percorrer->anterior; //guarda o anterior
                            pBuffer->aux->prox = pBuffer->percorrer->prox; //aponta o proximo para proximo após o apagado
                            pBuffer->aux2 = pBuffer->percorrer->prox; //guarda o proximo
                            pBuffer->aux2->anterior = pBuffer->percorrer->anterior;
                        }
                    }
                }

                pBuffer->encontrar = 1; //foi encontrado
                pBuffer->contador -= 1; //contador
                pBuffer->i = pBuffer->contador; //completa o for, sai do loop
            }
            
            pBuffer->percorrer = pBuffer->percorrer->prox; //avança percorrer
            
        }
        
        if(pBuffer->encontrar != 1){
            printf("Usuário não encontrado!\n");    
        }
    }
}


void buscar(Controle *pBuffer){
    if(pBuffer->contador == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("Digite o nome do usuário que deseja buscar: "); 
        getchar();
        scanf("%[^\n]", pBuffer->nomeProcurado);

        pBuffer->encontrar = 0; //encontrar
    
        printf("    AGENDA\n");
        for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
            if(strcmp(pBuffer->percorrer->dados.nome, pBuffer->nomeProcurado) == 0){
                printf("Nome: %s |  ", pBuffer->percorrer->dados.nome); 
                printf("Idade: %d | ", pBuffer->percorrer->dados.idade); 
                printf("Telefone: %d \n", pBuffer->percorrer->dados.telefone); 
                
                pBuffer->encontrar = 1;
            }
        }
        
        if(pBuffer->encontrar != 1){
            printf("Usuário não encontrado!\n");    
        }
    }
}


void imprimir(Controle *pBuffer){  
    if(pBuffer->contador == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("    AGENDA\n");
        for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
            printf("Nome: %s |  ", pBuffer->percorrer->dados.nome); 
            printf("Idade: %d | ", pBuffer->percorrer->dados.idade); 
            printf("Telefone: %d \n", pBuffer->percorrer->dados.telefone); 
        }
    }
}

/*void imprimir2(void *pBuffer){  
    if(*(int*)(pBuffer) == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("    AGENDA ordenada\n");
        for(percorrer = ordenada; percorrer != NULL; percorrer = percorrer->prox){
            printf("Nome: %s |  ", percorrer->dados.nome); 
            printf("Idade: %d | ", percorrer->dados.idade); 
            printf("Telefone: %d \n", percorrer->dados.telefone); 
        }
    }
}*/


/*funçoes de ordenar: a cada elemento da lista encadeada verifica a posição correta e insere na fila 

void ordenaI(void *pBuffer){
    ordenada = inicio;
}


void ordenaA(void *pBuffer){
   pBuffer->aux = pBuffer->inicio;

    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
        while(pBuffer->aux->prox != NULL){
            if(pBuffer->percorrer->dados.idade > pBuffer->aux->dados.idade){
                pBuffer->ordenada = pBuffer->percorrer;
            }
            pBuffer->aux=aux->prox;
        }
        //remover o nodo aramazendo do aux
        pBuffer->ordenada = pBuffer->ordenada->prox;
    }
}*/


int main(){
//    void *pBuffer = (void *)malloc((3)*sizeof(int) + (10)*(sizeof(char)) + (6)*sizeof(Nodo)); //contador de pessoas, flag encontrar, nome(buscar/remover), ...;
    Controle *pBuffer;
    pBuffer = malloc(sizeof(Controle));

    if(pBuffer == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }

    pBuffer->contador = 0;
    pBuffer->inicio = NULL;
    pBuffer->fim = NULL;
    pBuffer->percorrer = NULL;
    pBuffer->ordenada = NULL;

    do{
        printf("Escolha uma opção:\n 1)Incluir\n 2)Apagar\n 3)Busar\n 4)Listar\n 5)Sair\n"); //menu

        switch(getchar()){
            case '1': 
                incluir(pBuffer);
                break;
            case '2':
                apagar(pBuffer);
                break;
            case '3':
                buscar(pBuffer);
                break;
            case '4':
/*                printf("Escolha o parâmetro de ordenação desejado:\n 1)Ordenação por ordem alfabética \n 2)Ordenação por inserção\n 3)Ordenação por prioridade\n");
                switch case(getchar()){
                    case '1':
                        ordenaA(pBuffer);
                    case '2':
                        ordenaI(pBuffer);
                    case '3':
                        ordenaP(pBuffer)
                }
*/                imprimir(pBuffer);

//                  ordenaA(pBuffer);
//                 imprimir2(pBuffer);
                break;    
            case '5':
                free(pBuffer);
                exit(1);
            default: 
                printf("Opção inexistente\n");
        }

    }while(getchar());

    exit(0);
}
