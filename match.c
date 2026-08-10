#include <stdio.h>
#include <string.h>
#include "player.h"

void batting(struct Player *striker, int runs)
{
    striker->ballsfaced++;

    if (runs == 0)
    {
        striker->isout = 1;

        printf("\n%s is out", striker->name);
    }
    else
    {
        striker->runs += runs;
    }
}

void bowling(struct Player *bowler, int runs)
{
    bowler->ballsBowled++;
    bowler->runsgiven += runs;

    if (runs == 0)
    {
        bowler->wickets++;
    }
}

void play(struct Player *head, int totalOvers)
{
    struct Player *striker = NULL;
    struct Player *nonstriker = NULL;
    struct Player *bowler = NULL;
    struct Player *temp = NULL;

    int runs;
    int ball;
    int over;

    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BATSMAN") == 0 ||
            strcmp(temp->role, "ALLROUNDER") == 0 ||
            strcmp(temp->role, "batsman") == 0 ||
            strcmp(temp->role, "allrounder") == 0)
        {
            if (striker == NULL)
            {
                striker = temp;
            }
            else if (nonstriker == NULL)
            {
                nonstriker = temp;
                break;
            }
        }

        temp = temp->next;
    }

    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BOWLER") == 0 ||
            strcmp(temp->role, "ALLROUNDER") == 0 ||
            strcmp(temp->role, "bowler") == 0 ||
            strcmp(temp->role, "allrounder") == 0)
        {
            bowler = temp;
            break;
        }

        temp = temp->next;
    }

    if (striker == NULL ||
        nonstriker == NULL ||
        bowler == NULL)
    {
        printf("\nNot enough players\n");
        return;
    }

    for (over = 1; over <= totalOvers; over++)
    {
        printf("\n=================================\n");
        printf("Over %d\n", over);
        printf("Striker     : %s\n", striker->name);
        printf("Non-striker : %s\n", nonstriker->name);
        printf("Bowler      : %s\n", bowler->name);
        printf("=================================\n");

        for (ball = 1; ball <= 6; ball++)
        {
            printf("\nBall %d", ball);
            printf("\nStriker: %s", striker->name);
            printf("\nEnter the number of runs (0-Wicket): ");

            scanf("%d", &runs);

            if (runs != 0 &&
                runs != 1 &&
                runs != 2 &&
                runs != 3 &&
                runs != 4 &&
                runs != 6)
            {
                printf("Invalid runs!\n");
                ball--;
                continue;
            }

            batting(striker, runs);
            bowling(bowler, runs);

            if (runs == 0)
            {
                temp = head;

                while (temp != NULL)
                {
                    if ((strcmp(temp->role, "BATSMAN") == 0 ||
                         strcmp(temp->role, "ALLROUNDER") == 0 ||
                         strcmp(temp->role, "batsman") == 0 ||
                         strcmp(temp->role, "allrounder") == 0) &&
                        temp->isout == 0 &&
                        temp != striker &&
                        temp != nonstriker)
                    {
                        striker = temp;
                        break;
                    }

                    temp = temp->next;
                }

                if (striker != NULL)
                    printf("\nNew batsman: %s\n",
                           striker->name);
            }
            else if (runs % 2 == 1)
            {
                temp = striker;
                striker = nonstriker;
                nonstriker = temp;

                printf("\nStrike changed\n");
            }
        }

        temp = striker;
        striker = nonstriker;
        nonstriker = temp;

        printf("\nEnd of over %d\n", over);
    }
}
