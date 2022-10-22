#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NodeBST
{
    char *teamName;
    float teamScore;
    struct NodeBST *left, *right;
}NodeBST;

NodeBST *newNode(char *, float);

NodeBST *insertBST(NodeBST *, char *, float);

void freeSDR(NodeBST **);

void DRS(NodeBST *, FILE *);

#endif