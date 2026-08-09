#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "player.h"
void batting(struct Player *striker,int runs)
{
  striker->ballsfaced++;
  if(runs==0)
  {
    striker->isout=1;
    printf("\n%s is out",striker->name);
  }
  else
  {
    striker->runs+=runs;
  }
}

void bowling(struct Player *bowler,int runs)
{
  bowler->ballsBowled++;
  bowler->runsgiven+=runs;
  if(runs==0)
  {
   bowler->wickets+=1;
  }
}

void play(struct Player *head,int totalovers)
{
 struct Player *striker=NULL,*nonstriker=NULL,*bowler=NULL,*temp=NULL;
 int runs,ball,over;
 temp=head;
 while(temp!=NULL)
 {
  if(strcmp(temp->role,"BATSMAN")==0 || strcmp(temp->role,"ALLROUNDER")==0)
  {
   if(striker==NULL)
     striker=temp;
   else if(nonstriker==NULL)
   {
     nonstriker=temp;
     break;
   }
   }
   temp=temp->next;
  }
 temp=head;
 while(temp!=NULL)
 {
  if(strcmp(temp->role,"BOWLER")==0 || strcmp(temp->role,"ALLROUNDER")==0)
  {
   bowler=temp;
   break;
  }
  temp=temp->next;
 }
 if(striker==NULL || nonstriker==NULL || bowler==NULL)
 {
  printf("\nNot enough players");
  return;
 }

 for(over=1;over<=totalovers;over++)
 {
  printf("Over %d\nStriker %s\nNon striker %s\nBowler %s",over,striker->name,nonstriker->name,bowler->name);
  printf("\n");
  for(ball=1;ball<=6;ball++)
  {
   printf("\nBall %d\nStriker %s",ball,striker->name);
   printf("\nEnter the number of runs (0-Wicket)");
   scanf("%d",&runs);
   batting(striker,runs);
   bowling(bowler,runs);
   if(runs==0)
   {
    temp=head;
    while(temp!=NULL)
    {
     if((strcmp(temp->role,"BATSMAN")==0 || strcmp(temp->role,"ALLROUNDER")==0) && temp->isout=0 && temp!=striker && temp!=nonstriker))
     {
      striker=temp;
      break;
      }
      temp=temp->next;
     }
     printf("\nNew batsman %s",striker->name);
    }
   else if(runs%2==1)
   {
    temp=striker;
    striker=nonstriker;
    nonstriker=temp;
    printf("\nStrike changed");
   }
  }
    temp=striker;
   striker=nonstriker;
   nonstriker=temp;
   printf("\nEnd of over %d",over);
 }
}




