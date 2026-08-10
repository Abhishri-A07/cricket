#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"


void initializeMatch(MatchController *m)
{
    m->currentInnings = 0;

    m->currentOver = 0;
    m->currentBall = 0;

    m->totalBalls = 0;
    m->wickets = 0;
    m->runs = 0;

    m->maxOvers = MAX_OVERS;
    m->maxBalls = MAX_OVERS * 6;

    m->target = 0;

    m->battingTeam = -1;
    m->bowlingTeam = -1;

    m->state = NOT_STARTED;
}


void toss(MatchController *m)
{
    int tossWinner;
    int choice;

    tossWinner = rand() % 2;

    printf("\n=================================\n");
    printf("              TOSS\n");
    printf("=================================\n");

    printf("Team %c won the toss!\n",
           'A' + tossWinner);

    printf("\nCaptain's choice:\n");
    printf("1. Bat\n");
    printf("2. Bowl\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        m->battingTeam = tossWinner;
        m->bowlingTeam = 1 - tossWinner;

        printf("\nTeam %c chose to BAT first.\n",
               'A' + tossWinner);
    }
    else if (choice == 2)
    {
        m->bowlingTeam = tossWinner;
        m->battingTeam = 1 - tossWinner;

        printf("\nTeam %c chose to BOWL first.\n",
               'A' + tossWinner);
    }
    else
    {
        printf("\nInvalid choice!\n");
        printf("Default decision: BAT\n");

        m->battingTeam = tossWinner;
        m->bowlingTeam = 1 - tossWinner;
    }

    m->state = TOSS_DONE;

    printf("\nFirst Batting Team : Team %c\n",
           'A' + m->battingTeam);

    printf("First Bowling Team : Team %c\n",
           'A' + m->bowlingTeam);
}


void startInnings(MatchController *m,
                  int innings)
{
    m->currentInnings = innings;

    m->currentOver = 0;
    m->currentBall = 0;

    m->totalBalls = 0;
    m->wickets = 0;
    m->runs = 0;

    m->state = INNINGS_STARTED;

    printf("\n=================================\n");
    printf("           INNINGS %d\n",
           innings);
    printf("=================================\n");

    printf("Batting Team : Team %c\n",
           'A' + m->battingTeam);

    printf("Bowling Team : Team %c\n",
           'A' + m->bowlingTeam);

    if (innings == 2)
    {
        printf("Target: %d\n",
               m->target);
    }
}


void addBall(MatchController *m)
{
    if (m->state != INNINGS_STARTED)
        return;

    m->currentBall++;
    m->totalBalls++;

    if (m->currentBall == 6)
    {
        m->currentBall = 0;
        m->currentOver++;

        printf("\nOver %d completed.\n",
               m->currentOver);
    }
}


void addRuns(MatchController *m,
             int runs)
{
    if (m->state == INNINGS_STARTED)
        m->runs += runs;
}


void addWicket(MatchController *m)
{
    if (m->state != INNINGS_STARTED)
        return;

    if (m->wickets < MAX_WICKETS)
        m->wickets++;
}


int checkInningsEnd(struct MatchController *m)
{
    if (m->wickets >= MAX_WICKETS)
        return 1;

    if (m->totalBalls >= m->maxBalls)
        return 1;

    if (m->currentInnings == 2 && m->runs >= m->target)
        return 1;

    return 0;
}


void displayStatus(MatchController *m)
{
    printf("\n=================================\n");
    printf("           MATCH STATUS\n");
    printf("=================================\n");

    printf("Innings       : %d\n",
           m->currentInnings);

    if (m->battingTeam >= 0)
    {
        printf("Batting Team  : Team %c\n",
               'A' + m->battingTeam);

        printf("Bowling Team  : Team %c\n",
               'A' + m->bowlingTeam);
    }

    printf("Score         : %d/%d\n",
           m->runs,
           m->wickets);

    printf("Overs         : %d.%d\n",
           m->currentOver,
           m->currentBall);

    printf("Balls         : %d/%d\n",
           m->totalBalls,
           m->maxBalls);

    if (m->currentInnings == 2)
    {
        printf("Target        : %d\n",
               m->target);

        if (m->runs < m->target)
        {
            printf("Runs Required : %d\n",
                   m->target - m->runs);
        }
        else
        {
            printf("Target Reached!\n");
        }
    }

    printf("=================================\n");
}


void endInnings(MatchController *m)
{
    printf("\n=================================\n");
    printf("        INNINGS COMPLETED\n");
    printf("=================================\n");

    printf("Team %c Score : %d/%d\n",
           'A' + m->battingTeam,
           m->runs,
           m->wickets);

    printf("Overs         : %d.%d\n",
           m->currentOver,
           m->currentBall);

    if (m->wickets >= MAX_WICKETS)
    {
        printf("Reason: All wickets lost.\n");
    }
    else if (m->totalBalls >= m->maxBalls)
    {
        printf("Reason: All overs completed.\n");
    }
    else if (m->currentInnings == 2 &&
             m->runs >= m->target)
    {
        printf("Reason: Target reached.\n");
    }

    m->state = INNINGS_COMPLETED;
}


void startSecondInnings(struct MatchController *m)
{
    int firstInningsScore;
    int temp;

    /* Store first innings score */
    firstInningsScore = m->runs;

    /* Swap batting and bowling teams */
    temp = m->battingTeam;
    m->battingTeam = m->bowlingTeam;
    m->bowlingTeam = temp;

    /* Set target for second innings */
    m->target = firstInningsScore + 1;

    /* Start second innings */
    startInnings(m, 2);
}
