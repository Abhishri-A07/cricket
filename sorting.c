#include <stdio.h>
#include <string.h>
#include "player.h"


float calculatePerformance(Player *p)
{
    if (p == NULL)
        return 0;

    return (p->runs * 0.4f)
         + (p->wickets * 10.0f * 0.3f)
         + (p->strikeRate * 0.2f)
         + ((10.0f - p->economy) * 0.1f);
}


void performance(Player *head)
{
    Player *temp = head;

    while (temp != NULL)
    {
        temp->performance = calculatePerformance(temp);
        temp = temp->next;
    }
}


void ranking(Player *head)
{
    Player *temp = head;

    printf("\n:::::::::::::: PLAYERS RANK DETAILS ::::::::::::::\n");
    printf("PLAYER NAME\tSCORE\n");

    while (temp != NULL)
    {
        printf("%s\t\t%.2f\n",
               temp->name,
               temp->performance);

        temp = temp->next;
    }

    printf(":::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}


void bestplayer(Player *head)
{
    Player *temp = head;

    Player *batsman = NULL;
    Player *bowler = NULL;
    Player *allrounder = NULL;

    while (temp != NULL)
    {
        if (strcasecmp(temp->role, "BATSMAN") == 0)
        {
            if (batsman == NULL ||
                temp->runs > batsman->runs)
            {
                batsman = temp;
            }
        }

        if (strcasecmp(temp->role, "BOWLER") == 0)
        {
            if (bowler == NULL ||
                temp->wickets > bowler->wickets)
            {
                bowler = temp;
            }
        }

        if (strcasecmp(temp->role, "ALLROUNDER") == 0 ||
            strcasecmp(temp->role, "ALL-ROUNDER") == 0)
        {
            if (allrounder == NULL ||
                temp->performance > allrounder->performance)
            {
                allrounder = temp;
            }
        }

        temp = temp->next;
    }

    printf("\n========== BEST PLAYERS ==========\n");

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
        printf("Best All-rounder : %s (%.2f)\n",
               allrounder->name,
               allrounder->performance);
    else
        printf("Best All-rounder : Not available\n");
}


/*
 * Sort players according to performance.
 * The complete player information is exchanged so that
 * records remain together.
 */
void sortplayer(Player *head)
{
    Player *i;
    Player *j;

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->performance > i->performance)
            {
                Player temp = *i;

                /*
                 * Preserve linked-list pointers.
                 */
                Player *prevI = i->prev;
                Player *nextI = i->next;

                *i = *j;
                *j = temp;

                i->prev = prevI;
                i->next = nextI;

                j->prev = temp.prev;
                j->next = temp.next;
            }
        }
    }
}
