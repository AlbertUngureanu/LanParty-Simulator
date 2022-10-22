#include "bst.h"

NodeBST *newNode(char *teamName, float points)
{
    NodeBST *N;

    N = (NodeBST*)malloc(sizeof(NodeBST));
    N->teamScore = points;
    N->teamName = strdup(teamName);
    N->left = N->right = NULL;

    return N;
}

NodeBST *insertBST(NodeBST *root, char *teamName, float teamScore)
{
    if(root == NULL)
        return newNode(teamName, teamScore);
    
    if( (teamScore < root->teamScore) || (teamScore == root->teamScore && strcmp(teamName, root->teamName) < 0))
        root->left = insertBST(root->left, teamName, teamScore);
    else 
        root->right = insertBST(root->right, teamName, teamScore);
    return root;
}

void freeSDR(NodeBST **root) 
{
    if(*root == NULL)
        return ;
    freeSDR(&(*root)->left);
    freeSDR(&(*root)->right);
    free(*root);
    (*root) = NULL;
}

void DRS(NodeBST *root, FILE *f)
{
    if(f==NULL)
        exit(1);

    if(root)
    {
        DRS(root->right, f);
        fprintf(f, "%-34s-  %3.2f\n", root->teamName, root->teamScore);
        DRS(root->left, f);
    }
}