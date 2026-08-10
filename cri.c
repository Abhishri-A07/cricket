#include <stdio.h>
#include <string.h>
#include "player.h"

#define MAX_SQUAD 15
#define PLAYING_XI 11

void getSquad(struct Player squad[], int *n)
{
    int i;

    do
    {
        printf("Enter squad size (11-15): ");
        scanf("%d", n);

        if (*n < 11 || *n > 15)
        {
            printf("Squad size must be between 11 and 15.\n");
        }

    } while (*n < 11 || *n > 15);

    printf("\nEnter player details\n");

    for (i = 0; i < *n; i++)
    {
        printf("\nPlayer %d name: ", i + 1);
        scanf(" %[^\n]", squad[i].name);

        printf("Role (BATSMAN/BOWLER/ALLROUNDER): ");
        scanf("%s", squad[i].role);
    }
}

void getLineup(struct Player squad[],
               int n,
               struct Player xi[])
{
    int i;
    int x;
    int j;
    int selected[MAX_SQUAD] = {0};

    printf("\nSELECT PLAYING XI\n");

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("\nAvailable players:\n");

        for (j = 0; j < n; j++)
        {
            if (selected[j] == 0)
                printf("%d. %s\n", j + 1, squad[j].name);
        }

        printf("Select player %d: ", i + 1);
        scanf("%d", &x);

        if (x < 1 || x > n || selected[x - 1] == 1)
        {
            printf("Invalid or already selected player!\n");
            i--;
            continue;
        }

        xi[i] = squad[x - 1];
        selected[x - 1] = 1;
    }
}

void battingOrder(struct Player xi[])
{
    int i;
    int x;
    int selected[PLAYING_XI] = {0};
    struct Player temp[PLAYING_XI];

    printf("\nSET BATTING ORDER\n");

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("%d. %s\n", i + 1, xi[i].name);
    }

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("Position %d: ", i + 1);
        scanf("%d", &x);

        if (x < 1 || x > PLAYING_XI || selected[x - 1] == 1)
        {
            printf("Invalid or already selected player!\n");
            i--;
            continue;
        }

        temp[i] = xi[x - 1];
        selected[x - 1] = 1;
    }

    for (i = 0; i < PLAYING_XI; i++)
    {
        xi[i] = temp[i];
    }
}

void selectCaptain(struct Player xi[])
{
    int x;
    int i;

    printf("\nSELECT CAPTAIN\n");

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("%d. %s\n", i + 1, xi[i].name);
    }

    printf("Enter number: ");
    scanf("%d", &x);

    if (x < 1 || x > PLAYING_XI)
    {
        printf("Invalid player number!\n");
        return;
    }

    printf("Captain: %s\n", xi[x - 1].name);
}

void selectKeeper(struct Player xi[])
{
    int x;
    int i;

    printf("\nSELECT WICKETKEEPER\n");

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("%d. %s\n", i + 1, xi[i].name);
    }

    printf("Enter number: ");
    scanf("%d", &x);

    if (x < 1 || x > PLAYING_XI)
    {
        printf("Invalid player number!\n");
        return;
    }

    printf("Wicketkeeper: %s\n", xi[x - 1].name);
}

void bowlingPlan(struct Player xi[])
{
    int n;
    int x;
    int i;
    int j;
    int selected[PLAYING_XI] = {0};

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
        printf("\nAvailable players:\n");

        for (j = 0; j < PLAYING_XI; j++)
        {
            if (selected[j] == 0)
                printf("%d. %s\n", j + 1, xi[j].name);
        }

        printf("Bowler %d: ", i + 1);
        scanf("%d", &x);

        if (x < 1 || x > PLAYING_XI || selected[x - 1] == 1)
        {
            printf("Invalid or already selected player!\n");
            i--;
            continue;
        }

        selected[x - 1] = 1;

        printf("Selected: %s\n", xi[x - 1].name);
    }
}

void displayLineup(struct Player xi[])
{
    int i;

    printf("\n============================\n");
    printf("       FINAL LINE-UP\n");
    printf("============================\n");

    for (i = 0; i < PLAYING_XI; i++)
    {
        printf("%d. %s (%s)\n",
               i + 1,
               xi[i].name,
               xi[i].role);
    }
}
