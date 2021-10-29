#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct griddy// struct defining the structure of the gameboard
{
    int gridValue;// stores point value
    int gridNum;// stores cell number
    int deadCell;// stores whether cell has been visited or not
    struct griddy *up;
    struct griddy *down;
    struct griddy *left;
    struct griddy *right;
    struct griddy *upDiagLeft;
    struct griddy *upDiagRight;
    struct griddy *downDiagLeft;
    struct griddy *downDiagRight;
};

struct totallyAHuman// struct defining game players
{
    int points;
    char playerSymbol;
    struct griddy *currPos;
};

void createMap(struct griddy *tempPoint)// sets point values to each grid struct
{
    for(int i = 0; i <36; i++)
    {
        if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 11 || i == 12 || i == 17 || i == 18 || i == 23 || i == 24 || i == 29 || i == 30 || i == 31 || i == 32 || i == 33 || i == 34 || i == 35)
            tempPoint[i].gridValue = 1;
        else if( i == 7 || i == 8 || i == 9 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25 || i == 26 || i == 27 || i == 28)
            tempPoint[i].gridValue = 2;
        else
            tempPoint[i].gridValue = 3;
        tempPoint[i].gridNum = i;
        tempPoint[i].deadCell = 0;
    }
}

void setDirectionalPointers(struct griddy *tempPoint)// links each grid struct to the surrounding cells
{
    for (int i = 0; i < 36; i++)
    {
        if(i % 6 == 0)// if cell is leftmost column
        {
            tempPoint[i].upDiagLeft = NULL;
            tempPoint[i].left = NULL;
            tempPoint[i].downDiagLeft = NULL;
            tempPoint[i].right = &tempPoint[i+1];

            if(i - 6 < 0)// if cell is first row
            {
                tempPoint[i].up = NULL;
                tempPoint[i].upDiagRight = NULL;
            }
            else
            {
                tempPoint[i].up = &tempPoint[i - 6];
                tempPoint[i].upDiagRight = &tempPoint[i - 5];
            }

            if(i + 6 > 35) // if cell is last row
            {
                tempPoint[i].down = NULL;
                tempPoint[i].downDiagRight = NULL;
            }
            else
            {
                tempPoint[i].down = &tempPoint[i + 6];
                tempPoint[i].downDiagRight = &tempPoint[i + 7];
            }
            
        }

        else if(i % 6 == 5)// if cell is rightmost column
        {
            tempPoint[i].upDiagRight = NULL;
            tempPoint[i].right = NULL;
            tempPoint[i].downDiagRight = NULL;
            tempPoint[i].left = &tempPoint[i-1];

            if(i - 6 < 0) // if cell is first row
            {
                tempPoint[i].up = NULL;
                tempPoint[i].upDiagLeft = NULL;
            }
            else
            {
                tempPoint[i].up = &tempPoint[i - 6];
                tempPoint[i].upDiagLeft = &tempPoint[i - 7];
            }

            if(i + 6 > 35)// if cell is last row
            {
                tempPoint[i].down = NULL;
                tempPoint[i].downDiagLeft = NULL;
            }
            else
            {
                tempPoint[i].down = &tempPoint[i + 6];
                tempPoint[i].downDiagLeft = &tempPoint[i + 5];
            }
            
        }

        else if (i < 6) // if cell is first row
        {
            tempPoint[i].up = NULL;
            tempPoint[i].upDiagLeft = NULL;
            tempPoint[i].upDiagRight = NULL;
            tempPoint[i].left = &tempPoint[i - 1];
            tempPoint[i].right = &tempPoint[i + 1];
            tempPoint[i].down = &tempPoint[i + 6];
            tempPoint[i].downDiagLeft = &tempPoint[i + 5];
            tempPoint[i].downDiagRight = &tempPoint[i + 7];
        }

        else if (i > 30)// if cell is last row
        {
            tempPoint[i].up = &tempPoint[i - 6];
            tempPoint[i].upDiagLeft = &tempPoint[i - 7];;
            tempPoint[i].upDiagRight = &tempPoint[i - 5];;
            tempPoint[i].left = &tempPoint[i - 1];
            tempPoint[i].right = &tempPoint[i + 1];
            tempPoint[i].down = NULL;
            tempPoint[i].downDiagLeft = NULL;
            tempPoint[i].downDiagRight = NULL;
        }

        else
        {
            tempPoint[i].up = &tempPoint[i - 6];
            tempPoint[i].upDiagLeft = &tempPoint[i - 7];;
            tempPoint[i].upDiagRight = &tempPoint[i - 5];;
            tempPoint[i].left = &tempPoint[i - 1];
            tempPoint[i].right = &tempPoint[i + 1];
            tempPoint[i].down = &tempPoint[i + 6];
            tempPoint[i].downDiagLeft = &tempPoint[i + 5];
            tempPoint[i].downDiagRight = &tempPoint[i + 7];
        }
        

    }

}

