struct params{
    char    *conteudo;
    char    *usuario;
    int contador;
};

program PROG {
	version VERS {
		int    func1(params) = 1;
        params func2(void) = 2;
	} = 1;
} = 0x31279999;
