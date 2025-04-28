#include <stdio.h>
#include <stdlib.h>

// Structs

typedef struct Item {
    int value;
    struct Item *next;
}Item;

typedef struct {
    Item* primeiro;
    int qtd;
}Pilha;

// Prototipações
void push(int value, Pilha* pilha);
Item* pop(Pilha* pilha);
int popValue(Pilha* pilha);
Item* aloc(int value);
Pilha* alocPilha();

int main() {
    Pilha* pilha = alocPilha();
    for (int i = 1; i <= 10; i++) {
        push(i, pilha);
    }
    printf("Valores em fila, quantidade: %d\n", pilha->qtd);
    for (int i = 1; i <= 10; i++) {
        printf("%d \n", popValue(pilha));
    }
    printf("Quantidade: %d\n", pilha->qtd);
    return 0;
}

void push(int value, Pilha* pilha) {
    Item* new = aloc(value);
    if (pilha == NULL) return;
    pilha->qtd++;
    if (pilha->primeiro == NULL) {
        pilha->primeiro = new;
        return;
    }
    new->next = pilha->primeiro;
    pilha->primeiro = new;
}

Item* pop(Pilha* pilha) {
    if (pilha == NULL) return NULL;
    if (pilha->primeiro == NULL) return NULL;
    pilha->qtd--;
    Item* retorno = pilha->primeiro;
    pilha->primeiro = retorno->next;
    return retorno;
}

int popValue(Pilha* pilha) {
    if (pilha == NULL) return 0;
    if (pilha->primeiro == NULL) return 0;
    pilha->qtd--;
    Item* retorno = pilha->primeiro;
    pilha->primeiro = retorno->next;
    return retorno->value;
}

Item* aloc(int value) {
    Item* new = (Item*) calloc(1, sizeof(Item));
    new->value = value;
    new->next = NULL;
    return new;
}

Pilha* alocPilha() {
    Pilha* new = (Pilha*) calloc(1, sizeof(Pilha));
    new->primeiro = NULL;
    new->qtd = 0;
}
