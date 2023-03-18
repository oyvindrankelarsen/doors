#include <stdio.h>
#include "safeinput.h"

int getMenuSelection()
{
    printf("Admin menu\n");
    printf("1. Remote open door\n");
    printf("2. List all cards in system\n");
    printf("3. Add remove access\n");
    printf("4. Exit\n");
    printf("9. FAKE TEST SCAN CARD\n");
    // TODO input
    int sel=0;
    GetInputInt("Ange val:", &sel);
    return sel;
}
