typedef struct Encad {
	int chave;
    struct Encad* proximo;
} Encad;

void inicializarTabelaE(Encad* tabela);
void inserirElementoE(int chave, Encad* tabela);
void imprimirTabelaE(Encad* tabela, FILE* arquivo, int qntComparacoes);
int buscarElementoE(int chave, Encad* tabela, int* qntComparacoes);