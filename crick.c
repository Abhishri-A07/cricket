#include <stdio.h>
#include <string.h>
#include "player.h"


void initializeQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}


void enqueue(Queue *q,
             int no,
             int runs,
             int wicket,
             const char result[])
{
    if (q->rear >= MAX_BALLS - 1)
        return;

    q->rear++;

    q->b[q->rear].no = no;
    q->b[q->rear].runs = runs;
    q->b[q->rear].wicket = wicket;

    strcpy(q->b[q->rear].result,
           result);
}


void scoreboard(Score *s)
{
    printf("\n-------------------------\n");

    printf("SCORE: %d/%d\n",
           s->runs,
           s->wickets);

    printf("OVERS: %d.%d\n",
           s->balls / 6,
           s->balls % 6);

    printf("BATSMAN: %s  %d(%d)  SR: %.2f\n",
           s->batsman,
           s->bruns,
           s->bballs,
           s->bballs ?
           (s->bruns * 100.0 / s->bballs) : 0);

    printf("BOWLER: %s  %d/%d  Eco: %.2f\n",
           s->bowler,
           s->bwickets,
           s->bruns_conceded,
           s->bballs_bowled ?
           s->bruns_conceded /
           (s->bballs_bowled / 6.0) : 0);

    if (s->target > 0)
    {
        int need = s->target - s->runs;
        int left = 120 - s->balls;

        if (need < 0)
            need = 0;

        printf("TARGET: %d  NEED: %d\n",
               s->target,
               need);

        printf("REQUIRED RR: %.2f\n",
               left > 0 ?
               need * 6.0 / left : 0);
    }

    printf("-------------------------\n");
}


void displayQueue(Queue *q)
{
    int i;

    printf("\n========== BALL-BY-BALL ==========\n");

    for (i = q->front; i <= q->rear; i++)
    {
        printf("Ball %d : %s\n",
               q->b[i].no,
               q->b[i].result);
    }
}


void battingCard(Score *s)
{
    printf("\n========== BATTING CARD ==========\n");

    printf("Player: %s\n",
           s->batsman);

    printf("Runs: %d  Balls: %d  4's: %d  6's: %d\n",
           s->bruns,
           s->bballs,
           s->fours,
           s->sixes);

    printf("Strike Rate: %.2f\n",
           s->bballs ?
           s->bruns * 100.0 / s->bballs : 0);
}


void bowlingCard(Score *s)
{
    printf("\n========== BOWLING CARD ==========\n");

    printf("Bowler: %s\n",
           s->bowler);

    printf("Overs: %d.%d  Runs: %d  Wickets: %d\n",
           s->bballs_bowled / 6,
           s->bballs_bowled % 6,
           s->bruns_conceded,
           s->bwickets);

    printf("Economy: %.2f\n",
           s->bballs_bowled ?
           s->bruns_conceded /
           (s->bballs_bowled / 6.0) : 0);
}
