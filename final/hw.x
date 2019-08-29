struct arquivos{
    params arquivo[256];
    int quantidade;
};

struct params{
    char   conteudo[256];
    char   usuario[256];
    int contador;
};

program PROG {
	version VERS {
		int    func1(params) = 1;
        arquivos func2(void) = 2;
	} = 1;
} = 0x31279999;
