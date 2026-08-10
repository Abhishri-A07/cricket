#include <stdio.h>
#include <string.h>
#include "player.h"

void performance(struct Player *head)
{
    float total;
    struct Player *temp = head;

    while (temp != NULL)
    {
        total = (temp->runs * 0.4f)
              + (temp->wickets * 10 * 0.3f)
              + (temp->strikeRate * 0.2f)
              + ((10 - temp->economy) * 0.1f);

        temp->performance = total;

        temp = temp->next;
    }
}

void ranking(struct Player *head)
{
    struct Player *temp = head;

    printf("\n:::::::::::::: PLAYERS RANK DETAILS ::::::::::::::\n");
    printf("PLAYER NAME \tSCORE\n");

    while (temp != NULL)
    {
        printf("%s\t %.2f\n",
               temp->name,
               temp->performance);

        temp = temp->next;
    }

    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void bestplayer(struct Player *head)
{
    struct Player *temp = head;

    struct Player *batsman = NULL;
    struct Player *bowler = NULL;
    struct Player *allrounder = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BATSMAN") == 0 ||
            strcmp(temp->role, "batsman") == 0)
        {
            if (batsman == NULL ||
                temp->runs > batsman->runs)
            {
                batsman = temp;
            }
        }

        if (strcmp(temp->role, "BOWLER") == 0 ||
            strcmp(temp->role, "bowler") == 0)
        {
            if (bowler == NULL ||
                temp->wickets > bowler->wickets)
            {
                bowler = temp;
            }
        }

        if (strcmp(temp->role, "ALLROUNDER") == 0 ||
            strcmp(temp->role, "allrounder") == 0)
        {
            if (allrounder == NULL ||
                temp->performance > allrounder->performance)
            {
                allrounder = temp;
            }
        }

        temp = temp->next;
    }

    printf("\n================ BEST PLAYERS ================\n");

    if (batsman != NULL)
        printf("Best Batsman    : %s\n", batsman->name);
    else
        printf("Best Batsman    : Not available\n");

    if (bowler != NULL)
        printf("Best Bowler     : %s\n", bowler->name);
    else
        printf("Best Bowler     : Not available\n");

    if (allrounder != NULL)
        printf("Best All-Rounder: %s\n", allrounder->name);
    else
        printf("Best All-Rounder: Not available\n");

    printf("==============================================\n");
}

void sortplayer(struct Player *head)
{
    struct Player *i;
    struct Player *j;

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->performance > i->performance)
            {
                float tempPerf;
                int tempRuns;
                int tempWickets;
                float tempSR;
                float tempEco;
                char tempName[30];
                char tempRole[20];

                tempPerf = i->performance;
                i->performance = j->performance;
                j->performance = tempPerf;

                tempRuns = i->runs;
                i->runs = j->runs;
                j->runs = tempRuns;

                tempWickets = i->wickets;
                i->wickets = j->wickets;
                j->wickets = tempWickets;

                tempSR = i->strikeRate;
                i->strikeRate = j->strikeRate;
                j->strikeRate = tempSR;

                tempEco = i->economy;
                i->economy = j->economy;
                j->economy = tempEco;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                strcpy(tempRole, i->role);
                strcpy(i->role, j->role);
                strcpy(j->role, tempRole);
            }
        }
    }
}
