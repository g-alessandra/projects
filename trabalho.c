#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[10];
    int idade;
    int telefone;
}Dados;

typedef struct nodo{
    Dados dados;
    struct nodo *prox;
    struct nodo *anterior;
}Nodo;

typedef struct{
    int contador, encontrar, i, contadorOrdenada;
    char nomeProcurado[10];
    Nodo *inicio, *fim; //lista duplamente encadeada
    Nodo *inicioOrdenada, *fimOrdenada; //fila ordenada
    Nodo *percorrer, *aux, *aux2, *fimOrdenadaCopia; //auxiliares
}Controle;

void *incluir(Controle *pBuffer){ //insere no inicio da lista
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


void *apagar(Controle *pBuffer){
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
        for(pBuffer->percorrer = pBuffer->inicioOrdenada; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
            printf("Nome: %s |  ", pBuffer->percorrer->dados.nome); 
            printf("Idade: %d | ", pBuffer->percorrer->dados.idade); 
            printf("Telefone: %d \n", pBuffer->percorrer->dados.telefone); 
        }
    }
}


void ordenaI(Controle *pBuffer){ //insere no inicio da lista 
    pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){//percorre a lista pra inserir
    
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->prox = NULL;

        novo->dados = pBuffer->percorrer->dados;       

        if(pBuffer->inicioOrdenada == NULL){
            pBuffer->inicioOrdenada = novo;
            pBuffer->inicioOrdenada->anterior = NULL;
        }
        else{
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
        }
    
        pBuffer->fimOrdenada = novo;
    }
}


