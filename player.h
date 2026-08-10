#ifndef PLAYER_H
#define PLAYER_H

/* ================= PLAYER STRUCTURE ================= */

typedef struct Player
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

} Player;


/* ================= PLAYER DATABASE ================= */

extern Player *head;
extern Player *tail;

void addPlayer(void);
Player *searchPlayer(int id);
void displayPlayer(Player *p);
void searchAndDisplay(void);
void updatePlayer(void);
void deletePlayer(void);
void displayAllPlayers(void);
void freeDatabase(void);


/* ================= PERFORMANCE / RANKING ================= */

float calculatePerformance(Player *p);
void performance(Player *head);
void ranking(Player *head);
void bestplayer(Player *head);
void sortplayer(Player *head);


/* ================= SQUAD SELECTION ================= */

#define MAX_SQUAD 15

void getSquad(Player squad[], int *n);
void getLineup(Player squad[], int n, Player xi[]);
void battingOrder(Player xi[]);
void selectCaptain(Player xi[]);
void selectKeeper(Player xi[]);
void bowlingPlan(Player xi[]);
void displayLineup(Player xi[]);


/* ================= TEAM MANAGEMENT ================= */

#define MAX_TEAM_PLAYERS 22

typedef struct
{
    char name[20];
    Player players[MAX_TEAM_PLAYERS];
    int count;

} TeamManagement;

void addTeamPlayer(TeamManagement *team, Player p);
void removeTeamPlayer(TeamManagement *team, int id);
void replaceTeamPlayer(TeamManagement *team, int oldId, Player newPlayer);
void displayTeam(TeamManagement *team);
void checkSquad(TeamManagement *team);


/* ================= AUCTION ================= */

#define INITIAL_BUDGET 100.0f

typedef struct
{
    char name[20];
    float budget;
    float spent;
    int playerCount;

} AuctionTeam;

typedef struct
{
    int playerID;
    char playerName[30];
    char teamName[20];
    float soldPrice;

} AuctionResult;

void initializeTeam(AuctionTeam *team, const char name[]);
void displayAuctionPlayer(Player *player);
void auctionPlayer(Player *player,
                   AuctionTeam *teamA,
                   AuctionTeam *teamB,
                   AuctionResult *result);
void displayFinalReport(AuctionResult results[],
                        int count,
                        AuctionTeam *teamA,
                        AuctionTeam *teamB);


/* ================= BALL-BY-BALL SCORE ================= */

#define MAX_BALLS 200

typedef struct
{
    int no;
    int runs;
    int wicket;
    char result[15];

} Ball;

typedef struct
{
    Ball b[MAX_BALLS];
    int front;
    int rear;

} Queue;

typedef struct
{
    int runs;
    int wickets;
    int balls;
    int target;

    char batsman[30];
    char bowler[30];

    int bruns;
    int bballs;
    int fours;
    int sixes;

    int bwickets;
    int bruns_conceded;
    int bballs_bowled;

} Score;

void initializeQueue(Queue *q);
void enqueue(Queue *q, int no, int runs, int wicket, const char result[]);
void displayQueue(Queue *q);

void scoreboard(Score *s);
void battingCard(Score *s);
void bowlingCard(Score *s);


/* ================= MATCH CONTROLLER ================= */

#define MAX_OVERS 20
#define MAX_WICKETS 10

#define NOT_STARTED 0
#define TOSS_DONE 1
#define INNINGS_STARTED 2
#define INNINGS_COMPLETED 3
#define MATCH_COMPLETED 4

typedef struct
{
    int currentInnings;
    int currentOver;
    int currentBall;

    int totalBalls;
    int wickets;
    int runs;

    int maxOvers;
    int maxBalls;

    int target;

    int battingTeam;
    int bowlingTeam;

    int state;

} MatchController;

void initializeMatch(MatchController *m);
void toss(MatchController *m);
void startInnings(MatchController *m, int innings);
void addBall(MatchController *m);
void addRuns(MatchController *m, int runs);
void addWicket(MatchController *m);
int checkInningsEnd(MatchController *m);
void displayStatus(MatchController *m);
void endInnings(MatchController *m);
void startSecondInnings(MatchController *m);


/* ================= ACTUAL MATCH ================= */

void batting(Player *striker, int runs);
void bowling(Player *bowler, int runs);
void play(Player *team, int totalOvers);


/* ================= SORTING ================= */

#endif