void printMap(struct griddy *tempPoint, struct totallyAHuman *player, struct totallyAHuman *AI)// prints the game board displaying current and taken cells
{
    printf("   1 2 3 4 5 6");// grid scale horizontal
    for (int i = 0; i < 36; i++)
    {
        if(i%6==0)
            printf("\n%d  ", (i/6)+1);// grid scale vertical
        
        if(tempPoint[i].deadCell !=0)// if cell already visited
        {
            if(player->currPos->gridNum == i)// prints human player position on map
            {
                printf("%c ", player->playerSymbol);
            }
            else if (AI->currPos->gridNum == i)// prints AI position on map
            {
                printf("%c ", AI->playerSymbol);
            }
            else
                printf(". ");// prints . if cell visited
            
        }
        else
            printf("%d ", tempPoint[i].gridValue);// prints point grid

    }
    
}

void playerInit(struct totallyAHuman *player, struct totallyAHuman *AI, struct griddy *tempPoint)// Initializes player and AI starting positions, symbols and points
{
    //player = {0, 'P', 4};
    player->currPos = &tempPoint[4]; player->playerSymbol = 'P'; player->points = 0;// init human
    AI->currPos = &tempPoint[31]; AI->playerSymbol = 'A'; AI->points = 0;// init AI

    player->currPos->deadCell = 1;// set start position
    AI->currPos->deadCell = 1;// set start position
}
void moveIt(struct griddy* destinationGridBox, struct totallyAHuman* eitherPlayer, int *accruedPoints)// moves passed player to new cell
{
    eitherPlayer->currPos = destinationGridBox;// update position
    eitherPlayer->currPos->deadCell = 1;// set position to visited
    eitherPlayer->points = *accruedPoints;// update points
    accruedPoints = 0;
}

struct griddy* pathFinder(struct totallyAHuman AI, int *pointAccrual)// helps AI determine best cell to move to
{
    struct griddy *bestPath;// pointer to determined best grid cell
    struct totallyAHuman AIRefCopy = AI;// copy of passed struct to reset position after each direction length run
    int maxPoints = 0; int points = 0;// stores max points encoutered over all directions and per direction respectively
    while (AI.currPos->up != NULL)// loops till the edge of direction
    {
        if(AI.currPos->up->deadCell != 0)// if visited
        {
            break;
        }
        points = AI.currPos->up->gridValue;// stores points
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->up;// updates best path if higher value grid cell found
        }
        AI.currPos = AI.currPos->up;// jumps to next cell in direction
    }
    points = 0; AI = AIRefCopy;// reset points and AI position
    ///////
    while (AI.currPos->upDiagLeft != NULL)
    {
        if(AI.currPos->upDiagLeft->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->upDiagLeft->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->upDiagLeft;
        }
        AI.currPos = AI.currPos->upDiagLeft;
    }
    points = 0;AI = AIRefCopy;
    ///////
    while (AI.currPos->upDiagRight != NULL)
    {
        if(AI.currPos->upDiagRight->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->upDiagRight->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->upDiagRight;
        }
        AI.currPos = AI.currPos->upDiagRight;
    }
    points = 0;AI = AIRefCopy;
    while (AI.currPos->down != NULL)
    {
        if(AI.currPos->down->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->down->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->down;
        }
        AI.currPos = AI.currPos->down;
    }
    points = 0;AI = AIRefCopy;
    while (AI.currPos->downDiagLeft != NULL)
    {
        if(AI.currPos->downDiagLeft->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->downDiagLeft->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->downDiagLeft;
        }
        AI.currPos = AI.currPos->downDiagLeft;
    }
    points = 0;AI = AIRefCopy;
    while (AI.currPos->downDiagRight != NULL)
    {
        if(AI.currPos->downDiagRight->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->downDiagRight->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->downDiagRight;
        }
        AI.currPos = AI.currPos->downDiagRight;
    }
    points = 0;AI = AIRefCopy;
    while (AI.currPos->left != NULL)
    {
        if(AI.currPos->left->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->left->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->left;
        }
        AI.currPos = AI.currPos->left;
    }
    points = 0;AI = AIRefCopy;
    while (AI.currPos->right != NULL)
    {
        if(AI.currPos->right->deadCell != 0)
        {
            break;
        }
        points = AI.currPos->right->gridValue;
        if(points > maxPoints)
        {
            maxPoints = points;
            bestPath = AI.currPos->right;
        }
        AI.currPos = AI.currPos->right;
    }
    points = 0;
    *pointAccrual += bestPath->gridValue;// stores points of AI as per best path
    //printf("%d", *pointAccrual);
    return bestPath;// return destermined path
}