void ordenaAlfabetica(Controle *pBuffer){
    pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    pBuffer->contadorOrdenada = 0;    

    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){//percorre a lista pra inserir
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados;
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;//copia de fimOrdenada

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        
        else if((pBuffer->contadorOrdenada == 1) && (strcmp(novo->dados.nome, pBuffer->inicioOrdenada->dados.nome) < 0)){                 //insere no inicio, e so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                               //anterior do q tem sera o novo 
            novo->prox = pBuffer->inicioOrdenada;                                   //proximo do novo eh o q estava no fim;
            pBuffer->inicioOrdenada = novo;                                         //novo fica no inicio 
        }
        else if((pBuffer->contadorOrdenada >= 1) && (strcmp(novo->dados.nome, pBuffer->fimOrdenada->dados.nome) >= 0)){   //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{//tem + de 2 elementos, vai no meio ou inicio 
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (strcmp(novo->dados.nome, pBuffer->fimOrdenadaCopia->dados.nome) < 0 ); pBuffer->i -= 1){ //erro n1
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo

                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        //guarda o penultimo
                    pBuffer->aux2->prox = novo;                                 //prox do salvo eh o novo
                    
                    novo->anterior = pBuffer->aux2;                             //anterior do novo eh o salvo
                   
                    pBuffer->fimOrdenadaCopia->anterior = novo;                 //penultimo eh o novo
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;                     //prox do novo eh o ultimo

                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;           //original recebe 
                }
                else if(pBuffer->i == 1){         //novo fica depois inicio
                    pBuffer->aux2 = novo->prox;                                 //aux2 recebe prox de novo
                    pBuffer->aux2->anterior = novo->anterior;                   // anterior<-novo  <-aux2-> novo->prox
                    
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o segundo e o penultimo
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;
                    
                    novo->anterior = pBuffer->aux2;
                    
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;
                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo; 
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;//vai evitar lista infinita
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  

}

void ordenaAlfabeticaDecrescente(Controle *pBuffer){
    pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    pBuffer->contadorOrdenada = 0;    

    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){//percorre a lista pra inserir
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados;
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;//copia de fimOrdenada

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        
        else if((pBuffer->contadorOrdenada == 1) && (strcmp(novo->dados.nome, pBuffer->inicioOrdenada->dados.nome) < 0)){                 //insere no inicio, e so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                               //anterior do q tem sera o novo 
            novo->prox = pBuffer->inicioOrdenada;                                   //proximo do novo eh o q estava no fim;
            pBuffer->inicioOrdenada = novo;                                         //novo fica no inicio 
        }
        else if((pBuffer->contadorOrdenada >= 1) && (strcmp(novo->dados.nome, pBuffer->fimOrdenada->dados.nome) >= 0)){   //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{//tem + de 2 elementos, vai no meio ou inicio 
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (strcmp(novo->dados.nome, pBuffer->fimOrdenadaCopia->dados.nome) < 0 ); pBuffer->i -= 1){ //erro n1
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo

                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        //guarda o penultimo
                    pBuffer->aux2->prox = novo;                                 //prox do salvo eh o novo
                    
                    novo->anterior = pBuffer->aux2;                             //anterior do novo eh o salvo
                   
                    pBuffer->fimOrdenadaCopia->anterior = novo;                 //penultimo eh o novo
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;                     //prox do novo eh o ultimo

                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;           //original recebe 
                }
                else if(pBuffer->i == 1){         //novo fica depois inicio
                    pBuffer->aux2 = novo->prox;                                 //aux2 recebe prox de novo
                    pBuffer->aux2->anterior = novo->anterior;                   // anterior<-novo  <-aux2-> novo->prox
                    
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o segundo e o penultimo
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;
                    
                    novo->anterior = pBuffer->aux2;
                    
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;
                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo; 
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;//vai evitar lista infinita
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  
    
}


void ordenaIdade(Controle *pBuffer){
pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    pBuffer->contadorOrdenada = 0;    

    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){//percorre a lista pra inserir
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados;
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;//copia de fimOrdenada

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        
        else if((pBuffer->contadorOrdenada == 1) && (novo->dados.idade < pBuffer->inicioOrdenada->dados.idade)){                 //insere no inicio, e so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                               //anterior do q tem sera o novo 
            novo->prox = pBuffer->inicioOrdenada;                                   //proximo do novo eh o q estava no fim;
            pBuffer->inicioOrdenada = novo;                                         //novo fica no inicio 
        }
        else if((pBuffer->contadorOrdenada >= 1) && (novo->dados.idade >= pBuffer->fimOrdenada->dados.idade)){   //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{//tem + de 2 elementos, vai no meio ou inicio 
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (novo->dados.idade < pBuffer->fimOrdenadaCopia->dados.idade); pBuffer->i -= 1){ 
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo

                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        //guarda o penultimo
                    pBuffer->aux2->prox = novo;                                 //prox do salvo eh o novo
                    
                    novo->anterior = pBuffer->aux2;                             //anterior do novo eh o salvo
                   
                    pBuffer->fimOrdenadaCopia->anterior = novo;                 //penultimo eh o novo
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;                     //prox do novo eh o ultimo

                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;           //original recebe 
                }
                else if(pBuffer->i == 1){         //novo fica depois inicio
                    pBuffer->aux2 = novo->prox;                                 //aux2 recebe prox de novo
                    pBuffer->aux2->anterior = novo->anterior;                   // anterior<-novo  <-aux2-> novo->prox
                    
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o segundo e o penultimo
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;
                    
                    novo->anterior = pBuffer->aux2;
                    
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;
                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo; 
                    
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;//vai evitar lista infinita
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  
}


void ordenaIdadeDecrecente(Controle *pBuffer){
    
}


int main(){
    Controle *pBuffer;
    pBuffer = malloc(sizeof(Controle));

    if(pBuffer == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }

    pBuffer->contador = 0;
    pBuffer->contadorOrdenada = 0;
    
    pBuffer->inicio = NULL;
    pBuffer->fim = NULL;
    
    pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    
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
                printf("Escolha o parâmetro de ordenação desejado:\n"); 
                printf(" 1)Ordenação por ordem de inserção\n 2)Ordenação por ordem alfabética crescente\n 3)Ordenação por ordem alfabética decrescente\n 4)Ordenação por idade crescente\n 5)Ordenação por idade decrescente\n");
                scanf("%d", &pBuffer->i);
                switch (pBuffer->i){
                    case 1:
                        ordenaI(pBuffer);
                        break;
                    case 2:
                        ordenaAlfabetica(pBuffer);
                        break;
                    case 3:
                        ordenaAlfabeticaDecrescente(pBuffer);
                        break;
                    case 4:
                        ordenaIdade(pBuffer);
                        break;
                    case 5:
                        ordenaIdadeDecrecente(pBuffer);
                        break;
                }
                imprimir(pBuffer);
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
