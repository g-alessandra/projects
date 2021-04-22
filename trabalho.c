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

typedef struct{ //estrutura do NodoPessoa = Nodo
    Dados dados;
    struct Nodo *prox;
    struct Nodo *anterior;
}Nodo;

typedef struct{
    int contador, encontrar;
    char nomeProcurado[10];
    Nodo *inicio;
    Nodo *fim;
    Nodo *percorrer;
    Nodo *ordenada;
    Nodo *aux;
    Nodo *aux2;
}Controle;

void incluir(void *pBuffer){ //insere no inicio da lista
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


/*void apagar(void *pBuffer){
    if(*(int*)(pBuffer) == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("Digite o nome do usuário que deseja apagar: "); 
        getchar();
        scanf("%[^\n]", (char *)(pBuffer + (3)*sizeof(int)));

        *(int *)(pBuffer + (1)*sizeof(int)) = 0; //encontrar
        
        percorrer = inicio;
    
        for(*(int *)(pBuffer + (2)*sizeof(int)) = 0; *(int *)(pBuffer + (2)*sizeof(int)) < *(int *)(pBuffer); *(int *)(pBuffer + (2)*sizeof(int))+=1){
            
            if(strcmp(percorrer->dados.nome, (char *)(pBuffer + (3)*sizeof(int))) == 0){
                if(*(int *)(pBuffer) == 1){ //se eh o unico elemento
                    inicio = NULL;
                    fim = NULL;
                }
                else{
                    if(percorrer == inicio){ //eh o primeiro
                        percorrer = percorrer->prox;
                        percorrer->anterior = NULL;
                        
                        inicio = percorrer;
                    }
                    else{
                        if(percorrer == fim){ //eh o ultimo
                            percorrer = percorrer->anterior;
                            percorrer->prox = NULL;
                            
                            fim = percorrer;
                        }
                        else{ //ta no meio
                            aux = percorrer->anterior; //guarda o anterior
                            aux->prox = percorrer->prox; //aponta o proximo para proximo após o apagado
                            aux2 = percorrer->prox; //guarda o proximo
                            aux2->anterior = percorrer->anterior;
                        }
                    }
                }

                *(int *)(pBuffer + (1)*sizeof(int)) = 1; //foi encontrado
                *(int *)(pBuffer) -= 1; //contador
                *(int *)(pBuffer + (2)*sizeof(int)) = *(int *)(pBuffer); //completa o for, sai do loop
            }
            
            percorrer = percorrer->prox; //avança percorrer
            
        }
        
        if(*(int *)(pBuffer + (1)*sizeof(int)) != 1){
            printf("Usuário não encontrado!\n");    
        }
    }
}*/


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


/*funçoes de ordenar
void ordenaI(void *pBuffer){
    ordenada = inicio;
}


void ordenaA(void *pBuffer){
   aux = inicio;

    for(percorrer = inicio; percorrer != NULL; percorrer = percorrer->prox){
        while(aux->prox != NULL){
            if(percorrer->dados.idade > aux->dados.idade){
                ordenada = percorrer;
            }
            aux=aux->prox;
        }
        //falta remover o nodo aramazendo do aux
        ordenada = ordenada->prox;
    }
}
*/

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
               // apagar(pBuffer);
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
