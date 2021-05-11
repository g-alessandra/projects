#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int conteudo;
    struct nodo *esq; *dir;
}Nodo;

//
void insere(Nodo *raiz){
    
}

void imprime(Nodo *raiz){
    if(raiz != NULL){
        printf("%d(", raiz->conteudo);
        imprime(raiz->esq);
        imprime(raiz->dir);
        printf(")");   
    }
}
//

int Altura(Nodo* raiz){
    int iEsq, iDir;
    if (raiz == NULL){
        return 0;
    }
    
    iEsq = Altura(raiz->Esq);
    iDir = Altura(raiz->Dir);
    
    if(iEsq > iDir){
        return iEsq + 1;
    }
    else{
        return iDir + 1;
    }
}

int FB (Nodo* raiz){
    if(raiz == NULL){
        return 0;
    }
    return Altura(pRaiz->pEsq) -Altura(pRaiz->pDir);
}

void limpa(Nodo *raiz){ //limpa arvore
    if(!raiz){
        free(raiz->esq);
        free(raiz->dir);
        free(raiz);
    }
}

void RSE(Nodo **raizP){ //rotação simples esq
    Nodo *pAux;
    pAux = (*raizP)->dir;
    (*raizP)->dir = pAux->esq;
    pAux->esq = (*raizP);
    (*raizP) = pAux;
}

void RSD(Nodo **raizP){ //rotação simples dir
    Nodo *pAux;
    pAux = (*raizP)->esq;
    (*raizP)->esq = pAux->dir;
    pAux->dir = (*raizP);
    (*raizP) = pAux;
}



void caso1(Nodo *raiz){ //insere aleatoriamente
        printf("Informe quantos nodos deseja adicionar: ");
        scanf("%d", &numNodo);
        
        for(int i = 0; i < numNodo; i++){
            //insere nodo
            random = rand()%1000;
            insere(*raiz; random);
        
            //verfica balanceamento
            
            //imprime arvore
            imprime(raiz);
        }
    limpa(raiz);    
}

// void caso2(Nodo *raiz){ //insere pré estabelecidos
//
// }

int main(){
    Nodo *raiz = NULL;
    int numNodo, random;
    srand(time(0));
    
    do{
        printf("MENU:\n 1.Primeiro Cenário\n 2.Segundo Cenário\n 3.Sair\n");
        switch (getchar()){
            case 1:
                caso1(*raiz);
                break;
            case 2:
                //caso2(*raiz);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    
    }while(getchar != '3');
    
    exit 0;
}
