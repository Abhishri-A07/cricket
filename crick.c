#include <stdio.h>
#include <string.h>

#define MAX 100

struct Ball
{
    int no, runs, wicket;
    char result[15];
};

struct Queue
{
    struct Ball b[MAX];
    int front, rear;
};

struct Score
{
    int runs, wickets, balls, target;
    char batsman[30], bowler[30];
    int bruns, bballs, fours, sixes;
    int bwickets, bruns_conceded, bballs_bowled;
};

void enqueue(struct Queue *q, int no, int runs, int wicket, char result[])
{
    if (q->rear < MAX - 1)
    {
        q->rear++;
        q->b[q->rear].no = no;
        q->b[q->rear].runs = runs;
        q->b[q->rear].wicket = wicket;
        strcpy(q->b[q->rear].result, result);
    }
}

void scoreboard(struct Score *s)
{
    printf("\n-------------------------\n");
    printf("SCORE: %d/%d\n", s->runs, s->wickets);
    printf("OVERS: %d.%d\n", s->balls / 6, s->balls % 6);
    printf("BATSMAN: %s  %d(%d)  SR: %.2f\n",
           s->batsman, s->bruns, s->bballs,
           s->bballs ? (s->bruns * 100.0 / s->bballs) : 0);
    printf("BOWLER: %s  %d/%d  Eco: %.2f\n",
           s->bowler, s->bwickets, s->bruns_conceded,
           s->bballs_bowled ? s->bruns_conceded / (s->bballs_bowled / 6.0) : 0);

    if (s->target)
    {
        int need = s->target - s->runs, left = 120 - s->balls;
        if (need < 0)
            need = 0;
        printf("TARGET: %d  NEED: %d\n", s->target, need);
        printf("REQUIRED RR: %.2f\n",
               left > 0 ? need * 6.0 / left : 0);
    }
    printf("-------------------------\n");
}

void displayQueue(struct Queue *q)
{
    int i;
    printf("\nBALL-BY-BALL\n");
    for (i = q->front; i <= q->rear; i++)
        printf("Ball %d : %s\n", q->b[i].no, q->b[i].result);
}

void battingCard(struct Score *s)
{
    printf("\nBATTING CARD\n");
    printf("Player: %s\nRuns: %d  Balls: %d  4's: %d  6's: %d\n",
           s->batsman, s->bruns, s->bballs, s->fours, s->sixes);
    printf("Strike Rate: %.2f\n",
           s->bballs ? s->bruns * 100.0 / s->bballs : 0);
}

void bowlingCard(struct Score *s)
{
    printf("\nBOWLING CARD\n");
    printf("Bowler: %s\nOvers: %d.%d  Runs: %d  Wickets: %d\n",
           s->bowler, s->bballs_bowled / 6, s->bballs_bowled % 6,
           s->bruns_conceded, s->bwickets);
    printf("Economy: %.2f\n",
           s->bballs_bowled ? s->bruns_conceded / (s->bballs_bowled / 6.0) : 0);
}
