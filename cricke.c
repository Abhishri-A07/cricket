#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#define MAX_OVERS 20 
#define MAX_WICKETS 10 
#define NOT_STARTED 0 
#define TOSS_DONE 1 
#define INNINGS_STARTED 2 
#define INNINGS_COMPLETED 3 
#define MATCH_COMPLETED 4
struct MatchController 
{ 
int currentInnings; int currentOver;
int currentBall;
int totalBalls; int wickets; 
int runs; int maxOvers; 
int maxBalls;
int target; 
int battingTeam;
int bowlingTeam;
int state; 
}; 
void initializeMatch(struct MatchController *m) 
{ 
m->currentInnings = 0; 
m->currentOver = 0;
 m->currentBall = 0; 
m->totalBalls = 0;
 m->wickets = 0; 
m->runs = 0; 
m->maxOvers = MAX_OVERS;
 m->maxBalls = MAX_OVERS * 6; m->target = 0; 
m->battingTeam = -1;
 m->bowlingTeam = -1;
 m->state = NOT_STARTED; 
} 
void toss(struct MatchController *m) 
{ 
int tossWinner; int choice; tossWinner = rand() % 2;
printf("\n=================================\n"); 
printf("TOSS\n"); 
printf("=================================\n");
printf("Team %c won the toss!\n",tossWinner == 0 ? 'A' : 'B'); 
printf("\nCaptain's choice:\n"); 
printf("1. Bat\n"); 
printf("2. Bowl\n");
printf("Enter choice: "); 
scanf("%d", &choice);
switch (choice) 
{ 
case 1: 
m->battingTeam = tossWinner; 
m->bowlingTeam = 1 - tossWinner; 
printf("\nTeam %c chose to BAT first.\n",tossWinner == 0 ? 'A' : 'B');
break; 
case 2: 
m->bowlingTeam = tossWinner; 
m->battingTeam = 1 - tossWinner;
printf("\nTeam %c chose to BOWL first.\n",tossWinner == 0 ? 'A' : 'B');
break; 
default: 
printf("\nInvalid choice!\n"); 
printf("Default decision: BAT\n"); 
m->battingTeam = tossWinner; 
m->bowlingTeam = 1 - tossWinner; 
} 
m->state = TOSS_DONE; 
printf("\nFirst Batting Team : Team %c\n",'A' + m->battingTeam);
printf("First Bowling Team : Team %c\n",'A' + m->bowlingTeam); 
} 
void startInnings(struct MatchController *m, int innings) 
{ 
m->currentInnings = innings; m->currentOver = 0; 
m->currentBall = 0; 
m->totalBalls = 0; 
m->wickets = 0; 
m->runs = 0; 
m->state = INNINGS_STARTED; printf("\===============\n"); 
printf(“INNINGS %d\n", innings); 
printf("=================================\n");
printf("Batting Team : Team %c\n",'A' + m->battingTeam);
printf("Bowling Team : Team %c\n",'A' + m->bowlingTeam); 
if (innings == 2) 
{ 
printf("Target: %d\n", m->target); 
} 
} 
void addBall(struct MatchController *m) 
{ 
if (m->state != INNINGS_STARTED) return; 
m->currentBall++; 
m->totalBalls++;
if (m->currentBall == 6) 
{ 
m->currentBall = 0; 
m->currentOver++; 
printf("\nOver %d completed.\n",m->currentOver); 
 } 
} 
void addRuns(struct MatchController *m, int runs) 
{ 
m->runs += runs; 
} 
void addWicket(struct MatchController *m) 
{ 
if (m->wickets < MAX_WICKETS) m->wickets++; 
} 
int checkInningsEnd(struct MatchController *m) 
{ 
if (m->wickets >= MAX_WICKETS) 
return 1; 
if (m->totalBalls >= m->maxBalls) 
return 1; 
if (m->currentInnings == 2 &&m->runs >= m->target)
retun 1;

} 
void displayStatus(struct MatchController *m) 
{ 
printf("\n=================================\n"); printf("MATCH STATUS\n"); printf("=================================\n"); printf("Innings      : %d\n",m->currentInnings); 
printf("Batting Team  : Team %c\n",'A' + m->battingTeam); printf("Bowling Team  : Team %c\n",'A' + m->bowlingTeam); printf("Score         : %d/%d\n",m->runs,m->wickets); 
printf("Overs         : %d.%d\n",m->currentOver,m->currentBall); printf("Balls         : %d/%d\n",m->totalBalls,m->maxBalls); 
if (m->currentInnings == 2) 
{ 
printf("Target        : %d\n",m->target); 
if (m->runs < m->target) 
{ 
printf("Runs Required : %d\n",m->target - m->runs); 
} 
else 
{ 
 printf("Target Reached!\n"); 
 } 
 } 
printf("=================================\n"); 
} 
void endInnings(struct MatchController *m) 
{ 
printf("\n=================================\n"); 
printf("        INNINGS COMPLETED\n"); printf("=================================\n"); 
printf("Team %c Score : %d/%d\n",'A' + m->battingTeam,m->runs,m->wickets); printf("Overs         : %d.%d\n",m->currentOver,m->currentBall); 
if (m->wickets >= MAX_WICKETS) 
{ 
printf("Reason: All wickets lost.\n"); 
} 
else if (m->totalBalls >= m->maxBalls) 
{ 
printf("Reason: All overs completed.\n"); 
} 
else if (m->currentInnings == 2 &&m->runs >= m->target) 
{ 
printf("Reason: Target reached.\n"); 
} 
m->state = INNINGS_COMPLETED; 
} 
void startSecondInnings(struct MatchController *m) 
{ 
int firstInningsScore; 
firstInningsScore = m->runs; 
int temp = m->battingTeam; 
m->battingTeam = m->bowlingTeam; m->bowlingTeam = temp; 
m->target = firstInningsScore + 1; startInnings(m, 2); 
} 
