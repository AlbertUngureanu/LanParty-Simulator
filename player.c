#include "player.h"

void initPlayer(Player *P)
{
    P->firstName = NULL;
    P->secondName = NULL;
    P->points = 0;
}

void initPlayerNode(PlayerNode **PN)
{
    (*PN) = malloc(sizeof(PlayerNode));
    initPlayer(&(*PN)->P);
    (*PN)->nextPlayer = NULL;
}

void readPlayerInfo(Player *P, FILE *f)
{
    char aux[50];
    fscanf(f, "%s", aux);
    P->secondName = strdup(aux);
    fscanf(f, "%s", aux);
    P->firstName = strdup(aux);  
    fscanf(f, "%d", &P->points); 
}

void deepPlayerCopy(Player *A, Player *B)
{
    A->firstName = strdup(B->firstName);
    A->secondName = strdup(B->secondName);
    A->points = B->points;
}

void insertPlayerNodeAtBeginning(PlayerNode **firstPlayer, Player P)
{
    PlayerNode *newPlayer;
    initPlayerNode(&newPlayer);
    deepPlayerCopy(&newPlayer->P, &P);
    if((*firstPlayer) == NULL)    ///nu am adaugat inca niciun jucator in echipa;
    {
        (*firstPlayer) = newPlayer;
    }
    else
    {
        newPlayer->nextPlayer = (*firstPlayer);
        (*firstPlayer) = newPlayer;
    }
}

void printPlayerList(PlayerNode *firstPlayer, FILE *f)
{
    while(firstPlayer)
    {
        fprintf(f, "%s %s => %d\n", firstPlayer->P.firstName, firstPlayer->P.secondName, firstPlayer->P.points);
        firstPlayer = firstPlayer->nextPlayer;
    }
}

void deletePlayerList(PlayerNode **first)
{
    PlayerNode *PD;

    while(*first)
    {
        PD = (*first);
        (*first) = (*first)->nextPlayer;
        free(PD);
    }
    (*first) = NULL;
}