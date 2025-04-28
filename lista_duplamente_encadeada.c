#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int value;
    struct Item *seguinte;
    struct Item *anterior;
}Item;

typedef struct {
    Item* primeiro;
    Item* ultimo;
    int qtd;
}Lista;

// Prototipações
void colocar(int value, Lista* lista);
Item* aloc(int value);
Lista* alocLista();
void percorrerFT(Lista *lista);
void percorrerTF(Lista *lista);

int main() {
    Lista* lista = alocLista();
    for (int i = 1; i <= 10; i++) {
        colocar(i, lista);
    }

    percorrerFT(lista);
    percorrerTF(lista);

    printf("Valores dentro da lista, quantidade: %d\n", lista->qtd);
    return 0;
}

void percorrerFT(Lista *lista) {
    if (lista->ultimo == NULL) return;
    printf("Percorrendo a lista de frente pra trás\n");
    Item *aux = lista->primeiro;
    while (aux != NULL) {
        printf("FT: %d\n", aux->value);
        aux = aux->seguinte;
    }
}

void percorrerTF(Lista *lista) {
    if (lista == NULL) return;
    if (lista->ultimo == NULL) return;
    printf("Percorrendo a lista de trás pra frente\n");
    Item *aux = lista->ultimo;
    while (aux != NULL) {
        printf("TF: %d\n", aux->value);
        aux = aux->anterior;
    }
}

void colocar(int value, Lista* lista) {
    Item* new = aloc(value);
    if (lista == NULL) return;
    lista->qtd++;
    if (lista->ultimo == NULL) {
        lista->ultimo = new;
        lista->primeiro = new;
        return;
    }
    lista->ultimo->seguinte = new;
    new->anterior = lista->ultimo;
    lista->ultimo = new;
}

Item* aloc(int value) {
    Item* new = (Item*) calloc(1, sizeof(Item));
    new->value = value;
    new->seguinte = NULL;
    new->anterior = NULL;
    return new;
}

Lista* alocLista() {
    Lista* new = (Lista*) calloc(1, sizeof(Lista));
    new->primeiro = NULL;
    new->ultimo = NULL;
    new->qtd = 0;
}
