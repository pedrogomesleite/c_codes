#include <stdio.h>
#include <stdlib.h>

// Structs

typedef struct Item {
    int value;
    struct Item *next;
}Item;

typedef struct {
    Item* primeiro;
    Item* ultimo;
    int qtd;
}Fila;

// Prototipações
void enfileirar(int value, Fila* fila);
Item* desenfileira(Fila* fila);
int desenfileiraValue(Fila* fila);
Item* aloc(int value);
Fila* alocFila();

int main() {
    Fila* fila = alocFila();
    for (int i = 1; i <= 10; i++) {
        enfileirar(i, fila);
    }
    printf("Valores em fila, quantidade: %d\n", fila->qtd);
    for (int i = 1; i <= 10; i++) {
        printf("%d \n", desenfileiraValue(fila));
    }
    printf("Quantidade: %d\n", fila->qtd);
    return 0;
}

void enfileirar(int value, Fila* fila) {
    Item* new = aloc(value);
    if (fila == NULL) return;
    fila->qtd++;
    if (fila->ultimo == NULL) {
        fila->ultimo = new;
        fila->primeiro = new;
        return;
    }
    fila->ultimo->next = new;
    fila->ultimo = new;
}

Item* desenfileira(Fila* fila) {
    if (fila == NULL) return NULL;
    if (fila->primeiro == NULL) return NULL;
    fila->qtd--;
    Item* retorno = fila->primeiro;
    fila->primeiro = retorno->next;
    return retorno;
}

int desenfileiraValue(Fila* fila) {
    if (fila == NULL) return 0;
    if (fila->primeiro == NULL) return 0;
    fila->qtd--;
    Item* retorno = fila->primeiro;
    fila->primeiro = retorno->next;
    return retorno->value;
}

Item* aloc(int value) {
    Item* new = (Item*) calloc(1, sizeof(Item));
    new->value = value;
    new->next = NULL;
    return new;
}

Fila* alocFila() {
    Fila* new = (Fila*) calloc(1, sizeof(Fila));
    new->primeiro = NULL;
    new->ultimo = NULL;
    new->qtd = 0;
}
