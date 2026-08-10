#include <stdio.h>
#include <string.h>
#include "player.h"

void performance(struct Player *head)
{
    float total;
    struct Player *temp = head;

    while (temp != NULL)
    {
        total = (temp->runs * 0.4)
              + (temp->wickets * 10 * 0.3)
              + (temp->strikeRate * 0.2)
              + ((10 - temp->economy) * 0.1);

        temp->performance = total;

        temp = temp->next;
    }
}

void ranking(struct Player *head)
{
    struct Player *temp = head;

    printf("\n:::::::::::::: PLAYER RANK DETAILS ::::::::::::::\n");
    printf("PLAYER NAME\tSCORE\n");
    printf("-----------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%s\t\t%.2f\n",
               temp->name,
               temp->performance);

        temp = temp->next;
    }

    printf(":::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void bestplayer(struct Player *head)
{
    struct Player *temp = head;

    struct Player *batsman = NULL;
    struct Player *bowler = NULL;
    struct Player *allrounder = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BATSMAN") == 0)
        {
            if (batsman == NULL ||
                temp->runs > batsman->runs)
            {
                batsman = temp;
            }
        }

        if (strcmp(temp->role, "BOWLER") == 0)
        {
            if (bowler == NULL ||
                temp->wickets > bowler->wickets)
            {
                bowler = temp;
            }
        }

        if (strcmp(temp->role, "ALLROUNDER") == 0)
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
        printf("Best Batsman    : %s (%d runs)\n",
               batsman->name, batsman->runs);
    else
        printf("Best Batsman    : Not available\n");

    if (bowler != NULL)
        printf("Best Bowler     : %s (%d wickets)\n",
               bowler->name, bowler->wickets);
    else
        printf("Best Bowler     : Not available\n");

    if (allrounder != NULL)
        printf("Best All-Rounder : %s (%.2f performance)\n",
               allrounder->name,
               allrounder->performance);
    else
        printf("Best All-Rounder : Not available\n");

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
                struct Player temp;

                /*
                 * Swap player data only.
                 * Do not swap prev/next pointers.
                 */

                temp.id = i->id;
                strcpy(temp.name, i->name);
                strcpy(temp.role, i->role);

                temp.pruns = i->pruns;
                temp.runs = i->runs;
                temp.pwickets = i->pwickets;
                temp.wickets = i->wickets;

                temp.strikeRate = i->strikeRate;
                temp.economy = i->economy;
                temp.performance = i->performance;
                temp.basePrice = i->basePrice;

                temp.ballsfaced = i->ballsfaced;
                temp.isout = i->isout;
                temp.ballsBowled = i->ballsBowled;
                temp.runsgiven = i->runsgiven;

                i->id = j->id;
                strcpy(i->name, j->name);
                strcpy(i->role, j->role);

                i->pruns = j->pruns;
                i->runs = j->runs;
                i->pwickets = j->pwickets;
                i->wickets = j->wickets;

                i->strikeRate = j->strikeRate;
                i->economy = j->economy;
                i->performance = j->performance;
                i->basePrice = j->basePrice;

                i->ballsfaced = j->ballsfaced;
                i->isout = j->isout;
                i->ballsBowled = j->ballsBowled;
                i->runsgiven = j->runsgiven;

                j->id = temp.id;
                strcpy(j->name, temp.name);
                strcpy(j->role, temp.role);

                j->pruns = temp.pruns;
                j->runs = temp.runs;
                j->pwickets = temp.pwickets;
                j->wickets = temp.wickets;

                j->strikeRate = temp.strikeRate;
                j->economy = temp.economy;
                j->performance = temp.performance;
                j->basePrice = temp.basePrice;

                j->ballsfaced = temp.ballsfaced;
                j->isout = temp.isout;
                j->ballsBowled = temp.ballsBowled;
                j->runsgiven = temp.runsgiven;
            }
        }
    }
}
