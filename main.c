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
      return 0;
}
