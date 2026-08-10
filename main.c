#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"


void playerDatabaseMenu(void)
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
        printf("6. Back\n");

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
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 6);
}


void runAuction(void)
{
    AuctionTeam teamA;
    AuctionTeam teamB;

    AuctionResult results[100];

    Player *temp;

    int count = 0;
    int choice;


    initializeTeam(&teamA,
                   "Team A");

    initializeTeam(&teamB,
                   "Team B");


    temp = head;


    if (temp == NULL)
    {
        printf("\nNo players available for auction.\n");
        return;
    }


    while (temp != NULL)
    {
        printf("\nAuction player: %s\n",
               temp->name);

        printf("1. Auction this player\n");
        printf("2. Skip\n");
        printf("Enter choice: ");

        scanf("%d", &choice);


        if (choice == 1)
        {
            auctionPlayer(temp,
                          &teamA,
                          &teamB,
                          &results[count]);

            count++;
        }


        temp = temp->next;
    }


    displayFinalReport(results,
                       count,
                       &teamA,
                       &teamB);
}


void runSquadSelection(void)
{
    Player squad[MAX_SQUAD];
    Player xi[11];

    int n;


    getSquad(squad,
             &n);

    getLineup(squad,
              n,
              xi);

    battingOrder(xi);

    selectCaptain(xi);

    selectKeeper(xi);

    bowlingPlan(xi);

    displayLineup(xi);
}


void runMatch(void)
{
    MatchController match;

    int innings;


    srand((unsigned int)time(NULL));

    initializeMatch(&match);


    printf("\n========================================\n");
    printf("             CRICKET MATCH\n");
    printf("========================================\n");


    /*
     * Toss
     */

    toss(&match);


    /*
     * First innings
     */

    startInnings(&match,
                 1);


    /*
     * Actual ball-by-ball match
     */

    play(head,
         MAX_OVERS);


    /*
     * Store first innings score
     *
     * Since play() maintains the player records,
     * the controller is used here mainly for
     * match state management.
     */

    match.state = INNINGS_COMPLETED;


    printf("\nFirst innings completed.\n");


    /*
     * Second innings
     */

    printf("\nStarting second innings...\n");

    startSecondInnings(&match);

    play(head,
         MAX_OVERS);


    match.state = MATCH_COMPLETED;


    printf("\n========================================\n");
    printf("             MATCH COMPLETED\n");
    printf("========================================\n");
}


int main(void)
{
    int choice;


    do
    {
        printf("\n\n============================================\n");
        printf("          CRICKET MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. Player Database\n");
        printf("2. Player Auction\n");
        printf("3. Squad / Playing XI Selection\n");
        printf("4. Start Cricket Match\n");
        printf("5. Performance Ranking\n");
        printf("6. Best Players\n");
        printf("7. Sort Players\n");
        printf("8. Display All Players\n");
        printf("9. Start second innings\n");
        printf("10. Exit\n");


        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                playerDatabaseMenu();
                break;


            case 2:
                runAuction();
                break;


            case 3:
                runSquadSelection();
                break;


            case 4:
                if (head == NULL)
                {
                    printf("\nAdd players before starting a match.\n");
                }
                else
                {
                    runMatch();
                }
                break;


            case 5:
                performance(head);
                ranking(head);
                break;


            case 6:
                performance(head);
                bestplayer(head);
                break;


            case 7:
                performance(head);
                sortplayer(head);

                printf("\nPlayers sorted according to performance.\n");

                ranking(head);
                break;


            case 8:
                displayAllPlayers();
                break;


            case 9:
            if (match.state == INNINGS_COMPLETED &&
            match.currentInnings == 1)
            {
            startSecondInnings(&match);
            }
            else
            {
            printf("\nFirst innings must be completed first.\n");
            }
            break;
            case 10:
                freeDatabase();

                printf("\nExiting Cricket Management System...\n");
                break;


            default:
                printf("\nInvalid choice! Try again.\n");
        }


    } while (choice != 9);


    return 0;
}
