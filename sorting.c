#include<stdio.h>
#include "player.h"
#include<stdlib.h>
#include<string.h>
void performance(struct Player *head)
{
    float total;
    struct Player *temp=head;
    while(temp!=NULL)
    {
        total=(temp->runs*0.4)+(temp->wickets*10*0.3)+(temp->strikerate*0.2)+((10-temp->economy)*0.1);
        temp->performance=total;
        temp=temp->next;
        total=0;
    }
}
void ranking(struct Player *head)
{
    struct Player *temp=head;
    printf("\n:::::::::::::: PLAYERS RANK DETAILS ::::::::::::::\n");
    printf("PLAYER NAME \tSCORE")
    while(temp!=NULL)
    {
        printf("%s\t %.2f",temp->name,temp->performance);
        temp=temp->next;
        printf("\n");
    }
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}
void bestplayer(struct Player *head)
{
    struct Player *temp=head;
    struct Player *batsman=NULL;
    struct Player *bowler=NULL;
    struct Player *allrounder=NULL;
    while(temp!=NULL)
    {  
        
        if(strcmp(temp->role,"batsman")==0)
        {
            if(temp->runs>batsman->runs)
            {
                batsman=temp;
            }
        }
        if(strcmp(temp->role,"bowler")==0)
        {
            if(temp->wickets>bowler->wickets)
            {
                bowler=temp;
            }
        }
        if(strcmp(temp->role,"allrounder")==0)
        {
            if(temp->performance>allrounder->performance)
            {
                allrounder=temp;
            }
        }
        temp=temp->next;
    }
}
void sortplayer(struct Player *head)
{
    struct Player *i, *j;
    for(i=head;i!=NULL;i=i->next)
    {
        for(j =i->next;j!=NULL;j=j->next)
        {
            if(j->performance>i->performance)
            {
                float tempPerf = i->performance;
                i->performance = j->performance;
                j->performance = tempPerf;
                int tempRuns = i->runs;
                i->runs = j->runs;
                j->runs = tempRuns;
                int tempWickets = i->wickets;
                i->wickets = j->wickets;
                j->wickets = tempWickets;
                float tempSR = i->strikerate;
                i->strikerate = j->strikerate;
                j->strikerate = tempSR;
                float tempEco = i->economy;
                i->economy = j->economy;
                j->economy = tempEco;
                char tempName[50], tempRole[20];
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
                strcpy(tempRole, i->role);
                strcpy(i->role, j->role);
                strcpy(j->role, tempRole);
            }
        }
    }
}
