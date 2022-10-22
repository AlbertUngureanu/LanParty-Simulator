#include "player.h"
#include "team.h"
#include "bracket.h"
#include "stack.h"
#include "bst.h"
#include "avl.h"

int main(int argc, char *argv[])
{
    int numberOfTeams, C[5];
    FILE *f;
    TeamNode *firstTeam = NULL, *auxTeam = NULL;
    Team T;
    NodeBST *Top8 = NULL;
    avlN *AVLTop8 = NULL;
    
    if((f = fopen(argv[1], "rt"))==NULL)
    {
        printf("eroare deschidere fisier.");
        return 1;
    }
    fscanf(f, "%d %d %d %d %d", &C[0], &C[1], &C[2], &C[3], &C[4]);
    fclose(f);

    if(C[0])
    {
        if((f = fopen(argv[2], "rt"))==NULL)
        {
            printf("eroare deschidere fisier.");
            return 1;
        }
        fscanf(f, "%d", &numberOfTeams);
        for(int i = 0; i < numberOfTeams; i++)
        {
            readTeamInfo(&T,f);
            insertTeamNodeAtBeginning(&firstTeam, T);
        }
        fclose(f);

        printTeamsName(firstTeam, argv[3]);
    }

    if(C[1])
    {
        TeamNode *worstTeam = findWorstTeam(firstTeam);

        while (numberOfTeams & (numberOfTeams-1)) // cat timp nRem nu e putere a lui doi;
        {
            if((worstTeam != firstTeam) || (worstTeam == firstTeam && firstTeam->nextTeam->T.score < firstTeam->T.score))
            {
                removeTeamByAddr(&worstTeam, 0);
            }
            else
            {
                removeTeamByAddr(&firstTeam, 1);
            }
            numberOfTeams--;
            
            worstTeam = findWorstTeam(firstTeam);
        }

        printTeamsName(firstTeam, argv[3]);
    }
    
    if(C[2])
    {
        int roundNumber = 1;
        Queue *Q = createBracket(firstTeam);
        StackNode *winners = NULL, *losers = NULL;

        printBracketList(Q, argv[3], roundNumber);
        createStacks(Q, &winners, &losers);
        printStackValues(winners, argv[3], roundNumber);
        deleteLosers(&firstTeam, &losers);
        numberOfTeams /= 2;
        roundNumber++;

        while(numberOfTeams!=1)
        {
            if(numberOfTeams == 8 && C[3])
            {
                StackNode *curr = winners;
                while(curr)
                {
                    Top8 = insertBST(Top8, curr->TeamName, curr->pointsTeam);
                    curr = curr->next;
                }
            }

            if(numberOfTeams == 8 && C[4])
            {
                makeAVL(Top8, &AVLTop8);
            }

            Q = createBracketFromStack(&winners); //sterg si stiva in acelasi timp;
            printBracketList(Q, argv[3], roundNumber);

            createStacks(Q, &winners, &losers);

            printStackValues(winners, argv[3], roundNumber);

            deleteLosers(&firstTeam, &losers); //sterg si stiva in acelasi timp;

            numberOfTeams /= 2;
            roundNumber++;
        }
    }

    if(C[3])
    {
        f = fopen(argv[3], "at");
        if(f==NULL)
            exit(1);
        
        fprintf(f, "\nTOP 8 TEAMS:\n");

        DRS(Top8, f);

        fclose(f);

        freeSDR(&Top8);
    }

    if(C[4])
    {
        f = fopen(argv[3], "at");

        if(f==NULL)
            exit(1);
        
        fprintf(f, "\nTHE LEVEL 2 TEAMS ARE:\n");

        printLvlN(AVLTop8, 0, 2, f);

        fclose(f);

        freeAVL(&AVLTop8);
    }

    while(firstTeam)
    {
        auxTeam = firstTeam;
        firstTeam = firstTeam->nextTeam;
        deletePlayerList(&auxTeam->T.firstPlayer);
        free(auxTeam);
    }
    firstTeam = NULL;
    
    return 0;
}