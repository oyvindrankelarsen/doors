#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doors.h"
#include "safeinput.h"
#include <Windows.h>

#define LAMP "CURRENTLY LAMP IS: "

void AddRemoveAccessMenu(CardLista *state)
{
    while (1)
    {
        printf("\nAdd/remove access menu *******************\n");
        printf("1. Remote open door\n");
        printf("2. List logged in\n");
        printf("3. List all\n");
        printf("4. Add/remove access\n");
        printf("5. Back\n");

        int sel = 0;

        GetInputInt("Enter:", &sel);
        if (sel == 1)
            RemoteOpen(state);
        else if (sel == 2)
            ListLoggedIn(state);
        else if (sel == 3)
            ListAllCards(state);
        else if (sel == 4)
            AddRemoveAccess(state);
        else if (sel == 5)
            AdminMenu(state);
        else
            printf("Please choose a number from the menu\n\n");
    }
}

void AdminMenu(CardLista *state)
{
    while (1)
    {
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");

        int sel = 0;
        GetInputInt("Enter:", &sel);
        if (sel == 1)
            RemoteOpen(state);
        else if (sel == 2)
            ListAllCards(state);
        else if (sel == 3)
            AddRemoveAccessMenu(state);
        else if (sel == 4)
        {
            WriteCardsFile(state);
            exit(0);
        }
        else if (sel == 9)
            FakeScan(state);
        else
            printf("Please choose a number from the menu\n\n");
    }
}

void AddRemoveAccess(CardLista *state)
{
    Card *p;
    int cardNo = 0, sel = 0;
    GetInputInt("(AddRemoveAccess)Enter cardnumber:", &cardNo);

    for (int i = 0; i < state->antal; i++)
    {
        if (state->cards[i].cardNumber == cardNo)
        {
            p = &state->cards[i];
            printf("%d", state->cards[i].cardNumber);
            printf("This card has ");
            (p->hasAccess) ? printf(" access    ") : printf(" no Access ");
            int sel = 0;
            GetInputInt("\n(AddRemoveAccess2)Enter 1 for access, 2 for no access ", &sel);
            if (sel == 1)
                p->hasAccess = 1;
            else
                p->hasAccess = 0;
            AddRemoveAccessMenu(state);
        }
    }

    printf("\nThe card is not added to the system\n");
    GetInputInt("((CardExistsFalse))Enter 1 to add a card, 2 to go back to menu:", &sel);
    if (sel == 1)
        CreateCard(state);
    else if (sel == 2)
        AddRemoveAccessMenu(state);
}

void CreateCard(CardLista *state)
{
    state->antal++;
    if (state->antal == 1)
        state->cards = (Card *)malloc(1 * sizeof(Card));
    else
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));

    InputCard(&state->cards[state->antal - 1], state);
}

void FakeScan(CardLista *state)
{
    printf("Please scan card to enter or X to go back to menu\n");
    printf("%sOff", LAMP);
    int cardNo;
    Card *p;
    GetInputInt("\n", &cardNo);

    for (int i = 0; i < state->antal; i++)
    {
        if (state->cards[i].cardNumber == cardNo)
        {
            p = &state->cards[i];
            printf("%d", state->cards[i].cardNumber);
            if (p->hasAccess)
            {
                p->isLoggedIn = 1;
                printf("%sGreen\n", LAMP);
            }
            else
            {
                p->isLoggedIn = 0;
                printf("%sRed\n", LAMP);
            }
        }
    }
}

void InputCard(Card *p, CardLista *state)
{
    int sel = 0;
    GetInputInt("(Input card)New cardnumber:\n", &(p->cardNumber));
    GetInputInt("(Input card)Enter 1 for access, 2 for no access ", &sel);

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
    AddRemoveAccessMenu(state);
}

void ListAllCards(CardLista *state)
{
    printf("\nListing all cards\n*******************\n");
    for (int i = 0; i < state->antal; i++)
    {
        PrintCard(&state->cards[i]);
    }

    if (state->antal == 0)
        printf("No card in the system\n\n");
    printf("Press key to continue");
    _getch();
}

void ListLoggedIn(CardLista *state)
{
    printf("\nListing logged in cards\n*******************\n");
    for (int i = 0; i < state->antal; i++)
    {
        if (state->cards[i].isLoggedIn != 0)
            PrintCard(&state->cards[i]);
    }
}

void PrintCard(Card *p)
{
    printf(" %d", p->cardNumber);
    (p->hasAccess) ? printf(" Access    ") : printf(" No Access ");
    printf("Added to the system: %s\n", p->dateAdded);
}

void ReadCardsFile(CardLista *state)
{
    FILE *f = fopen("cards.bin", "rb");
    state->antal++;
    state->cards = (Card *)malloc(1 * sizeof(Card));
    int i = 0;

    while (fread(&state->cards[i], sizeof(Card), 1, f))
    {
        printf("%d\n", state->cards[i].cardNumber);
        state->antal++;
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));
        i++;
    }
    fclose(f);
    state->antal--;
}

void RemoteOpen(CardLista *state)
{
    printf("%sGreen\n", LAMP);
    Sleep(3000);
    printf("%sRed\n", LAMP);
}

void WriteCardsFile(CardLista *state)
{
    FILE *f = fopen("cards.bin", "wb");
    for (int i = 0; i < state->antal; i++)
    {
        fwrite(&state->cards[i], sizeof(Card), 1, f);
    }
    fclose(f);
}

int main(void)
{
    CardLista state;
    state.cards = NULL;
    state.antal = 0;

    ReadCardsFile(&state);

    AdminMenu(&state);
    free(state.cards);
    return 0;
}
