typedef struct inglesPortugues{
    char *palavra;
    struct inglesPortugues *dir,*esq;
}InglesPortugues;

typedef struct info{
    char *palavraPortugues;
    int unidade;
    InglesPortugues *traducaoIngles;
}Info;

typedef struct portuguesIngles{
    Info info1,info2;

    int qtdInfo;
    struct portuguesIngles *dir,*cen,*esq;
}PortugesIngles;