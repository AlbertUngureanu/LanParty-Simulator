#include "queue.h"

Queue *createQueue()
{
    Queue *q;
    q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL)
        return NULL;
        
    q->front = NULL;
    q->rear = NULL;

    return q;
}

int isEmpty(Queue *Q)
{
    return (Q->front == NULL);
}

void enQueue(Queue *Q, char *t1, char *t2, float p1, float p2)
{
    Node *newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->TeamName1 = strdup(t1);
    newNode->TeamName2 = strdup(t2);
    newNode->pointsTeam1 = p1;
    newNode->pointsTeam2 = p2;
    newNode->next = NULL;

    if(Q->rear == NULL)
        Q->rear = newNode;
    else
    {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
    
    if(isEmpty(Q))
        Q->front = newNode;
}

void deQueue(Queue *Q)
{
    Node *dNode;
    if(!isEmpty(Q))
    {
        dNode = Q->front;
        Q->front = Q->front->next;
        free(dNode);
    }
}