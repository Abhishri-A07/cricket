#include <stdio.h>
#include <string.h>
#include "player.h"


static int isBatsman(Player *p)
{
    return strcmp(p->role, "BATSMAN") == 0 ||
           strcmp(p->role, "batsman") == 0 ||
           strcmp(p->role, "ALLROUNDER") == 0 ||
           strcmp(p->role, "allrounder") == 0 ||
           strcmp(p->role, "ALL-ROUNDER") == 0 ||
           strcmp(p->role, "all-rounder") == 0;
}


static int isBowler(Player *p)
{
    return strcmp(p->role, "BOWLER") == 0 ||
           strcmp(p->role, "bowler") == 0 ||
           strcmp(p->role, "ALLROUNDER") == 0 ||
           strcmp(p->role, "allrounder") == 0 ||
           strcmp(p->role, "ALL-ROUNDER") == 0 ||
           strcmp(p->role, "all-rounder") == 0;
}


void batting(Player *striker,
             int runs)
{
    striker->ballsfaced++;

    striker->runs += runs;

    if (runs == 4)
        striker->strikeRate =
            striker->ballsfaced ?
            striker->runs * 100.0f /
            striker->ballsfaced : 0;
}


void bowling(Player *bowler,
             int runs)
{
    bowler->ballsBowled++;

    bowler->runsgiven += runs;

    bowler->economy =
        bowler->ballsBowled ?
        bowler->runsgiven /
        (bowler->ballsBowled / 6.0f) : 0;
}


static Player *findNextBatsman(Player *head,
                               Player *striker,
                               Player *nonstriker)
{
    Player *temp = head;

    while (temp != NULL)
    {
        if (isBatsman(temp) &&
            temp != striker &&
            temp != nonstriker &&
            temp->isout == 0)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


static Player *findBowler(Player *head,
                          Player *striker,
                          Player *nonstriker)
{
    Player *temp = head;

    while (temp != NULL)
    {
        if (isBowler(temp) &&
            temp != striker &&
            temp != nonstriker)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


void play(Player *head,
          int totalovers)
{
    Player *striker = NULL;
    Player *nonstriker = NULL;
    Player *bowler = NULL;

    Player *temp;

    int runs;
    int wicket;
    int ball;
    int over;

    int totalRuns = 0;
    int totalWickets = 0;


    /* Find first two batsmen */

    temp = head;

    while (temp != NULL)
    {
        if (isBatsman(temp) &&
            temp->isout == 0)
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


    bowler = findBowler(head,
                        striker,
                        nonstriker);


    if (striker == NULL ||
        nonstriker == NULL ||
        bowler == NULL)
    {
        printf("\nNot enough players to start match.\n");
        return;
    }


    printf("\n========================================\n");
    printf("              MATCH STARTED\n");
    printf("========================================\n");


    for (over = 1;
         over <= totalovers;
         over++)
    {
        printf("\n========== OVER %d ==========\n",
               over);

        printf("Striker     : %s\n",
               striker->name);

        printf("Non-Striker : %s\n",
               nonstriker->name);

        printf("Bowler      : %s\n",
               bowler->name);


        for (ball = 1;
             ball <= 6;
             ball++)
        {
            printf("\nBall %d\n",
                   ball);

            printf("Striker: %s\n",
                   striker->name);

            printf("Enter runs (0,1,2,3,4,6): ");
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


            /* Update batsman */

            batting(striker,
                    runs);


            /* Update bowler */

            bowling(bowler,
                    runs);


            /* Update team score */

            totalRuns += runs;


            if (wicket == 1)
            {
                striker->isout = 1;

                totalWickets++;

                bowler->wickets++;

                printf("\nWICKET! %s is OUT!\n",
                       striker->name);

                if (totalWickets >= 10)
                {
                    printf("\nAll wickets lost!\n");
                    break;
                }


                striker =
                    findNextBatsman(head,
                                    striker,
                                    nonstriker);

                if (striker == NULL)
                {
                    printf("\nNo batsman available.\n");
                    break;
                }

                printf("New batsman: %s\n",
                       striker->name);
            }


            /*
             * Strike changes after odd runs.
             * If a wicket occurred, the new batsman
             * becomes striker.
             */
            if (wicket == 0 &&
                runs % 2 == 1)
            {
                temp = striker;
                striker = nonstriker;
                nonstriker = temp;
            }


            printf("\nCurrent Score: %d/%d\n",
                   totalRuns,
                   totalWickets);
        }


        if (totalWickets >= 10)
            break;


        /*
         * At the end of every over,
         * batsmen change ends.
         */
        temp = striker;
        striker = nonstriker;
        nonstriker = temp;


        printf("\nEnd of Over %d\n",
               over);

        printf("Score: %d/%d\n",
               totalRuns,
               totalWickets);
    }


    printf("\n========================================\n");
    printf("           INNINGS COMPLETED\n");
    printf("========================================\n");

    printf("Final Score: %d/%d\n",
           totalRuns,
           totalWickets);

    printf("Overs: %d.%d\n",
           over - 1,
           ball == 6 ? 0 : ball - 1);


    printf("\n========== PLAYER PERFORMANCE ==========\n");

    temp = head;

    while (temp != NULL)
    {
        if (temp->runs > 0 ||
            temp->wickets > 0)
        {
            printf("\n%s\n",
                   temp->name);

            printf("Runs       : %d\n",
                   temp->runs);

            printf("Balls      : %d\n",
                   temp->ballsfaced);

            printf("Wickets    : %d\n",
                   temp->wickets);

            printf("Balls Bowled: %d\n",
                   temp->ballsBowled);

            printf("Runs Given : %d\n",
                   temp->runsgiven);
        }

        temp = temp->next;
    }
}
