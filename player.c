#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

Player *head = NULL;
Player *tail = NULL;


/* ================= ADD PLAYER ================= */

void addPlayer(void)
{
    Player *newPlayer;
    Player *temp;

    newPlayer = (Player *)malloc(sizeof(Player));

    if (newPlayer == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Player ID: ");
    scanf("%d", &newPlayer->id);

    temp = head;

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

    printf("Enter Player Role (BATSMAN/BOWLER/ALLROUNDER): ");
    scanf(" %[^\n]", newPlayer->role);

    printf("Enter Previous Runs: ");
    scanf("%d", &newPlayer->pruns);

    printf("Enter Previous Wickets: ");
    scanf("%d", &newPlayer->pwickets);

    printf("Enter Strike Rate: ");
    scanf("%f", &newPlayer->strikeRate);

    printf("Enter Economy: ");
    scanf("%f", &newPlayer->economy);

    printf("Enter Base Price: ");
    scanf("%f", &newPlayer->basePrice);

    newPlayer->runs = 0;
    newPlayer->wickets = 0;
    newPlayer->performance = 0;

    newPlayer->ballsfaced = 0;
    newPlayer->isout = 0;

    newPlayer->ballsBowled = 0;
    newPlayer->runsgiven = 0;

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


/* ================= SEARCH ================= */

Player *searchPlayer(int id)
{
    Player *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}


/* ================= DISPLAY PLAYER ================= */

void displayPlayer(Player *p)
{
    if (p == NULL)
        return;

    printf("\n----------------------------------------\n");
    printf("Player ID       : %d\n", p->id);
    printf("Name            : %s\n", p->name);
    printf("Role            : %s\n", p->role);
    printf("Previous Runs   : %d\n", p->pruns);
    printf("Previous Wickets: %d\n", p->pwickets);
    printf("Strike Rate     : %.2f\n", p->strikeRate);
    printf("Economy         : %.2f\n", p->economy);
    printf("Base Price      : %.2f Cr\n", p->basePrice);
    printf("----------------------------------------\n");
}


/* ================= SEARCH AND DISPLAY ================= */

void searchAndDisplay(void)
{
    int id;
    Player *p;

    printf("\nEnter Player ID to search: ");
    scanf("%d", &id);

    p = searchPlayer(id);

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


/* ================= UPDATE ================= */

void updatePlayer(void)
{
    int id;
    Player *p;

    printf("\nEnter Player ID to update: ");
    scanf("%d", &id);

    p = searchPlayer(id);

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
    scanf("%d", &p->pruns);

    printf("Enter New Previous Wickets: ");
    scanf("%d", &p->pwickets);

    printf("Enter New Strike Rate: ");
    scanf("%f", &p->strikeRate);

    printf("Enter New Economy: ");
    scanf("%f", &p->economy);

    printf("Enter New Base Price: ");
    scanf("%f", &p->basePrice);

    p->performance = calculatePerformance(p);

    printf("\nPlayer details updated successfully!\n");
}


/* ================= DELETE ================= */

void deletePlayer(void)
{
    int id;
    Player *p;

    printf("\nEnter Player ID to delete: ");
    scanf("%d", &id);

    p = searchPlayer(id);

    if (p == NULL)
    {
        printf("Player not found!\n");
        return;
    }

    if (p->prev != NULL)
        p->prev->next = p->next;
    else
        head = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;
    else
        tail = p->prev;

    free(p);

    printf("\nPlayer deleted successfully!\n");
}


/* ================= DISPLAY ALL ================= */

void displayAllPlayers(void)
{
    Player *temp = head;

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
        printf("\nRuns        : %d", temp->pruns);
        printf("\nWickets     : %d", temp->pwickets);
        printf("\nStrike Rate : %.2f", temp->strikeRate);
        printf("\nEconomy     : %.2f", temp->economy);
        printf("\nBase Price  : %.2f Cr", temp->basePrice);
        printf("\n-----------------------------------------------\n");

        temp = temp->next;
    }
}


/* ================= FREE DATABASE ================= */

void freeDatabase(void)
{
    Player *temp = head;

    while (temp != NULL)
    {
        Player *next = temp->next;
        free(temp);
        temp = next;
    }

    head = NULL;
    tail = NULL;
}
