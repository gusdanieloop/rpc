#include <stdio.h>
#include <rpc/rpc.h>
#include "tools.c"
#include <unistd.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int main (int argc, char *argv[]) {
    int contador_arquivo = 1;
    FILE *file_to_read, *file_to_write;
    char filename[50];
    char nome_do_arquivo[256];
	
    // Estrutura RPC de comunicação
	CLIENT *cl;

	// Parâmetros das funçcões
    struct params parametros;
   // parametros.conteudo = (char *) malloc(256*sizeof(char));
   // parametros.usuario = (char *) malloc(256*sizeof(char));
    char *conteudo_arquivo = NULL;
	
    // Retorno das funções
    int   *meu_numero = NULL;
    struct arquivos *retorno = NULL;


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
    //printf("eoq\n");
    fclose(file_to_read);
	// Atribuições de valores para os parâmetros
    strcpy (parametros.conteudo, conteudo_arquivo);
    strcpy (parametros.usuario, argv[2]);
    parametros.contador = contador_arquivo;
    contador_arquivo+=1;

    // Chamadas das funções remotas
    //printf ("Chamando funcao\n");
    //printf("so pra ter ctz...\n%s\nby:%s\n", parametros.conteudo, parametros.usuario);
	meu_numero = func1_1(&parametros, cl);
    if (meu_numero == NULL) {
            printf("nossa\n");
	    clnt_perror(cl,argv[1]);
	    exit(1);
	}
    //printf("puts\n");
    //printf ("Retorno funcao (%d)\n", *meu_numero);

    //procurando se tem coisa nova no servidor
    int polling = 1;
    char contador[12];
    while(polling){
        retorno = func2_1(NULL, cl);
        //printf("chegou no cliente!\n");
        //printf("%d arquivos\n", retorno->quantidade);
        //printf("%s\n", retorno->arquivo[0].conteudo );
        for(int i = 0; i < retorno->quantidade; ++i){
            //printf("Cont: %d\nConteudo: %s",i, retorno->arquivo[i].conteudo);
            strcpy(nome_do_arquivo, "");
            strcat(nome_do_arquivo, argv[2]);
            sprintf(contador, "%d", contador_arquivo);
            strcat(nome_do_arquivo, contador);
            strcat(nome_do_arquivo, ".client0");
            sprintf(contador, "%d", *meu_numero);
            strcat(nome_do_arquivo, contador);
            file_to_write = fopen(nome_do_arquivo,"w");
            //printf ("Escrevendo...\n");
            writeline(retorno->arquivo[i].conteudo, file_to_write);
            //printf ("Escrito!\n");
            fclose (file_to_write);
            contador_arquivo+=1;
        }
        printf("deseja buscar no servidor novamente? 1- SIM 0- NÃO\n");
        scanf("%d", &polling);
    }
	return 0;
}
