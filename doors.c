#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doors.h"
#include "safeinput.h"
#include "menu.h"



// const double pi = 3.1415927;
// #define  pi 3.1415927

// 2. titta på en struct i runtime struct tm (time)
// allokera malloc realloc free

// om inte access: 0 avbryt, 1 void CreateCard(CardLista *state)
void Access(CardLista *state)
{
    CreateCard(state);
}

void CreateCard(CardLista *state)
{
    // HEAP Vi sköter birth and death
    // föda = malloc
    // föda en till Emploee
    //    employee -> sist i arrayen
    //    antal + 1

    // state->employees 9850
    // state->antal =2
    // state->antal = state->antal + 1;
    state->antal++;
    if (state->antal == 1) // DEN FÖRSTA NÅNSIN  Employee = 150
        state->cards = (Card *)malloc(1 * sizeof(Card));
    else
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));

    // Paxat upp utrymme för en till SIST
    //  state->antal = 3     3 *150
    //  state->employees = 1000 -> 1450
    //  state->employees[state->antal-1] ÄR NY PAXAD - "tom"
    //  &state->employees[state->antal-1] -> Minnes 1300

    InputCard(&state->cards[state->antal - 1]);
}

void FakeScan(CardLista *state)
{
}

// lägg in 1212 has access, 1213 No access
void InputCard(Card *p)
{
    GetInputInt("New cardnumber:\n", &(p->cardNumber));
    GetInputInt("Has access?: 0 or 1:\n", &(p->hasAccess));
    //  lägg in dateAdded
    struct tm *tm;
    time_t t;
    char str_date[100]; // HÄR ligger datumet rätt formaterat i de 10 första tecknen följt av null
    t = time(NULL);
    tm = localtime(&t);
    strftime(str_date, sizeof(str_date), "%Y-%m-%d", tm);
    strcpy(p->dateAdded, str_date);
}
// Lista ALLA kortnummer och skriv om dom har access eller INTE
// (1212 har access, 1213 har nekats samt DATUM när dom lades till i systemet, Added to the system: )
void ListAllCards(CardLista *state)
{
    printf("Listing all cards\n*******************\n");// skrev bara ut första
    for (int i = 0; i < state->antal; i++)
    {
        // Employee *p = state->cards;
        // Employee *toPrint = &p[i];
        // PrintEmployee(toPrint);

        PrintCard(&state->cards[i]);
    }
}

void PrintCard(Card *p)
{
    printf("%d", p->cardNumber);
    (p->hasAccess) ? printf(" Access   ") : printf(" No Access");
    printf(" %s\n", p->dateAdded);
}

// Dörren ska vara öppen (grön lampa) i 3 sekunder
void RemoteOpen(CardLista *state)
{
}

int main()
{
    /*
  Att tänka på:
  - buffer overflow (inmatning) - GetInput - kontroll char namn[10] -> 20 ->  IG
  - stack overflow (flöde)   -> meny -> add -> meny  lösningen loopar + return
  - inga globala variabler ABSOLUT KRAV -> IG
  */

    CardLista state;
    state.cards = NULL;
    state.antal = 0;
    //= {NULL,0};

    while (1)
    {
        // int sel = getMenuSelection();
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");
        // TODO input
        int sel = 0;

        GetInputInt("Ange val:", &sel);
        if (sel == 1)
            RemoteOpen(&state);
        else if (sel == 2)
            ListAllCards(&state);
        else if (sel == 3)
            Access(&state);
        else if (sel == 4)
        {
            // skriv till fil
            break;
        }
        else if (sel == 9)
            FakeScan(&state);
    }

    free(state.cards);
    return 0;
}
