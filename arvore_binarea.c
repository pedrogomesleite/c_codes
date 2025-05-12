#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int profundidade;
    struct Node *nextE;
    struct Node *nextD;
}Node;

Node *alocaNode(int value, int p);
Node *alocaArvore(int *valores, int qtd);
void insertBinario(int value, Node* raiz, int p);
void printArvore(Node *raiz);

int main() {
    int qtd = 6;
    int valores[] = {10, 5, 2, 6, 19, 20};

    Node* arvore = alocaArvore(valores, qtd);
    printArvore(arvore);

    return 0;
}

Node *alocaArvore(int *valores, int qtd) {
    if (valores == NULL) return NULL;
    if (qtd == 0) return NULL;
    Node *raiz = alocaNode(valores[0], 0);
    for (int i = 1; i < qtd; i++) {
        insertBinario(valores[i], raiz, 1);
    }
    return raiz;
}

void printArvore(Node *raiz) {
    if (raiz == NULL) return;
    printArvore(raiz->nextE);
    for (int i = 0; i < raiz->profundidade * 4; i++) printf(" ");
    if (raiz->profundidade == 0) printf("R:");
    printf("%d\n", raiz->value);
    printArvore(raiz->nextD);

}

Node *alocaNode(int value, int p) {
    Node *new = (Node*) malloc(sizeof(Node));
    new->value = value;
    new->profundidade = p;
    new->nextE = NULL;
    new->nextD = NULL;
    return new;
}

void insertBinario(int value, Node* raiz, int p) {
    if (raiz == NULL) return;
    if (value < raiz->value) {
        
        if (raiz->nextE == NULL) raiz->nextE = alocaNode(value, p);
        insertBinario(value, raiz->nextE, ++p);
    } else if (value > raiz->value) {

        if (raiz->nextD == NULL) raiz->nextD = alocaNode(value, p);
        insertBinario(value, raiz->nextD, ++p);
    }
}