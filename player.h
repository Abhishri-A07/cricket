#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    int id;
    char name[30];
    char role[20];

    int pruns;
    int runs;

    int pwickets;
    int wickets;

    float strikeRate;
    float economy;
    float performance;
    float basePrice;

    int ballsfaced;
    int isout;

    int ballsBowled;
    int runsgiven;

    struct Player *prev;
    struct Player *next;
};

extern struct Player *head;
extern struct Player *tail;

/* Player Database */
void addPlayer();
struct Player *searchPlayer(int id);
void displayPlayer(struct Player *p);
void searchAndDisplay();
void updatePlayer();
void deletePlayer();
void displayAllPlayers();
void freeDatabase();

/* Performance and Ranking */
void performance(struct Player *head);
void ranking(struct Player *head);
void bestplayer(struct Player *head);
void sortplayer(struct Player *head);

/* Match */
void batting(struct Player *striker, int runs);
void bowling(struct Player *bowler, int runs);
void play(struct Player *head, int totalOvers);

/* Auction */
typedef struct
{
    char name[20];
    float budget;
    float spent;
    int playerCount;
} Team;

typedef struct
{
    int playerID;
    char playerName[30];
    char teamName[20];
    float soldPrice;
} AuctionResult;

#define INITIAL_BUDGET 100.0f

void initializeTeam(Team *team, const char name[]);
void displayAuctionPlayer(struct Player *player);
void auctionPlayer(struct Player *player,
                   Team *teamA,
                   Team *teamB,
                   AuctionResult *result);
void displayFinalReport(AuctionResult results[],
                        int count,
                        Team *teamA,
                        Team *teamB);

#endif
