#include<stdio.h>
#include "player.h"
int main()
{
    int choice;
    do
    {
        printf("\n\n========== CRICKET PLAYER DATABASE ==========\n");
        printf("1. Add Player\n");
        printf("2. Delete Player\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Display All Players\n");
        printf("6. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
               addPlayer();
                break;
           case 2:
                deletePlayer();
                break;
           case 3:
                searchAndDisplay();
                break;
           case 4:
                updatePlayer();
                break;
           case 5:
                displayAllPlayers();
                break;
           case 6:
                freeDatabase();
                printf("\nPlayer database closed.\n");
                break;
           default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 6);
      
     struct Queue q = {{{0}}, 0, -1};
    struct Score s = {0, 0, 0, 0, "Batsman", "Bowler", 0, 0, 0, 0, 0, 0, 0};
    int x, w;

    printf("Enter target (0 for first innings): ");
    scanf("%d", &s.target);

    while (s.balls < 12 && s.wickets < 10)
    {
        printf("\nRuns (0,1,2,3,4,6): ");
        scanf("%d", &x);
        if (x != 0 && x != 1 && x != 2 && x != 3 && x != 4 && x != 6)
            continue;

        printf("Wicket? (1/0): ");
        scanf("%d", &w);

        s.balls++;
        s.runs += x;
        s.bballs++;
        s.bruns += x;
        s.bballs_bowled++;
        s.bruns_conceded += x;

        if (x == 4)
            s.fours++;
        if (x == 6)
            s.sixes++;
        if (w)
        {
            s.wickets++;
            s.bwickets++;
        }

        if (x == 0)
            strcpy(s.balls % 6 == 0 ? (char[15]){"OVER"} : (char[15]){"DOT"}, "");

        char result[15];
        if (w)
            strcpy(result, "WICKET");
        else if (x == 4)
            strcpy(result, "FOUR");
        else if (x == 6)
            strcpy(result, "SIX");
        else if (x == 0)
            strcpy(result, "DOT");
        else
            sprintf(result, "%d RUN", x);

        enqueue(&q, s.balls, x, w, result);
        scoreboard(&s);

        if (s.target && s.runs >= s.target)
            break;
    }

    battingCard(&s);
    bowlingCard(&s);
    displayQueue(&q);

struct MatchController match; int choice; 
int runs; 
int ballResult; srand(time(NULL)); initializeMatch(&match); 
do 
{ 
printf("\n\n=================================\n"); 
printf(“CRICKET MATCH CONTROLLER\n"); printf("=================================\n"); 
printf("1. Conduct Toss\n"); 
printf("2. Start First Innings\n"); 
printf("3. Add Ball\n"); 
printf("4. Add Runs\n"); 
printf("5. Add Wicket\n"); 
printf("6. Display Match Status\n"); 
printf("7. Check Innings Completion\n"); 
printf("8. End Innings\n"); 
printf("9. Start Second Innings\n"); 
printf("10. Exit\n"); 
printf("\nEnter your choice: "); 
scanf("%d", &choice); 
switch (choice) 
{ 
case 1: if (match.state ==NOT_STARTED) 
{ 
toss(&match); 
} 
Else 
{ 
printf("\nToss has already been completed.\n"); 
} 
break; 
case 2: 
if(match.state== TOSS_DONE) 
  { 
 startInnings(&match, 1); 
 } 
 else 
 { 
printf("\nPlease conduct the toss first.\n"); 
 } 
break; 
case 3:
 if (match.state == INNINGS_STARTED) 
{ 
addBall(&match) 
printf("\nBall completed successfully.\n"); 
if (checkInningsEnd(&match)) 
{ 
printf("\nInnings should now end.\n"); 
} 
Else 
{ 
printf("\nNo innings is currently running.\n"); 
} 
break; 
case 4: 
if (match.state == INNINGS_STARTED) 
{ 
printf("Enter runs scored: "); scanf("%d", &runs); 
if (runs >= 0 && runs <= 6) 
{ 
addRuns(&match, runs); 
printf("\n%d run(s) added.\n", runs); 
} 
else 
{ 
printf("\nInvalid number of runs.\n"); 
} 
} 
else 
{ 
printf("\nStart an innings first.\n"); 
} 
break; 
case 5:  
if (match.state == INNINGS_STARTED) 
 { 
 addWicket(&match); printf("\nWicket added.\n"); 
if (checkInningsEnd(&match)) 
{ 
printf("All wickets lost or innings completed.\n"); 
} 
} 
Else 
{ 
printf("\nStart an innings first.\n"); 
}
break; 
case 6: displayStatus(&match); break; 
case 7: 
if (match.state == INNINGS_STARTED) 
{ 
if (checkInningsEnd(&match) 
{ 
printf("\n INNINGS COMPLETED \n"); 
if (match.wickets >= MAX_WICKETS) 
printf("Reason: All wickets lost.\n"); 
else if (match.totalBalls >= match.maxBalls) 
printf("Reason: Overs completed.\n"); 
else if (match.currentInnings == 2 &&match.runs >= match.target) printf("Reason: Target reached.\n"); 
} 
else 
{ 
printf("\nInnings is still in progress.\n"); 
} 
} 
else 
{ 
printf("\nNo active innings.\n"); 
} 
Break; 
case 8: 
if(match.state == INNINGS_STARTED) 
{ 
endInnings(&match); 
} 
else 
{ 
printf("\nNo active innings to end.\n"); 
} 
break; 
case 9: 
if (match.state == INNINGS_COMPLETED &&match.currentInnings == 1) 
{ 
startSecondInnings(&match); 
} 
else 
{ 
printf("\nFirst innings must be completed first.\n"); 
} 
break; 
case 10: 
printf("\nExiting Match Controller...\n"); break; 
default: 
printf("\nInvalid choice! Please try again\n"); 
} 
} while (choice != 10); 

    return 0;


}
