#include "bracket.h"

Queue *createBracket(TeamNode *TeamList)
{
    Queue *bracketQueue = createQueue();
    TeamNode *secondTeam;

    while(TeamList && TeamList->nextTeam)
    {
        secondTeam = TeamList->nextTeam;
        enQueue(bracketQueue, TeamList->T.teamName, secondTeam->T.teamName, TeamList->T.score, secondTeam->T.score);
        TeamList = TeamList->nextTeam->nextTeam;
    }

    return bracketQueue;
}

Queue *createBracketFromStack(StackNode **TeamList)
{
    Queue *bracketQueue = createQueue();

    while(!isEmptyS(*TeamList))
    {
        enQueue(bracketQueue, (*TeamList)->TeamName, (*TeamList)->next->TeamName, (*TeamList)->pointsTeam, (*TeamList)->next->pointsTeam);
        pop(TeamList);
        pop(TeamList);
    }

    return bracketQueue;    
}

void printBracketList(Queue *Q, char *fileName, int roundNR)
{
    Node *firstGame = Q->front;
    FILE *f = fopen(fileName, "at");
    if(f == NULL)
        exit(1);

    fprintf(f, "\n--- ROUND NO:%d\n", roundNR);

    while(firstGame)
    {
        fprintf(f, "%-33s-%33s\n", firstGame->TeamName1, firstGame->TeamName2);
        firstGame = firstGame->next;
    }

    fclose(f);
}

void deleteLosers(TeamNode **firstTeam, StackNode **S)
{
    while(!isEmptyS(*S))
    {
        removeTeamByName(firstTeam, (*S)->TeamName);
        pop(S);
    }
}