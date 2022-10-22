#include "stack.h"

void push(StackNode **stackNode, char *teamName, float teamPoints)
{
    StackNode *newNode;
    newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->TeamName = strdup(teamName);
    newNode->pointsTeam = teamPoints;
    newNode->next = (*stackNode);
    (*stackNode) = newNode;
}

int isEmptyS(StackNode *stackNode)
{
    return (stackNode == NULL);
}

void pop(StackNode **top)
{
    StackNode *dNode;

    dNode = (*top);
    (*top) = (*top)->next;
    free(dNode);
}

void deleteStack(StackNode **Node)
{
    StackNode *toDel;
    
    /*while((*Node))
    {
        toDel = (*Node);
        (*Node) = (*Node)->next;
        free(toDel);
    }*/

    (*Node) = NULL;
}

void createStacks(Queue *Q, StackNode **winners, StackNode **losers)
{
    (*winners) = (*losers) = NULL;

    while(!isEmpty(Q))
    {
        if(Q->front->pointsTeam1 > Q->front->pointsTeam2)
        {
            push(winners, Q->front->TeamName1, Q->front->pointsTeam1 + 1);
            push(losers, Q->front->TeamName2, Q->front->pointsTeam2);
        }
        else if(Q->front->pointsTeam1 == Q->front->pointsTeam2)
            {
                push(winners, Q->front->TeamName2, Q->front->pointsTeam2 + 1);
                push(losers, Q->front->TeamName1, Q->front->pointsTeam1);
            }
            else
                {
                    push(losers, Q->front->TeamName1, Q->front->pointsTeam1);
                    push(winners, Q->front->TeamName2, Q->front->pointsTeam2 + 1);            
                }
        deQueue(Q);
    }
}

void printStackValues(StackNode *Elem, char *fileName, int roundNR)
{
    FILE *f = fopen(fileName, "at");

    if(f == NULL)
        exit(1);

    fprintf(f, "\nWINNERS OF ROUND NO:%d\n", roundNR);

    while(Elem)
    {
        fprintf(f, "%-34s-  %3.2f\n", Elem->TeamName, Elem->pointsTeam);

        Elem = Elem->next;
    }

    fclose(f);
}