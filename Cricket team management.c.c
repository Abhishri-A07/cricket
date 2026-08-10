#include <stdio.h>
#include <string.h>
#include "player.h"

#define MAX 22

struct Team
{
    char name[20];
    struct Player players[MAX];
    int count;
};

void addTeamPlayer(struct Team *team, struct Player p)
{
    if (team->count < MAX)
    {
        team->players[team->count] = p;
        team->count++;

        printf("%s added to %s\n",
               p.name,
               team->name);
    }
    else
    {
        printf("Team is full!\n");
    }
}

void removeTeamPlayer(struct Team *team, int id)
{
    int i;
    int j;

    for (i = 0; i < team->count; i++)
    {
        if (team->players[i].id == id)
        {
            for (j = i; j < team->count - 1; j++)
            {
                team->players[j] = team->players[j + 1];
            }

            team->count--;

            printf("Player removed from %s\n",
                   team->name);

            return;
        }
    }

    printf("Player not found!\n");
}

void replaceTeamPlayer(struct Team *team,
                        int oldId,
                        struct Player newPlayer)
{
    int i;

    for (i = 0; i < team->count; i++)
    {
        if (team->players[i].id == oldId)
        {
            team->players[i] = newPlayer;

            printf("Player replaced in %s\n",
                   team->name);

            return;
        }
    }

    printf("Player not found!\n");
}

void displayTeam(struct Team *team)
{
    int i;

    printf("\n-------------------------\n");
    printf("%s\n", team->name);
    printf("-------------------------\n");

    for (i = 0; i < team->count; i++)
    {
        printf("%d. %s\n",
               team->players[i].id,
               team->players[i].name);
    }

    printf("Total Players: %d\n",
           team->count);
}

void checkSquad(struct Team *team)
{
    if (team->count >= 11)
    {
        printf("%s has the required squad size.\n",
               team->name);
    }
    else
    {
        printf("%s needs %d more players.\n",
               team->name,
               11 - team->count);
    }
}
