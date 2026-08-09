#include <stdio.h>
#include <string.h>

#define MAX 22

struct Player
{
    int id;
    char name[30];
};

struct Team
{
    char name[20];
    struct Player players[MAX];
    int count;
};

void addPlayer(struct Team *team, struct Player p)
{
    if (team->count < MAX)
    {
        team->players[team->count] = p;
        team->count++;

        printf("%s added to %s\n", p.name, team->name);
    }
    else
    {
        printf("Team is full!\n");
    }
}

void removePlayer(struct Team *team, int id)
{
    int i, j;

    for (i = 0; i < team->count; i++)
    {
        if (team->players[i].id == id)
        {
            for (j = i; j < team->count - 1; j++)
            {
                team->players[j] = team->players[j + 1];
            }

            team->count--;

            printf("Player removed from %s\n", team->name);
            return;
        }
    }

    printf("Player not found!\n");
}

void replacePlayer(struct Team *team, int oldId, struct Player newPlayer)
{
    int i;

    for (i = 0; i < team->count; i++)
    {
        if (team->players[i].id == oldId)
        {
            team->players[i] = newPlayer;

            printf("Player replaced in %s\n", team->name);
            return;
        }
    }

    printf("Player not found!\n");
}

void displayTeam(struct Team *team)
{
    int i;

    printf("\n-------------------------\n");
    printf("%s\n", team->name);
    printf("-------------------------\n");

    for (i = 0; i < team->count; i++)
    {
        printf("%d. %s\n",
               team->players[i].id,
               team->players[i].name);
    }

    printf("Total Players: %d\n", team->count);
}

void checkSquad(struct Team *team)
{
    if (team->count >= 11)
    {
        printf("%s has the required squad size.\n", team->name);
    }
    else
    {
        printf("%s needs %d more players.\n",
               team->name,
               11 - team->count);
    }
}

int main()
{
    struct Team teamA = {"Team A", {}, 0};
    struct Team teamB = {"Team B", {}, 0};

    struct Player players[22] =
    {
        {1, "Virat"},
        {2, "Rohit"},
        {3, "Dhoni"},
        {4, "Rahul"},
        {5, "Jadeja"},
        {6, "Bumrah"},
        {7, "Gill"},
        {8, "Hardik"},
        {9, "Pant"},
        {10, "Shami"},
        {11, "Surya"},
        {12, "Siraj"},
        {13, "Ashwin"},
        {14, "Ishan"},
        {15, "Rinku"},
        {16, "Kuldeep"},
        {17, "Arshdeep"},
        {18, "Axar"},
        {19, "Samson"},
        {20, "Washington"},
        {21, "Chahal"},
        {22, "Shreyas"}
    };

    /* Adding players to Team A */
    addPlayer(&teamA, players[0]);
    addPlayer(&teamA, players[2]);
    addPlayer(&teamA, players[4]);
    addPlayer(&teamA, players[5]);
    addPlayer(&teamA, players[6]);
    addPlayer(&teamA, players[7]);
    addPlayer(&teamA, players[9]);
    addPlayer(&teamA, players[12]);
    addPlayer(&teamA, players[15]);
    addPlayer(&teamA, players[17]);
    addPlayer(&teamA, players[20]);

    /* Adding players to Team B */
    addPlayer(&teamB, players[1]);
    addPlayer(&teamB, players[3]);
    addPlayer(&teamB, players[8]);
    addPlayer(&teamB, players[10]);
    addPlayer(&teamB, players[11]);
    addPlayer(&teamB, players[13]);
    addPlayer(&teamB, players[14]);
    addPlayer(&teamB, players[16]);
    addPlayer(&teamB, players[18]);
    addPlayer(&teamB, players[19]);
    addPlayer(&teamB, players[21]);

    printf("\n\nTEAM SQUADS\n");
    displayTeam(&teamA);
    displayTeam(&teamB);

    printf("\n\nSQUAD SIZE CHECK\n");
    checkSquad(&teamA);
    checkSquad(&teamB);

    printf("\n\nRemoving player from Team A...\n");
    removePlayer(&teamA, 5);

    printf("\nReplacing player in Team B...\n");
    replacePlayer(&teamB, 13, players[14]);

    printf("\n\nUPDATED TEAM SQUADS\n");
    displayTeam(&teamA);
    displayTeam(&teamB);

    return 0;
}
