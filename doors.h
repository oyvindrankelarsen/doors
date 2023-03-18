#ifndef __DOORS_H
#define __DOORS_H

typedef struct
{
    int cardNumber; // fyra siffror
    int hasAccess;
    char dateAdded[11];
} Card;

// state
typedef struct
{
    Card *cards; // array
    int antal;   // hur många finns det i den
} CardLista;

#endif

void Access(CardLista *state);
void CreateCard(CardLista *state);
// FakeScan(CardLista *state);
void InputCard(Card *p);
void ListAllCards(CardLista *state);
void PrintCard(Card *p);
void RemoteOpen(CardLista *state);
