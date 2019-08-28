#include <stdio.h>
#include <rpc/rpc.h>
#include "tools.h"

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int main (int argc, char *argv[]) {
    int contador = 1;
    FILE *file_to_read;
    char filename[50];
	
    // Estrutura RPC de comunicação
	CLIENT *cl;

	// Parâmetros das funçcões
    struct params parametros;
    parametros.conteudo = (char *) malloc(256*sizeof(char));
    char *conteudo_arquivo = NULL;
	
    // Retorno das funções
    int   *ret_funcao = NULL;


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
    sprintf(filename, "%s.chat", argv[2]);
    fileread = fopen(filename, "r");
    if(fileread == NULL){
        printf("Erro ao abrir o arquivo %s", filename);
        exit(1);
    }
    conteudo_arquivo = readline(fileread); //uma linha só
    fclose(fileread);
	// Atribuições de valores para os parâmetros
	strcpy (parametros.conteudo, conteudo_arquivo);
    strcpy (parametros.usuario, argv[1]);
    parametros.contador = contador;
    contador+=1;

    // Chamadas das funções remotas
    printf ("Chamando funcao\n");
	ret_funcao = func1_1(&parametros, cl);
    if (ret_funcao == NULL) {
	    clnt_perror(cl,argv[1]);
	    exit(1);
	}
    printf ("Retorno funcao (%d)\n", *ret_funcao);
	return 0;
}