int humanCheckIsValidMove(struct totallyAHuman player, int *accruedPoints)// accepts player move, checks if move legal or not
{
    char playerInput[15]; int spaces; int count = 0;
    printf("\nInput player move: ");
    scanf("%s %d", playerInput, &spaces);

    if(strcmp(playerInput, "DOWN") == 0)// compares for each direction
    {   
        while(player.currPos->down != NULL && count < spaces)// iterates each direction to specified number of spaces
        {
            if(player.currPos->down->deadCell != 0)// if visited cell encountered, return error indication
            {
                return -1;
            }
            player.currPos = player.currPos->down;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "UP") == 0)
    {   
        while(player.currPos->up != NULL && count < spaces)
        {
            if(player.currPos->up->deadCell != 0)
            {
                return -1;
            }
            player.currPos = player.currPos->up;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "LEFT") == 0)
    {   
        while(player.currPos->left != NULL && count < spaces)
        {
            if(player.currPos->left->deadCell != 0)
            {
                return -1;
            }

            player.currPos = player.currPos->left;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "RIGHT") == 0)
    {   
        while(player.currPos->right != NULL && count < spaces)
        {
            if(player.currPos->right->deadCell != 0)
            {
                return -1;
            }

            player.currPos = player.currPos->right;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "UPRIGHT") == 0)
    {   
        while(player.currPos->upDiagRight != NULL && count < spaces)
        {
            if(player.currPos->upDiagRight->deadCell != 0)
            {
                return -1;
            }

            player.currPos = player.currPos->upDiagRight;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "UPLEFT") == 0)
    {   
        while(player.currPos->upDiagLeft != NULL && count < spaces)
        {
            if(player.currPos->upDiagLeft->deadCell != 0)
            {
                return -1;
            }

            player.currPos = player.currPos->upDiagLeft;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "DOWNRIGHT") == 0)
    {   
        while(player.currPos->downDiagRight != NULL && count < spaces)
        {
            if(player.currPos->downDiagRight->deadCell != 0)
            {
                return -1;
            }
            //printf("%d %d ;", player.currPos->downDiagRight->gridNum, pointCount);
            player.currPos = player.currPos->downDiagRight;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }

    else if(strcmp(playerInput, "DOWNLEFT") == 0)
    {   
        while(player.currPos->downDiagLeft != NULL && count < spaces)
        {
            if(player.currPos->downDiagLeft->deadCell != 0)
            {
                return -1;
            }
            //printf("%d %d ;", player.currPos->downDiagLeft->gridNum, pointCount);
            player.currPos = player.currPos->downDiagLeft;
            count += 1;
            
        }
        if(count < spaces)
        {
            return -1;
        }
    }
    *accruedPoints += player.currPos->gridValue;// stores human player points if move is legitimate
    return player.currPos->gridNum;
}
int testDeadLock(struct totallyAHuman eitherPlayer)// tests if either player is gridlocked and has no moves left
{
    if(eitherPlayer.currPos->up == NULL || eitherPlayer.currPos->up->deadCell == 1)
    {
        if(eitherPlayer.currPos->upDiagRight == NULL || eitherPlayer.currPos->upDiagRight->deadCell == 1)
        {
            if(eitherPlayer.currPos->upDiagLeft == NULL || eitherPlayer.currPos->upDiagLeft->deadCell == 1)
            {
                if(eitherPlayer.currPos->left == NULL || eitherPlayer.currPos->left->deadCell == 1)
                {
                    if(eitherPlayer.currPos->right == NULL || eitherPlayer.currPos->right->deadCell == 1)
                    {
                        if(eitherPlayer.currPos->down == NULL || eitherPlayer.currPos->down->deadCell == 1)
                        {
                            if(eitherPlayer.currPos->downDiagLeft == NULL || eitherPlayer.currPos->downDiagLeft->deadCell == 1)
                            {
                                if(eitherPlayer.currPos->downDiagRight == NULL || eitherPlayer.currPos->downDiagRight->deadCell == 1)
                                {
                                    return -1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    struct griddy *gridHead = (struct griddy*)malloc(36*sizeof(struct griddy));// create memory space for grid structure
    int pointAccrual = 0; int pointAccrualPlayer = 0;// stores point values accrued by both players

    createMap(gridHead);
    setDirectionalPointers(gridHead);

    struct totallyAHuman player;
    struct totallyAHuman AI;
    playerInit(&player, &AI, gridHead);// player init
    printMap(gridHead, &player, &AI);// print init map state

    while(1)
    {
        if(testDeadLock(player) != -1)// checks player gridlock
        {
            int check = humanCheckIsValidMove(player, &pointAccrualPlayer);
            if(check == -1)// Error if invalid move
            {
                printf("Error try again\n");
                continue;
            }

            struct griddy *pointerPlayerNew = &gridHead[check];
            moveIt(pointerPlayerNew, &player, &pointAccrualPlayer);
        }

        if(testDeadLock(AI) != -1)// checks AI gridlock
        {
            moveIt(pathFinder(AI, &pointAccrual), &AI, &pointAccrual);
        }
        printMap(gridHead, &player, &AI);
        printf("\n");

        if(testDeadLock(AI) == -1 && testDeadLock(player) == -1)// if both stuck, game over
        {
            printf("\nGAME OVER\n");
            printf("AI: %d\nPlayer: %d\n", AI.points, player.points);
            if(AI.points > player.points)
            {
                printf("AI WINS\n");
            }
            else if(AI.points < player.points)
            {
                printf("PLAYER WINS\n");
            }
            else
                printf("TIE\n");

            free(gridHead);
            return 1;
        }
    }
    return 1;
}