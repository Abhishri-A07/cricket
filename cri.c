#include <stdio.h>
#include <string.h>

#define MAX 15

struct Player
{
    char name[30];
    char role[20];
};

void getSquad(struct Player squad[], int *n)
{
    int i;

    printf("Enter squad size (11-15): ");
    scanf("%d", n);

    printf("\nEnter player details\n");

    for(i = 0; i < *n; i++)
    {
        printf("\nPlayer %d name: ", i + 1);
        scanf(" %[^\n]", squad[i].name);

        printf("Role: ");
        scanf("%s", squad[i].role);
    }
}

void getLineup(struct Player squad[], int n,
               struct Player xi[])
{
    int i, x, j;

    printf("\nSELECT PLAYING XI\n");

    for(i = 0; i < 11; i++)
    {
        printf("\n");

        for(j = 0; j < n; j++)
            printf("%d. %s\n", j + 1, squad[j].name);

        printf("Select player %d: ", i + 1);
        scanf("%d", &x);

        xi[i] = squad[x - 1];
    }
}

void battingOrder(struct Player xi[])
{
    int i, x;
    struct Player temp[11];

    printf("\nSET BATTING ORDER\n");

    for(i = 0; i < 11; i++)
        printf("%d. %s\n", i + 1, xi[i].name);

    for(i = 0; i < 11; i++)
    {
        printf("Position %d: ", i + 1);
        scanf("%d", &x);

        temp[i] = xi[x - 1];
    }

    for(i = 0; i < 11; i++)
        xi[i] = temp[i];
}

void selectCaptain(struct Player xi[])
{
    int x, i;

    printf("\nSELECT CAPTAIN\n");

    for(i = 0; i < 11; i++)
        printf("%d. %s\n", i + 1, xi[i].name);

    printf("Enter number: ");
    scanf("%d", &x);

    printf("Captain: %s\n", xi[x - 1].name);
}

void selectKeeper(struct Player xi[])
{
    int x, i;

    printf("\nSELECT WICKETKEEPER\n");

    for(i = 0; i < 11; i++)
        printf("%d. %s\n", i + 1, xi[i].name);

    printf("Enter number: ");
    scanf("%d", &x);

    printf("Wicketkeeper: %s\n", xi[x - 1].name);
}

void bowlingPlan(struct Player xi[])
{
    int n, x, i, j;

    printf("\nNUMBER OF BOWLERS (4 or 5): ");
    scanf("%d", &n);

    while(n < 4 || n > 5)
    {
        printf("Enter 4 or 5: ");
        scanf("%d", &n);
    }

    printf("\nBOWLING PLAN\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < 11; j++)
            printf("%d. %s\n", j + 1, xi[j].name);

        printf("Bowler %d: ", i + 1);
        scanf("%d", &x);

        printf("Selected: %s\n", xi[x - 1].name);
    }
}

void displayLineup(struct Player xi[])
{
    int i;

    printf("\n============================\n");
    printf("       FINAL LINE-UP\n");
    printf("============================\n");

    for(i = 0; i < 11; i++)
        printf("%d. %s (%s)\n",
               i + 1, xi[i].name, xi[i].role);
}
