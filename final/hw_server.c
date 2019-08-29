#include <rpc/rpc.h>
#include <dirent.h>
#include "tools.c"
#include <string.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

static int quantidade = 0;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int *func1_1_svc(struct params *parametros, struct svc_req *req) {
    printf("chegando %s\nby:%s\n", parametros->conteudo, parametros->usuario);
    static int ret = = quantidade + 1;
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
    printf("%s\n", parametros->conteudo);
    writeline(parametros->conteudo, file_to_write);
    printf ("Escrito!\n");
    fclose (file_to_write);
    quantidade +=1;
    return (&ret);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
struct arquivos *func2_1_svc(void *a, struct svc_req *req) {
    printf("chega aqui?\n");
    char *conteudo = NULL;
    quantidade = 0;
    static struct arquivos ret;
    ret.quantidade = quantidade;
    printf("chega aqui2?\n");
    char *current_directory = ".";
    DIR *directory = NULL;
    directory = opendir(current_directory);
    printf("chega aqui3?\n");
    if(directory == NULL)
        return NULL;
    printf("chega aqui4?\n");
    struct dirent *ent;
    printf("chega aqui5?\n");
    while((ent = readdir(directory)) != NULL){
        printf("arquivo...");
        if(strstr(ent->d_name, ".serv") != NULL){
            printf("achou!\t");
            FILE *file_to_read;
            file_to_read = fopen(ent->d_name, "r");
            conteudo = readline(file_to_read);
            fclose(file_to_read);
            strcpy(ret.arquivo[quantidade].conteudo, conteudo);
            ret.quantidade +=1;
            printf("procurando proximo...\n");
        }
    }
    printf("achou %d arquivos\n", ret.quantidade);
    for(int i = 0; i < ret.quantidade; ++i)
    {
        printf("%s\n", ret.arquivo[i].conteudo);
    }
    printf("chegou aqui?final\n");
    return &ret;   
}
