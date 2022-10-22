#ifndef BRACKET_H
#define BRACKET_H

#include "queue.h"
#include "stack.h"
#include "team.h"

Queue *createBracket(TeamNode *);

Queue *createBracketFromStack(StackNode **);

void printBracketList(Queue *, char *, int);

void deleteLosers(TeamNode **, StackNode **);

#endif