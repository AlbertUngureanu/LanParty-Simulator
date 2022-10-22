#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct ElemS
{
    char *TeamName;
    float pointsTeam;
    struct ElemS *next;
}StackNode;

void push(StackNode **, char *, float );

int isEmptyS(StackNode *);

void pop(StackNode **);

void deleteStack(StackNode **);

void createStacks(Queue *, StackNode **, StackNode **);

void printStackValues(StackNode *, char *, int);

#endif