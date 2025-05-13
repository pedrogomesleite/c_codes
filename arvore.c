#include <stdio.h>
#include <stdlib.h>

typedef struct Node  {
    int value;
    int p;
    struct Node * pai;
    struct Node * nextE;
    struct Node * nextD;
}Node;

Node *alocaArvore(int *val, int qtd);
void printArvore(Node *raiz);
Node *alocaNode(int value, Node *pai, int p);
void inserirBinario(int value, Node * raiz, int p);
void printArvoreMelhor(Node *raiz, char *last);
Node *buscaBinaria(int value, Node* raiz);
int deletaBinario(int value, Node* raiz);
Node *achaCandidatoE(Node *raiz);
Node *achaCandidatoD(Node *raiz);

int main() {
    int qtd = 6;
    int val[] = {16, 20, 2, 1, 17, 18};
    Node *arvore = alocaArvore(val, qtd);
    printArvore(arvore);
    printArvoreMelhor(arvore, ":");
    Node *achei = buscaBinaria(17, arvore);
    if (achei != NULL) printf("\n Valor buscado: %d\n", achei->value);
    printf("\nValor deletado: %d\n", deletaBinario(20, arvore));
    // printArvoreMelhor(arvore, ":");
    printArvore(arvore);
    return 0;
}

int deletaBinario(int value, Node* raiz) {
    if (raiz == NULL) return 0;
    Node *minus = buscaBinaria(value, raiz);
    if (minus->nextD != NULL) {
        Node *candidato = achaCandidatoD(minus);
        printf("valor x%d\n", candidato->value);
        
        if (candidato->nextE != NULL) {
            if (candidato->pai != minus) {
                candidato->nextE->pai = candidato->pai;
                candidato->nextE->p = candidato->p;
            }
        }
        candidato->nextE = minus->nextE;
        candidato->pai = minus->pai;
        candidato->p = minus->p;
        candidato->pai->nextE = candidato;
    }
    else if (minus->nextE != NULL) {
        Node *candidato = achaCandidatoE(minus);
        printf("valor x%d\n", candidato->value);
        if (candidato->nextD != NULL) {
            if (candidato->pai != minus) {
                candidato->nextD->pai = candidato->pai;
                candidato->nextD->p = candidato->p;
            }
        } 
        if (candidato->pai == minus) {
            candidato->pai = minus->pai;
            candidato->nextD = minus->nextD;
            minus->pai = candidato;
            candidato->p = minus->p;
            candidato->pai->nextE = candidato;
        }  else {
            candidato->pai = minus->pai;
            candidato->nextD = minus->nextD;
            candidato->nextE = minus->nextE;
            minus->pai = candidato;
            candidato->p = minus->p;
            candidato->pai->nextE = candidato;
        }
        
        // printf("valor x%d %d\n", );
    }

    minus->nextD = NULL;
    minus->nextE = NULL;
    int ret = minus->value;
    free(minus);
    return ret;
}

Node *achaCandidatoD(Node *raiz) {
    if (raiz == NULL) return NULL;
    if (raiz->nextD == NULL) return raiz;
    achaCandidatoD(raiz->nextD);
}

Node *achaCandidatoE(Node *raiz) {
    if (raiz == NULL) return NULL;
    if (raiz->nextE == NULL) return raiz;
    achaCandidatoE(raiz->nextE);
}

Node *alocaArvore(int *val, int qtd) {
    if (val == NULL) return NULL;
    if (qtd == 0) return NULL;
    Node *raiz = alocaNode(val[0], NULL, 0);
    for (int i = 1; i < qtd; i++) {
        inserirBinario(val[i], raiz, 1);
    }
    return raiz;
}

Node *buscaBinaria(int value, Node* raiz) {
    if (raiz == NULL) return NULL;
    if (raiz->value == value) return raiz;
    if (value < raiz->value) {
        if (raiz->nextE == NULL) return NULL;
        return buscaBinaria(value, raiz->nextE);
    } else if (value > raiz->value) {
        if (raiz->nextD == NULL) return NULL;
        return buscaBinaria(value, raiz->nextD);
    }
}

void printArvoreMelhor(Node *raiz, char *last) {
    if (raiz == NULL) return;

    printArvoreMelhor(raiz->nextE, "┌");

    for (int i = 0; i < raiz->p * 4; i++) printf(" ");

    printf("%s", last);
    printf("%d", raiz->value);

    if (raiz->nextE == NULL && raiz->nextD == NULL) {
        printf("\n");
    } else if (raiz->nextE == NULL) {
        printf("┐\n");
    } else if (raiz->nextD == NULL) {
        printf("┘\n");
    } else {
        printf("┤\n");
    }

    // Reset de cor
    printf("\033[0m");

    printArvoreMelhor(raiz->nextD, "└");
}

void printArvore(Node *raiz) {
    if (raiz == NULL) return;
    printArvore(raiz->nextE);
    printf("%d\n", raiz->value);
    printArvore(raiz->nextD);
}

Node *alocaNode(int value, Node *pai, int p) {
    Node *new = (Node*) malloc(sizeof(Node));
    new->value = value;
    new->nextD = NULL;
    new->nextE = NULL;
    new->pai = pai;
    new->p = p;
}

void inserirBinario(int value, Node * raiz, int p) {
    if (raiz == NULL) return;
    if (value < raiz->value) {
        if (raiz->nextE == NULL) {
            raiz->nextE = alocaNode(value, raiz, p);
        }
        inserirBinario(value, raiz->nextE, ++p);
    } else if (value > raiz->value) {
        if (raiz->nextD == NULL) {
            raiz->nextD = alocaNode(value, raiz, p);
        }
        inserirBinario(value, raiz->nextD, ++p);
    }
}

