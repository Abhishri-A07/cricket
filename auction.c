#include <stdio.h>
#include <string.h>
#include "player.h"


void initializeTeam(AuctionTeam *team,
                    const char name[])
{
    strcpy(team->name, name);
    team->budget = INITIAL_BUDGET;
    team->spent = 0.0f;
    team->playerCount = 0;
}


void displayAuctionPlayer(Player *player)
{
    printf("\n========================================\n");
    printf("              PLAYER AUCTION\n");
    printf("========================================\n");

    printf("Player ID   : %d\n", player->id);
    printf("Player Name : %s\n", player->name);
    printf("Role        : %s\n", player->role);
    printf("Base Price  : %.2f Cr\n", player->basePrice);

    printf("========================================\n");
}


void auctionPlayer(Player *player,
                   AuctionTeam *teamA,
                   AuctionTeam *teamB,
                   AuctionResult *result)
{
    float currentBid = player->basePrice;
    float bid;

    int choice;
    int highestBidder = 0;

    displayAuctionPlayer(player);

    while (1)
    {
        printf("\n%s\n", teamA->name);
        printf("Budget      : %.2f Cr\n", teamA->budget);
        printf("Current Bid : %.2f Cr\n", currentBid);

        printf("1. Bid\n");
        printf("2. Pass\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter Team A bid: ");
            scanf("%f", &bid);

            if (bid <= currentBid)
            {
                printf("Bid must be greater than %.2f Cr\n",
                       currentBid);
                continue;
            }

            if (bid > teamA->budget)
            {
                printf("Insufficient budget!\n");
                continue;
            }

            currentBid = bid;
            highestBidder = 1;

            printf("Team A bid %.2f Cr\n",
                   currentBid);
        }
        else if (choice == 2)
        {
            printf("Team A passed.\n");

            if (highestBidder == 2)
                break;
        }
        else
        {
            printf("Invalid choice!\n");
            continue;
        }


        printf("\n%s\n", teamB->name);
        printf("Budget      : %.2f Cr\n", teamB->budget);
        printf("Current Bid : %.2f Cr\n", currentBid);

        printf("1. Bid\n");
        printf("2. Pass\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter Team B bid: ");
            scanf("%f", &bid);

            if (bid <= currentBid)
            {
                printf("Bid must be greater than %.2f Cr\n",
                       currentBid);
                continue;
            }

            if (bid > teamB->budget)
            {
                printf("Insufficient budget!\n");
                continue;
            }

            currentBid = bid;
            highestBidder = 2;

            printf("Team B bid %.2f Cr\n",
                   currentBid);
        }
        else if (choice == 2)
        {
            printf("Team B passed.\n");

            if (highestBidder == 1 || highestBidder==0)
                break;
        }
        else
        {
            printf("Invalid choice!\n");
            continue;
        }
    }


    result->playerID = player->id;
    strcpy(result->playerName, player->name);


    if (highestBidder == 0)
    {
        printf("\n%s is UNSOLD!\n",
               player->name);

        strcpy(result->teamName, "UNSOLD");
        result->soldPrice = 0.0f;
    }
    else if (highestBidder == 1)
    {
        printf("\n%s SOLD TO TEAM A\n",
               player->name);

        printf("Final Price: %.2f Cr\n",
               currentBid);

        teamA->budget -= currentBid;
        teamA->spent += currentBid;
        teamA->playerCount++;

        strcpy(result->teamName, teamA->name);
        result->soldPrice = currentBid;
    }
    else
    {
        printf("\n%s SOLD TO TEAM B\n",
               player->name);

        printf("Final Price: %.2f Cr\n",
               currentBid);

        teamB->budget -= currentBid;
        teamB->spent += currentBid;
        teamB->playerCount++;

        strcpy(result->teamName, teamB->name);
        result->soldPrice = currentBid;
    }
}


void displayFinalReport(AuctionResult results[],
                        int count,
                        AuctionTeam *teamA,
                        AuctionTeam *teamB)
{
    int i;

    printf("\n============================================\n");
    printf("              FINAL AUCTION REPORT\n");
    printf("============================================\n");

    printf("%-5s %-20s %-15s %-10s\n",
           "ID",
           "PLAYER",
           "TEAM",
           "PRICE");

    printf("--------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-5d %-20s %-15s %.2f Cr\n",
               results[i].playerID,
               results[i].playerName,
               results[i].teamName,
               results[i].soldPrice);
    }

    printf("\nTEAM A\n");
    printf("Amount Spent   : %.2f Cr\n",
           teamA->spent);

    printf("Remaining      : %.2f Cr\n",
           teamA->budget);

    printf("Players Bought : %d\n",
           teamA->playerCount);


    printf("\nTEAM B\n");
    printf("Amount Spent   : %.2f Cr\n",
           teamB->spent);

    printf("Remaining      : %.2f Cr\n",
           teamB->budget);

    printf("Players Bought : %d\n",
           teamB->playerCount);
}
