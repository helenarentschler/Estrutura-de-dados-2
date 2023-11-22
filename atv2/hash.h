typedef struct Hash {
	int chave;
	char status;
} Hash;

int inserirElemento(int chave, Hash* tabela, int posicoes, int* qnt);
void imprimirTabela(Hash* tabela, int posicoes, FILE* arquivo, int qntComparacoes);
void inicializarTabela(Hash* tabela, int posicoes);
int buscarElemento(int chave, Hash* tabela, int posicoes, int* qntComparacoes);
Hash* calcularCarga(Hash* tabela, int* qnt, int* posicoes);
