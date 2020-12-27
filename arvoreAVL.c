#include <stdio.h>
#include <stdlib.h>

int maior(int a, int b){
    if(a>b) return a; 
    return b;
}

typedef struct arvore{
	int chave;
	int alt;
	struct arvore *filhoEsq;
	struct arvore *filhoDir;
}arvoreAVL;

arvoreAVL* novoNo(int dado){
	arvoreAVL* no = malloc(sizeof(arvoreAVL));
	no->chave = dado;
	no->filhoEsq = NULL;
	no->filhoDir = NULL;
	no->alt = 1;
	return no;
}

int altura(arvoreAVL *raiz){
    if(raiz==NULL) return 0;
    return 1 + maior(altura(raiz->filhoEsq),altura(raiz->filhoDir));
}

int fatorDeBalanceamento(arvoreAVL *no){
	if(no==NULL) return 0;
    return (altura(no->filhoEsq) - altura(no->filhoDir));
}

void imprimirInOrderFB(arvoreAVL* no){
	if(no==NULL) return;
	else{
		imprimirInOrderFB(no->filhoEsq);
		printf("%d(%d) ", no->chave, fatorDeBalanceamento(no));
		imprimirInOrderFB(no->filhoDir);
	}
}

arvoreAVL* rotacaoParaDireita(arvoreAVL* raiz){
	arvoreAVL* auxP = raiz->filhoEsq;
	arvoreAVL* auxU = auxP->filhoDir;

	auxP->filhoDir = raiz;
	raiz->filhoEsq = auxU;

	raiz->alt = maior(altura(raiz->filhoEsq), altura(raiz->filhoDir)) +1;
	auxP->alt = maior(altura(auxP->filhoEsq), altura(auxP->filhoDir)) +1;

	return auxP;
}

arvoreAVL* rotacaoParaEsquerda(arvoreAVL* raiz){
	arvoreAVL* auxP = raiz->filhoDir;
	arvoreAVL* auxU = auxP->filhoEsq;

	auxP->filhoEsq = raiz;
	raiz->filhoDir = auxU;

	raiz->alt = maior(altura(raiz->filhoEsq), altura(raiz->filhoDir)) +1;
	auxP->alt = maior(altura(auxP->filhoEsq), altura(auxP->filhoDir))+1;
}

arvoreAVL* inserirAVL(arvoreAVL* no, int dado){
	if(no==NULL){
		return (novoNo(dado));
	}
	else{
		if(dado < no->chave) no->filhoEsq = inserirAVL(no->filhoEsq, dado);
		else no->filhoDir = inserirAVL(no->filhoDir, dado);
	}

	no->alt = 1 + maior(altura(no->filhoEsq), altura(no->filhoDir));

	int fb = fatorDeBalanceamento(no);

	if(fb>1 && dado < no->filhoEsq->chave) return rotacaoParaDireita(no);

	if(fb<-1 && dado>no->filhoDir->chave) return rotacaoParaEsquerda(no);

	//rotacao dupla a direita
	if(fb>1 && dado>no->filhoEsq->chave){
		no->filhoEsq = rotacaoParaEsquerda(no->filhoEsq);
		return rotacaoParaDireita(no);
	}

	//rotacao dupla a esquerd
	if(fb<-1 && dado<no->filhoDir->chave){
		no->filhoDir=rotacaoParaDireita(no->filhoDir);
		return rotacaoParaEsquerda(no);
	}

	return no;
}

int main(){
	arvoreAVL *raiz;

	/*
	Exemplo apresentado no item (a) do exercício
	A árvore é impressa com o seu fator de balanceamento
	O resultado está conforme o demonstrado no relatório */
	
	raiz = inserirAVL(raiz, 5);
    raiz = inserirAVL(raiz, 4);
    raiz = inserirAVL(raiz, 3);
    raiz = inserirAVL(raiz, 6);
    raiz = inserirAVL(raiz, 7);
    raiz = inserirAVL(raiz, 8);
    raiz = inserirAVL(raiz, 8);
    imprimirInOrderFB(raiz);
    printf("\n");
}