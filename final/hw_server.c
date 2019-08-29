#include <rpc/rpc.h>
#include "tools.c"

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int *func1_1_svc(struct params *parametros, struct svc_req *req) {
    static int ret = 0;
    FILE *file_to_write;
    char *nome_do_arquivo = (char *) malloc(256*sizeof(char));
    strcpy(nome_do_arquivo, "");
    strcat(nome_do_arquivo, parametros->usuario);
    strcat(nome_do_arquivo, "-");
    char contador[12];
    sprintf(contador, "%d", parametros->contador);
    strcat(nome_do_arquivo, contador);
    strcat(nome_do_arquivo, ".serv");
    file_to_write = fopen(nome_do_arquivo,"w");
    printf ("Escrevendo...\n");
    printf("%s\n\n\n----------\n%s\n", *parametros->conteudo, parametros->conteudo);
    writeline(*parametros->conteudo, file_to_write);
    printf ("Escrito!\n");
    fclose (file_to_write);
    return (&ret);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*params *func2_1_svc(void *a, struct svc_req *req) {
    struct params ret;
    
}*/
