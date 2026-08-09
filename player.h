#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    int id;
    char name[30];
    char role[20];

    int pruns,runs;
    int pwickets,wickets;
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

float calculatePerformance(struct Player *p);

void addPlayer();
struct Player *searchPlayer(int id);
void displayPlayer(struct Player *p);
void searchAndDisplay();
void updatePlayer();
void deletePlayer();
void displayAllPlayers();
void freeDatabase();
void play(struct Player *head,int totalOvers);

#endif
