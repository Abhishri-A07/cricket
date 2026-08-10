#include <stdio.h>
#include <string.h>
#include "player.h"


void getSquad(Player squad[], int *n)
{
    int i;

    do
    {
        printf("Enter squad size (11-15): ");
        scanf("%d", n);

        if (*n < 11 || *n > 15)
            printf("Squad size must be between 11 and 15.\n");

    } while (*n < 11 || *n > 15);


    printf("\nEnter player details\n");

    for (i = 0; i < *n; i++)
    {
        printf("\nPlayer %d name: ",
               i + 1);

        scanf(" %[^\n]", squad[i].name);

        printf("Role: ");
        scanf("%s", squad[i].role);
    }
}


void getLineup(Player squad[],
               int n,
               Player xi[])
{
    int i;
    int x;

    printf("\nSELECT PLAYING XI\n");

    for (i = 0; i < 11; i++)
    {
        printf("\nAvailable players:\n");

        int j;

        for (j = 0; j < n; j++)
        {
            printf("%d. %s (%s)\n",
                   j + 1,
                   squad[j].name,
                   squad[j].role);
        }

        do
        {
            printf("Select player %d: ",
                   i + 1);

            scanf("%d", &x);

        } while (x < 1 || x > n);

        xi[i] = squad[x - 1];
    }
}


void battingOrder(Player xi[])
{
    int i;
    int x;
    Player temp[11];

    printf("\nSET BATTING ORDER\n");

    for (i = 0; i < 11; i++)
    {
        printf("%d. %s\n",
               i + 1,
               xi[i].name);
    }

    for (i = 0; i < 11; i++)
    {
        do
        {
            printf("Position %d: ",
                   i + 1);

            scanf("%d", &x);

        } while (x < 1 || x > 11);

        temp[i] = xi[x - 1];
    }

    for (i = 0; i < 11; i++)
        xi[i] = temp[i];
}


void selectCaptain(Player xi[])
{
    int x;
    int i;

    printf("\nSELECT CAPTAIN\n");

    for (i = 0; i < 11; i++)
    {
        printf("%d. %s\n",
               i + 1,
               xi[i].name);
    }

    do
    {
        printf("Enter number: ");
        scanf("%d", &x);

    } while (x < 1 || x > 11);

    printf("Captain: %s\n",
           xi[x - 1].name);
}


void selectKeeper(Player xi[])
{
    int x;
    int i;

    printf("\nSELECT WICKETKEEPER\n");

    for (i = 0; i < 11; i++)
    {
        printf("%d. %s\n",
               i + 1,
               xi[i].name);
    }

    do
    {
        printf("Enter number: ");
        scanf("%d", &x);

    } while (x < 1 || x > 11);

    printf("Wicketkeeper: %s\n",
           xi[x - 1].name);
}


void bowlingPlan(Player xi[])
{
    int n;
    int x;
    int i;
    int j;

    printf("\nNUMBER OF BOWLERS (4 or 5): ");
    scanf("%d", &n);

    while (n < 4 || n > 5)
    {
        printf("Enter 4 or 5: ");
        scanf("%d", &n);
    }

    printf("\nBOWLING PLAN\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 11; j++)
        {
            printf("%d. %s (%s)\n",
                   j + 1,
                   xi[j].name,
                   xi[j].role);
        }

        do
        {
            printf("Bowler %d: ",
                   i + 1);

            scanf("%d", &x);

        } while (x < 1 || x > 11);

        printf("Selected: %s\n",
               xi[x - 1].name);
    }
}


void displayLineup(Player xi[])
{
    int i;

    printf("\n============================\n");
    printf("       FINAL LINE-UP\n");
    printf("============================\n");

    for (i = 0; i < 11; i++)
    {
        printf("%d. %s (%s)\n",
               i + 1,
               xi[i].name,
               xi[i].role);
    }
}
