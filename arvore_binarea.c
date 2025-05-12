#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int profundidade;
    struct Node *nextE;
    struct Node *nextD;
}Node;

Node *alocaNode(int value, int p);
Node *alocaArvore(int *valores, int qtd);
void insertBinario(int value, Node* raiz, int p);
void printArvore(Node *raiz, char* last);
void printProfundidade(Node *raiz);

int main() {
    // int qtd = 6;
    // int valores[] = {10, 5, 2, 6, 19, 20};

    int qtd = 100;
    int valores[] = {
        15, 8, 23, 42, 4, 16, 33, 7, 91, 55,
        12, 99, 31, 5, 67, 81, 40, 29, 77, 60,
        1, 100, 3, 14, 38, 27, 49, 11, 63, 90,
        26, 13, 88, 73, 59, 18, 30, 94, 6, 75,
        20, 41, 19, 87, 28, 21, 39, 53, 44, 36,
        10, 62, 24, 46, 58, 17, 32, 35, 80, 25,
        85, 70, 47, 95, 66, 9, 61, 48, 84, 68,
        2, 43, 22, 79, 76, 96, 92, 98, 57, 54,
        34, 50, 83, 65, 37, 64, 45, 97, 86, 51,
        56, 74, 93, 71, 82, 78, 52, 89, 69, 72
    };

    Node* arvore = alocaArvore(valores, qtd);
    printArvore(arvore, ":");
    // printf("\n\n\n");
    // printProfundidade(arvore);

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

void printArvore(Node *raiz, char *last) {
    if (raiz == NULL) return;

    printArvore(raiz->nextE, "┌");

    int maxDepth = 15; // defina um máximo esperado de profundidade
    int step = (255 / maxDepth); // quanto diminuir G e B por nível

    int green = 255 - raiz->profundidade * step;
    int blue = 255 - raiz->profundidade * step;

    if (green < 0) green = 0;
    if (blue < 0) blue = 0;

    printf("\033[38;2;255;%d;%dm", green, blue);   // Vermelho com intensidade baseada na profundidade

    for (int i = 0; i < raiz->profundidade * 4; i++) printf(" ");


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

    printArvore(raiz->nextD, "└");
}


void printProfundidade(Node *raiz) {
    if (raiz == NULL) return;
    printProfundidade(raiz->nextE);
    for (int i = 0; i < raiz->profundidade * 4; i++) printf(" ");
    if (raiz->profundidade == 0) printf("R:");
    printf("%d\n", raiz->profundidade);
    printProfundidade(raiz->nextD);

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