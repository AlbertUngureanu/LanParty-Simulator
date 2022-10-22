#include "avl.h"

int max(int a, int b)
{
    return (a>b) ? a : b;
}

int nodeHeight(avlN *root)
{
    if(root == NULL)
        return -1;
    return root->height;
}

avlN *rightRotation(avlN *N)
{
    avlN *A = N->left;
    avlN *AUX = A->right;

    A->right = N;
    N->left = AUX;

    N->height = max(nodeHeight(N->left), nodeHeight(N->right)) + 1;
    A->height = max(nodeHeight(A->left), nodeHeight(A->right)) + 1;

    return A;
}

avlN *leftRotation(avlN *N)
{
    avlN *A = N->right;
    avlN *AUX = A->left;

    A->left = N;
    N->right = AUX;

    N->height = max(nodeHeight(N->left), nodeHeight(N->right)) + 1;
    A->height = max(nodeHeight(A->left), nodeHeight(A->right)) + 1;

    return A;
}

avlN *LRRotation(avlN *N)
{
    N->left = leftRotation(N->left);

    return rightRotation(N);
}

avlN *RLRotation(avlN *N)
{
    N->right = rightRotation(N->right);

    return leftRotation(N);
}

avlN *insertAVL(avlN *Node, char *teamName, float teamScore)
{

    if(Node == NULL)
    {
        Node = (avlN*)malloc(sizeof(avlN));
        Node->teamName = strdup(teamName);
        Node->teamScore = teamScore;
        Node->height = 0;
        Node->left = Node->right = NULL;
        return Node;
    }

    if((teamScore < Node->teamScore) || (teamScore == Node->teamScore && strcmp(teamName, Node->teamName) < 0))
        Node->left = insertAVL(Node->left, teamName, teamScore);
    else
        Node->right = insertAVL(Node->right, teamName, teamScore);

    Node->height = max(nodeHeight(Node->left), nodeHeight(Node->right)) + 1;

    int k = nodeHeight(Node->left) - nodeHeight(Node->right);

    if(k > 1 && ((teamScore < Node->left->teamScore) || (teamScore == Node->left->teamScore && strcmp(teamName, Node->left->teamName) < 0)) )
        return rightRotation(Node);
    
    if(k < -1 && ((teamScore < Node->right->teamScore) || (teamScore == Node->right->teamScore && strcmp(teamName, Node->right->teamName) < 0)) )
        return leftRotation(Node);

    if(k > 1 && ((teamScore > Node->left->teamScore) || (teamScore == Node->left->teamScore && strcmp(teamName, Node->left->teamName) > 0)) )
        return RLRotation(Node);

    if(k < -1 && ((teamScore > Node->right->teamScore) || (teamScore == Node->right->teamScore && strcmp(teamName, Node->right->teamName) > 0)) )
        return LRRotation(Node);

    return Node;     
}

void makeAVL(NodeBST *N, avlN **AVL)
{
    if(N == NULL)
        return;

    makeAVL(N->right, AVL);

    *AVL = insertAVL(*AVL, N->teamName, N->teamScore);

    makeAVL(N->left, AVL);
}

void printLvlN(avlN *root, int cLevel, int level, FILE *f)
{
    if(root == NULL)
        return ;

    printLvlN(root->right, cLevel+1, level, f);
    printLvlN(root->left, cLevel+1, level, f);

    if(level == cLevel)
        fprintf(f, "%s\n", root->teamName);
}

void printAVL(avlN *root)
{
    if(root == NULL)
        return ;
    
    printAVL(root->right);
    printf("%s\n", root->teamName);
    printAVL(root->left);
}

void freeAVL(avlN **root) 
{
    if(*root == NULL)
        return ;
    freeAVL(&(*root)->left);
    freeAVL(&(*root)->right);
    free(*root);
    (*root) = NULL;
}