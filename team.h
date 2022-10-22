#ifndef TEAM_H
#define TEAM_H

#include "player.h"


typedef struct Team
{
    char *teamName;
    int numberOfPlayers;
    float score;
    PlayerNode *firstPlayer;
}Team;

typedef struct TeamNode
{
    Team T;
    struct TeamNode *nextTeam;
}TeamNode;

void initTeam(Team *);

void initTeamNode(TeamNode **);

void printTeamsInfo(TeamNode *, char *);

void printTeamsName(TeamNode *, char *);

void readTeamInfo(Team *, FILE *);

void deepTeamCopy(Team *, Team *);

void insertTeamNodeAtBeginning(TeamNode  **, Team );

TeamNode *findWorstTeam(TeamNode *);

void removeTeamByAddr(TeamNode **, int );

void removeTeamByName(TeamNode **, char *);

#endif