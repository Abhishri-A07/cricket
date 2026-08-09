#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Player
{
    int id;
    char name[30];
    char role[20];
    int runs;
    int wickets;
    float strikeRate;
    float economy;
    float performance;
    struct Player *prev;
    struct Player *next;
};
struct Player *head = NULL;
struct Player *tail = NULL;
float calculatePerformance(struct Player *p)
{
    return (p->runs * 0.5) +
           (p->wickets * 20) +
           (p->strikeRate * 0.2) +
           (p->economy * 0.1);
}
void addPlayer()
{
    struct Player *newPlayer;
    newPlayer = (struct Player *)malloc(sizeof(struct Player));
    if (newPlayer == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("\nEnter Player ID: ");
    scanf("%d", &newPlayer->id);
    struct Player *temp = head;
    while (temp != NULL)
    {
        if (temp->id == newPlayer->id)
        {
            printf("Player ID already exists!\n");
            free(newPlayer);
            return;
        }
    temp = temp->next;
    }
    printf("Enter Player Name: ");
    scanf(" %[^\n]", newPlayer->name);
    printf("Enter Player Role (Batsman/Bowler/All-Rounder): ");
    scanf(" %[^\n]", newPlayer->role);
    printf("Enter Previous Runs: ");
    scanf("%d", &newPlayer->runs);
    printf("Enter Previous Wickets: ");
    scanf("%d", &newPlayer->wickets);
    printf("Enter Strike Rate: ");
    scanf("%f", &newPlayer->strikeRate);
    printf("Enter Economy: ");
    scanf("%f", &newPlayer->economy);
    newPlayer->performance = calculatePerformance(newPlayer);
    newPlayer->prev = NULL;
    newPlayer->next = NULL;
    if (head == NULL)
    {
        head = newPlayer;
        tail = newPlayer;
    }
    else
    {
        tail->next = newPlayer;
        newPlayer->prev = tail;
        tail = newPlayer;
    }
    printf("\nPlayer added successfully!\n");
}
struct Player *searchPlayer(int id)
{
    struct Player *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
       temp = temp->next;
    }
return NULL;
}
void displayPlayer(struct Player *p)
{
    printf("\n----------------------------------------\n");
    printf("Player ID       : %d\n", p->id);
    printf("Name            : %s\n", p->name);
    printf("Role            : %s\n", p->role);
    printf("Previous Runs   : %d\n", p->runs);
    printf("Wickets         : %d\n", p->wickets);
    printf("Strike Rate     : %.2f\n", p->strikeRate);
    printf("Economy         : %.2f\n", p->economy);
    printf("Performance     : %.2f\n", p->performance);
    printf("----------------------------------------\n");
}
void searchAndDisplay()
{
    int id;
    printf("\nEnter Player ID to search: ");
    scanf("%d", &id);
    struct Player *p = searchPlayer(id);
    if (p == NULL)
    {
        printf("Player not found!\n");
    }
    else
    {
        printf("\nPlayer found!\n");
        displayPlayer(p);
    }
}
void updatePlayer()
{
    int id;
   printf("\nEnter Player ID to update: ");
    scanf("%d", &id);
    struct Player *p = searchPlayer(id);
    if (p == NULL)
    {
        printf("Player not found!\n");
        return;
    }
    printf("\nEnter New Player Name: ");
    scanf(" %[^\n]", p->name);
    printf("Enter New Role: ");
    scanf(" %[^\n]", p->role);
    printf("Enter New Previous Runs: ");
    scanf("%d", &p->runs);
    printf("Enter New Wickets: ");
    scanf("%d", &p->wickets);
    printf("Enter New Strike Rate: ");
    scanf("%f", &p->strikeRate);
    printf("Enter New Economy: ");
    scanf("%f", &p->economy);
    p->performance = calculatePerformance(p);
    printf("\nPlayer details updated successfully!\n");
}
void deletePlayer()
{
    int id;
    printf("\nEnter Player ID to delete: ");
    scanf("%d", &id);
    struct Player *p = searchPlayer(id);
    if (p == NULL)
    {
        printf("Player not found!\n");
        return;
    }
   if (p == head)
    {
        head = p->next;
    }
    if (p == tail)
    {
        tail = p->prev;
    }
   if (p->prev != NULL)
    {
        p->prev->next = p->next;
    }
   if (p->next != NULL)
    {
        p->next->prev = p->prev;
    }
   free(p);
   printf("\nPlayer deleted successfully!\n");
}
void displayAllPlayers()
{
    struct Player *temp = head;
    if (head == NULL)
    {
        printf("\nNo players available in database.\n");
        return;
    }
      printf("\n================ PLAYER DATABASE ================\n");
      while (temp != NULL)
    {
        printf("\nID          : %d", temp->id);
        printf("\nName        : %s", temp->name);
        printf("\nRole        : %s", temp->role);
        printf("\nRuns        : %d", temp->runs);
        printf("\nWickets     : %d", temp->wickets);
        printf("\nStrike Rate : %.2f", temp->strikeRate);
        printf("\nEconomy     : %.2f", temp->economy);
        printf("\nPerformance : %.2f", temp->performance);
        printf("\n-----------------------------------------------");
       temp = temp->next;
    }
}
void freeDatabase()
{
    struct Player *temp = head;
    while (temp != NULL)
    {
        struct Player *next = temp->next;
        free(temp);
        temp = next;
    }
   head = NULL;
    tail = NULL;
}
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
