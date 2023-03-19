#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doors.h"
#include "safeinput.h"
#include <Windows.h>

#define LAMP "CURRENTLY LAMP IS: "

// const double pi = 3.1415927;
// #define

// 2. titta på en struct i runtime struct tm (time)
// allokera malloc realloc free

// ADD REMOVE access
void Access(CardLista *state)
{
    AddRemoveAccess(state);
}

void AddRemoveAccess(CardLista *state)
{
    while (1)
    {
        printf("\nAdd/remove access*******************\n");
        printf("1. Remote open door\n");
        printf("2. List logged in\n");
        printf("3. List all\n");
        printf("4. Add/remove access\n");
        printf("5. Back\n"); // två gånger 5 för huvudmeny

        int sel = 0;

        GetInputInt("Ange val:", &sel);
        if (sel == 1)
            RemoteOpen(state);
        else if (sel == 2)
            ListLoggedIn(state);
        else if (sel == 3)
            ListAllCards(state);
        else if (sel == 4)
            CardExists(state);
        else if (sel == 5)
            break;
    }
    // skriv till fil
}

void CardExists(CardLista *state)
{
    int cardNo, sel = 0;
    GetInputInt("Enter cardnumber:", &cardNo);

    if (state->antal > 0)
    {
        Card *p;
        for (int i = 0; i < state->antal; i++)
        {
            if (state->cards[i].cardNumber == cardNo)
            {
                p = &state->cards[i];
                GetInputInt("\nEnter 1 for access, 2 for no access", &sel);
                if (sel == 1)
                    p->hasAccess = 1;
                else
                    p->hasAccess = 0;
            }
            else
            {
                printf("\nThe card is not added to the system\n");
                GetInputInt("Enter 1 to add a card, 2 to go back to menu:", &sel);
                if (sel == 1)
                    CreateCard(state);
                else if (sel == 2)
                    AddRemoveAccess(state);
            }
        }
    }
    else
    {
        printf("\nNo card in the system\n\n");
        GetInputInt("Enter 1 to add a card, 2 to go back to menu:", &sel);
        if (sel == 1)
            CreateCard(state);
        else if (sel == 2)
            AddRemoveAccess(state);
    }
}
void CreateCard(CardLista *state)
{
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

    InputCard(&state->cards[state->antal - 1]);
}

void FakeScan(CardLista *state)
{
    printf("FakeScan");
}

// lägg in 1212 has access, 1213 No access
void InputCard(Card *p)
{
    int sel = 0;
    GetInputInt("New cardnumber:\n", &(p->cardNumber));

    GetInputInt("\nEnter 1 for access, 2 for no access", &sel);
    if (sel == 1)
        p->hasAccess = 1;
    else
        p->hasAccess = 0;

    struct tm *tm;
    time_t t;
    char str_date[100];
    t = time(NULL);
    tm = localtime(&t);
    strftime(str_date, sizeof(str_date), "%Y-%m-%d", tm);
    strcpy(p->dateAdded, str_date);
}

void ListAllCards(CardLista *state)
{
    printf("Listing all cards\n*******************\n");
    for (int i = 0; i < state->antal; i++)
    {
        PrintCard(&state->cards[i]);
    }
    if (state->antal == 0)
        printf("No card in the system\n\n");
}

void ListLoggedIn(CardLista *state)
{
    printf("Listing logged in cards\n*******************\n");
    for (int i = 0; i < state->antal; i++)
    {
        if (state->cards[i].isLoggedIn != 0)
            PrintCard(&state->cards[i]);
    }

    printf("No card logged in\n");
}

void PrintCard(Card *p)
{
    printf(" %d", p->cardNumber);
    (p->hasAccess) ? printf(" Access    ") : printf(" No Access ");
    printf("Added to the system: %s\n", p->dateAdded);
}

// Dörren ska vara öppen (grön lampa) i 3 sekunder
void RemoteOpen(CardLista *state)
{
    printf("%sGreen\n", LAMP);
    Sleep(3000);
    printf("%sRed\n", LAMP);
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

    while (1)
    {
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");

        int sel = 0;

        GetInputInt("Ange val:", &sel);
        if (sel == 1)
            RemoteOpen(&state);
        else if (sel == 2)
            ListAllCards(&state);
        else if (sel == 3)
            AddRemoveAccess(&state);
        // Access(&state);
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
