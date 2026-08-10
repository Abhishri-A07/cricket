#include <stdio.h>
#include "player.h"

int main()
{
    int choice;
    int totalOvers;

    do
    {
        printf("\n\n========== CRICKET MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Player\n");
        printf("2. Delete Player\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Display All Players\n");
        printf("6. Start Match\n");
        printf("7. Performance Calculation\n");
        printf("8. Player Ranking\n");
        printf("9. Best Players\n");
        printf("10. Sort Players\n");
        printf("11. Exit\n");
        printf("===============================================\n");

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
                printf("\nEnter number of overs: ");
                scanf("%d", &totalOvers);

                if (totalOvers <= 0)
                {
                    printf("Invalid number of overs!\n");
                }
                else
                {
                    play(head, totalOvers);
                }
                break;

            case 7:
                performance(head);
                printf("\nPerformance calculated successfully.\n");
                break;

            case 8:
                ranking(head);
                break;

            case 9:
                bestplayer(head);
                break;

            case 10:
                sortplayer(head);
                printf("\nPlayers sorted successfully.\n");
                break;

            case 11:
                freeDatabase();
                printf("\nPlayer database closed.\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 11);

    return 0;
}
