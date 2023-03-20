#ifndef __DOORS_H
#define __DOORS_H

typedef struct
{
    int cardNumber; // fyra siffror
    char dateAdded[11];
    int hasAccess;
    int isLoggedIn;
} Card;

// state
typedef struct
{
    Card *cards; // array
    int antal;   // hur många finns det i den
} CardLista;

#endif

void AddRemoveAccessMenu(CardLista *state);
void AdminMenu(CardLista *state);
void AddRemoveAccess(CardLista *state);
void CreateCard(CardLista *state);
void FakeScan(CardLista *state);
void InputCard(Card *p, CardLista *state);
void ListAllCards(CardLista *state);
void ListLoggedIn(CardLista *state);
void PrintCard(Card *p);
void RemoteOpen(CardLista *state);
