#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

char *add_name(char *string){ //adiciona nome a listas
    printf("Digite o nome que deseja adicionar: "); //solicita o nome
    getchar(); //consome \n
    char *s = (char*)malloc(sizeof(char) * 100); //declaraçao da variavel auxiliar
    scanf("%[^\n]", s); //le o novo nome

    if (string == NULL){ //verifica se string ja possui algum conteudo
        string = (char *) malloc(sizeof(char) * (strlen(s) + 2));
        strcpy(string, s); //concatena as strings adicionando o novo nome no final
    }
    else{
        string = (char *) realloc(string, (strlen(string) + strlen(s) + 2)); //realoca o tamanho da string
        strcat(string, s); //concatena as strings adicionando o novo nome no final
    }

    strcat(string, "|");
         
    if(string == NULL){ //testa se consegui alocar a memoria
        printf("Erro!"); //caso nao tenha conseguido notifica o erro
        exit(1);
    }

    free(s);// desaloca s
    return string;
}

char *remove_name(char *string){
    if (string != NULL){
        printf("Digite o nome que deseja remover: "); //solicita o nome
        getchar();
        char *r = (char*)malloc(sizeof(char) * 100); // declaraçao variavel auxiliar
        scanf("%[^\n]", r); //le o nome a ser removido

        int encontrar = 0;//flag

        char *guarda = NULL; //string que vai guardar todos os nomes, exceto o removido 
        char *s = NULL; //usada para comparar com o nome a ser removido, armazena token temporariamente
        s = strtok(string, "|");
        while(s != NULL){
            if(strcmp (s, r) != 0){ //verifica se o token eh o nome a ser removido
                if (guarda == NULL){
                    guarda = (char *) malloc(sizeof(char) * (strlen(s) + 2)); //realoca o tamanho da string guarda
                    strcpy(guarda,s);
                }
                else{                
                    guarda = (char *) realloc(guarda, (strlen(guarda) + strlen(s) + 2)); //realoca o tamanho da string guarda
                    strcat(guarda,s);
                }
                strcat(guarda,"|");
            }
            else{
                encontrar = 1;
            }
   	        s = strtok(NULL, "|");
        }
        
        if(encontrar != 1){
            printf("Nome não encontrado!\n");               
        }

        if (guarda != NULL){
            string = (char *) realloc(string, sizeof(char) * (strlen(guarda) + 1));
            strcpy(string, guarda); //copia guarda para string
        }
        else{
      	    string = (char *) realloc(string, sizeof(char)*0);
        }        
        free(s);    
        free(guarda);
        free(r);
    }

    else{
        printf("Lista vazia!\n");               
    }
	return string;
}
 

void show(char *string){ //lista os nomes presentes na string
    if(string != NULL){
        while (*string){
            if(*string != '|'){
	            putchar(*string);
	        }
	        else{
	            putchar('\n');
	        }
            string++;
        }
    }
    else{
        printf("Lista vazia!\n");
    }     
}


 
int main(){
    
    char *string = NULL;//declaração do ponteiro para a string

    do{
        printf("Escolha uma opção:\n 1)Adicionar\n 2)Remover\n 3)Listar\n 4)Sair\n"); //menu

        switch(getchar()){
            case '1': 
                string = add_name(string);
                break;
            case '2':
                string = remove_name(string);
                break;
            case '3':
                show(string);
                break;
            case '4':
                free(string); //desaloca na memoria
                exit(1);
            default: 
                printf("Opção inexistente\n");
        }
    }while(getchar());
    exit(0);
}

