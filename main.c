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

    return 0;


}
