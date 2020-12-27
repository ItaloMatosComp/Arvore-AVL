#include <stdio.h>
#include <stdlib.h>

int maior(int a, int b);

typedef struct arvore arvoreAVL;

arvoreAVL* novoNo(int dado);

int altura(arvoreAVL *raiz);

int fatorDeBalanceamento(arvoreAVL *no);

void imprimirInOrderFB(arvoreAVL* no);

arvoreAVL *rotacaoParaDireita(arvoreAVL* raiz);

arvoreAVL *rotacaoParaEsquerda(arvoreAVL* raiz);

arvoreAVL *inserirAVL(arvoreAVL* no, int dado);
