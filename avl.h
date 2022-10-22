#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

typedef struct avlN
{
    char *teamName;
    float teamScore;
    int height;
    struct avlN *left, *right;
}avlN;

int nodeHeight(avlN *);

avlN *rightRotation(avlN *);

avlN *leftRotation(avlN *);

avlN *LRRotation(avlN *);

avlN *RLRotation(avlN *);

avlN *insertAVL(avlN *, char *, float);

void makeAVL(NodeBST *, avlN **);

void printLvlN(avlN *, int, int, FILE *);

void printAVL(avlN *);

void freeAVL(avlN **);

#endif