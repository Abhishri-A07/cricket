#include <stdio.h>
#include <string.h>
#include "player.h"

void batting(struct Player *striker, int runs, int wicket)
{
    striker->ballsfaced++;

    if (wicket == 1)
    {
        striker->isout = 1;

        printf("\n%s is OUT!\n", striker->name);
    }
    else
    {
        striker->runs += runs;
    }
}

void bowling(struct Player *bowler, int runs, int wicket)
{
    bowler->ballsBowled++;
    bowler->runsgiven += runs;

    if (wicket == 1)
    {
        bowler->wickets++;
    }
}

void play(struct Player *head, int totalOvers)
{
    struct Player *striker = NULL;
    struct Player *nonstriker = NULL;
    struct Player *bowler = NULL;
    struct Player *temp;

    int runs;
    int wicket;
    int ball;
    int over;

    /* Find first two batsmen */
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BATSMAN") == 0 ||
            strcmp(temp->role, "ALLROUNDER") == 0)
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

    /* Find first bowler */
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->role, "BOWLER") == 0 ||
            strcmp(temp->role, "ALLROUNDER") == 0)
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
        printf("\nNot enough players.\n");
        return;
    }

    for (over = 1; over <= totalOvers; over++)
    {
        printf("\n================================\n");
        printf("Over %d\n", over);
        printf("Striker     : %s\n", striker->name);
        printf("Non-Striker : %s\n", nonstriker->name);
        printf("Bowler      : %s\n", bowler->name);
        printf("================================\n");

        for (ball = 1; ball <= 6; ball++)
        {
            printf("\nBall %d\n", ball);
            printf("Striker: %s\n", striker->name);

            printf("Enter number of runs (0,1,2,3,4,6): ");
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

            printf("Wicket? (1 = Yes, 0 = No): ");
            scanf("%d", &wicket);

            if (wicket != 0 && wicket != 1)
            {
                printf("Invalid wicket choice!\n");
                ball--;
                continue;
            }

            batting(striker, runs, wicket);
            bowling(bowler, runs, wicket);

            if (wicket == 1)
            {
                /*
                 * Find next available batsman.
                 */
                temp = head;

                while (temp != NULL)
                {
                    if ((strcmp(temp->role, "BATSMAN") == 0 ||
                         strcmp(temp->role, "ALLROUNDER") == 0) &&
                        temp->isout == 0 &&
                        temp != striker &&
                        temp != nonstriker)
                    {
                        striker = temp;
                        break;
                    }

                    temp = temp->next;
                }

                printf("New batsman: %s\n", striker->name);
            }
            else if (runs % 2 == 1)
            {
                temp = striker;
                striker = nonstriker;
                nonstriker = temp;

                printf("Strike changed.\n");
            }
        }

        /* Change strike at end of over */
        temp = striker;
        striker = nonstriker;
        nonstriker = temp;

        printf("\nEnd of over %d\n", over);
    }
}
