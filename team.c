#include "team.h"

void initTeam(Team *T)
{
    T->teamName = NULL;
    T->numberOfPlayers = 0;
    T->score = 0;
    initPlayerNode(&T->firstPlayer);
}

void initTeamNode(TeamNode **TN)
{
    (*TN) = malloc(sizeof(TeamNode));
    initTeam(&(*TN)->T);
    (*TN)->nextTeam = NULL;
}

void printTeamsInfo(TeamNode *firstTeam, char *fileName)
{
    FILE *f;
    if((f = fopen(fileName, "wt")) ==NULL)
    {
        printf("eroare deschidere fisier.");
        return ;
    }
    for(TeamNode *i = firstTeam; i ; i = i->nextTeam)
    {
        fprintf(f, "%s <-> %f\n", i->T.teamName, i->T.score);
        printPlayerList(i->T.firstPlayer, f);
        fprintf(f,"\n");
    }
    fclose(f);
}

void printTeamsName(TeamNode *firstTeam, char *fileName)
{
    FILE *f;
    if((f = fopen(fileName, "wt")) == NULL)
    {
        printf("eroare deschidere fisier.");
        return ;
    }
    for(TeamNode *i = firstTeam; i; i = i->nextTeam)
    {
        fprintf(f, "%s\n", i->T.teamName);
    }
    fclose(f);    
}

void readTeamInfo(Team *T, FILE *f)
{
    char aux[50];
    Player P;
    initPlayer(&P);
    fscanf(f, "%d", &T->numberOfPlayers);

    fgets(aux, 50, f);
    aux[strlen(aux)-1] = '\0'; // elimin \n din nume;
    if(aux[strlen(aux)-1] ==' ') // elimin un spatiu care mai apare random in unele teste;
        aux[strlen(aux)-1] ='\0';
    T->teamName = strdup(aux+1);  // sar peste spatiul de la inceput;

    T->firstPlayer = NULL;
    T->score = 0;
    for(int i=0; i < T->numberOfPlayers; i++)
    {
        readPlayerInfo(&P, f);
        insertPlayerNodeAtBeginning(&T->firstPlayer, P);
        T->score += P.points;
    }

    T->score /= T->numberOfPlayers;
}

void deepTeamCopy(Team *A, Team *B)
{
    A->teamName = strdup(B->teamName);
    A->firstPlayer = B->firstPlayer;
    A->numberOfPlayers = B->numberOfPlayers;
    A->score = B->score;
}

void insertTeamNodeAtBeginning(TeamNode  **firstTeam, Team T)
{
    TeamNode *newTeam;
    initTeamNode(&newTeam);
    deepTeamCopy(&newTeam->T, &T);
    if((*firstTeam) == NULL)    ///nu am adaugat inca nicio echipa;
    {
        (*firstTeam) = newTeam;
    }
    else
    {
        newTeam->nextTeam = (*firstTeam);
        (*firstTeam) = newTeam;
    }
}

TeamNode *findWorstTeam(TeamNode *firstTeam) 
{
    float res = firstTeam->T.score;
    TeamNode *removedTeam = firstTeam;

    for(firstTeam; firstTeam && firstTeam->nextTeam; firstTeam = firstTeam->nextTeam)
        if(res > firstTeam->nextTeam->T.score)
        {
            res = firstTeam->nextTeam->T.score; 
            removedTeam = firstTeam; // retin adresa nodului dinaintea celui pe care il voi elimina;
        }

    return removedTeam;
}

void removeTeamByAddr(TeamNode **toDelete, int K) // k==1 => sterg primul nod;
{
    if(K)
    {
        TeamNode *D = *toDelete;
        (*toDelete) = D->nextTeam;

        deletePlayerList(&D->T.firstPlayer);
        free(D);
    }
    else
    {
        TeamNode *D = (*toDelete)->nextTeam;
        (*toDelete)->nextTeam = D->nextTeam;

        deletePlayerList(&D->T.firstPlayer);
        free(D);
    }
}

void removeTeamByName(TeamNode **firstTeam, char *teamName)
{
    TeamNode *toDelete, *currTeam = (*firstTeam);

    if(strcmp((*firstTeam)->T.teamName, teamName) == 0)
    {
        toDelete = (*firstTeam);
        (*firstTeam) = (*firstTeam)->nextTeam;

        deletePlayerList(&toDelete->T.firstPlayer);
        free(toDelete);
        return ;
    }

    while(currTeam && currTeam->nextTeam)
    {
        if(strcmp(currTeam->nextTeam->T.teamName, teamName) == 0)
        {
            toDelete = currTeam->nextTeam;
            currTeam->nextTeam = currTeam->nextTeam->nextTeam;
            
            deletePlayerList(&toDelete->T.firstPlayer);
            free(toDelete);
        }

        currTeam = currTeam->nextTeam;
    }
}