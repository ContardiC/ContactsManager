#include <stdio.h>
#include <stdlib.h>

struct Nodo
{
    int valore;
    struct Nodo *next;
};

void inserisciInTesta(struct Nodo **head, int val)
{
    struct Nodo *nuovo = malloc(sizeof(struct Nodo));
    nuovo->valore = val;
    nuovo->next = *head;
    *head = nuovo;
}
void stampaLista(struct Nodo *head)
{
    while (head != NULL)
    {
        printf("%d ", head->valore);
        head = head->next;
    }
    printf("NULL \n");
}

int main()
{
    struct Nodo *lista = NULL;
    printf("\n Stampo la lista senza aver fatto inserimenti: ");
    stampaLista(lista);
    inserisciInTesta(&lista, 10);
    inserisciInTesta(&lista, -20);
    inserisciInTesta(&lista, 30);
    printf("\nLista dopo inserimenti ");
    stampaLista(lista);
}