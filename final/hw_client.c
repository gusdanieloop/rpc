#include <stdio.h>
#include <rpc/rpc.h>
#include "tools.c"
//#include <windows.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int main (int argc, char *argv[]) {
    int contador = 1;
    FILE *file_to_read, *file_to_write;
    char filename[50];
	
    // Estrutura RPC de comunicação
	CLIENT *cl;

	// Parâmetros das funçcões
    struct params parametros;
    //parametros.conteudo = (char *) malloc(256*sizeof(char));
    //parametros.usuario = (char *) malloc(256*sizeof(char));
    char *conteudo_arquivo = NULL;
	
    // Retorno das funções
    int   *ret_funcao = NULL;
    //struct params retorno;


	// Verificação dos parâmetros oriundos da console	
	if (argc != 3) {
		printf("ERRO: ./client <hostname> <msg>\n");
		exit(1);
	}

	// Conexão com servidor RPC
	cl = clnt_create(argv[1], PROG, VERS, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

    //arquivo
    sprintf(filename, "chat%s.chat", argv[2]);
    file_to_read = fopen(filename, "r");
    if(file_to_read == NULL){
        printf("Erro ao abrir o arquivo %s", filename);
        exit(1);
    }
    conteudo_arquivo = readline(file_to_read); //uma linha só
    fclose(file_to_read);
	// Atribuições de valores para os parâmetros
	strcpy (parametros.conteudo, conteudo_arquivo);
    strcpy (parametros.usuario, argv[1]);
    parametros.contador = contador;
    contador+=1;

    // Chamadas das funções remotas
    printf("%s")
    printf ("Chamando funcao\n");
	ret_funcao = func1_1(&parametros, cl);
    if (ret_funcao != NULL) {

	    clnt_perror(cl,argv[1]);
	    exit(1);
	}
    printf ("Retorno funcao (%d)\n", *ret_funcao);

    //procurando se tem coisa nova no servidor
    /*while(true){
        sleep(10);
        retorno = func2_1(NULL, cl);
        if (retorno != NULL) {
            char *nome_do_arquivo = (char *) malloc(256*sizeof(char));
            strcpy(nome_do_arquivo, "");
            strcat(nome_do_arquivo, argv[1]);
            char contador[12];
            sprintf(contador, "%d", retorno.contador);
            strcat(nome_do_arquivo, ".client");
            strcat(nome_do_arquivo, contador);
            file_to_write = fopen(nome_do_arquivo,"w");
            printf ("Escrevendo...\n");
            writeline(*retorno.conteudo, file_to_write);
            printf ("Escrito!\n");
            flose (file_to_write);
        }
    }*/
	return 0;
}
