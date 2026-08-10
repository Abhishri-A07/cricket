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


void addPlayer();
struct Player *searchPlayer(int id);
void displayPlayer(struct Player *p);
void searchAndDisplay();
void updatePlayer();
void deletePlayer();
void displayAllPlayers();
void freeDatabase();

/* Performance and sorting functions */
void performance(struct Player *head);
void ranking(struct Player *head);
void bestplayer(struct Player *head);
void sortplayer(struct Player *head);

/* Match playing function */
void play(struct Player *head, int totalOvers);

#endif
