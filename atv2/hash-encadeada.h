typedef struct Encad {
	int chave;
    struct Encad* proximo;
} Encad;

void inicializarTabelaE(Encad* tabela, int posicoes);
void inserirElementoE(int chave, Encad* tabela, int posicoes);
void imprimirTabelaE(Encad* tabela, FILE* arquivo, int qntComparacoes, int posicoes);
int buscarElementoE(int chave, Encad* tabela, int* qntComparacoes, int posicoes);