#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem
{
    char *TeamName1, *TeamName2; // nu e nevoie de toate informatiile unei echipe dpdv al unui meci;
    float pointsTeam1, pointsTeam2; // ci doar de nume si numar de puncte;
    struct Elem *next;
}Node;

typedef struct Q
{
    Node *front, *rear;
}Queue;

Queue* createQueue();

int isEmpty(Queue *);

void enQueue(Queue *, char *, char *, float , float );

void deQueue(Queue *);

#endif