#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
}Player;

typedef struct PlayerNode
{
    Player P;
    struct PlayerNode *nextPlayer;
}PlayerNode;

void initPlayer(Player *);

void initPlayerNode(PlayerNode **);

void readPlayerInfo(Player *, FILE *);

void deepPlayerCopy(Player *, Player *);

void insertPlayerNodeAtBeginning(PlayerNode **, Player );

void printPlayerList(PlayerNode *, FILE *);

void deletePlayerList(PlayerNode **);

#endif