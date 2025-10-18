/**
 * @file main.c
 * @author Carlo Contardi
 * @brief Gestione di una Rubrica di contatti
 * @version 1.0
 * @date 2025-10-18
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char f_name[30];
    char l_name[60];
    char cell[20];
} Contact;
struct Node
{
    Contact contact;
    struct Node *next;
};
void insertInQueue(struct Node **head, Contact contact)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->contact = contact;
    new->next = NULL;
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        struct Node *tmp = *head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
}
void viewList(struct Node *head)
{
    while (head != NULL)
    {
        printf("\n|Nome: %s|\t|Cognome: %s|\t|Cell: %s|", head->contact.f_name, head->contact.l_name, head->contact.cell);
        head = head->next;
    }
    printf("\n");
}
void saveToFile(struct Node *head)
{
    FILE *f = fopen("contacts.csv", "w");
    if (f == NULL)
    {
        printf("\n Errore apertura file!\n");
        return;
    }
    while (head != NULL)
    {
        fprintf(f, "%s;%s;%s\n", head->contact.f_name, head->contact.l_name, head->contact.cell);
        head = head->next;
    }
    printf("\n I dati sono stati salvati su file.");
    printf("\n");
    fclose(f);
}
void loadFromFile(struct Node **head)
{
    FILE *f = fopen("contacts.csv", "r");
    if (f == NULL)
    {
        return;
    }
    Contact contact;
    while (fscanf(f, "%[^;];%[^;];%s\n", contact.f_name, contact.l_name, contact.cell) == 3)
    {

        insertInQueue(head, contact);
    }
    fclose(f);
}
void searchByLastName(struct Node *head, char last_name[60])
{
    Contact contact;
    int is_find = 0;
    while (head != NULL)
    {
        if (strcmp(head->contact.l_name, last_name) == 0)
        {
            printf("\n|Nome: %s|\t|Cognome: %s|\t|Cell: %s|", head->contact.f_name, head->contact.l_name, head->contact.cell);
            is_find = 1;
        }
        head = head->next;
    }
    if (is_find == 0)
    {
        printf("\nNon sono presenti Contatti con questo cognome");
    }
    printf("\n");
}

int main()
{
    Contact contact;
    char last_name[60];
    int opt;
    struct Node *contact_list = NULL;
    loadFromFile(&contact_list);
    do
    {

        printf("\n1 - Inserisci un contatto ");
        printf("\n2 - Visualizza i contatti ");
        printf("\n3 - Cerca un contatto per [cognome] ");
        printf("\n4 - Salva i dati su file ");
        printf("\n0 - Esci dal programma ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 0:
            // Nel caso l'utente non abbia salvato ed abbia aggiunto dei contatti
            // salviamo prima di uscire dal programma
            saveToFile(contact_list);
            printf("\n Arrivederci. ");
            break;
        case 1:
            printf("\nInserisci il nome : ");
            scanf("%s", contact.f_name);
            printf("\nInserisci il cognome : ");
            scanf("%s", contact.l_name);
            // TODO: Capitalize only the first letter
            printf("\nInserisci il numero di telefono : ");
            scanf("%s", contact.cell);
            insertInQueue(&contact_list, contact);
            break;
        case 2:
            viewList(contact_list);
            break;
        case 3:
            printf("\nInserisci il [cognome] da ricercare: ");
            scanf("%s", last_name);
            searchByLastName(contact_list, last_name);
            break;
        case 4:
            saveToFile(contact_list);
            break;
        default:
            printf("\nHai selezionato [%d], non è un'opzione valida.", opt);
        }
    } while (opt != 0);
    // liberariamo la memoria rimasta
    while (contact_list != NULL)
    {
        struct Nodo *tmp = contact_list;
        contact_list = contact_list->next;
        free(tmp);
    }
}