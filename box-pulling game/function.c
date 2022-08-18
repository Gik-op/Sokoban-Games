#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/* map size */
int LENGTH;
int WIDTH;
int BOX;

/* characters need to print, 'W' for Wall, '-' for blank space, 'P' for Player */
char symbols[] = {'-','W','=','@','*','P','!','p'};

/* four moving vectors */
int DIR[5][2] = {
        {-1,0},             /* UP */
        {1,0},              /* DOWN */
        {0,-1},             /* LEFT */
        {0,1},              /* RIGHT */
        {0,0}               /* SITU */
};

void playerPosition(int map[LENGTH][WIDTH],int player[2])
{
    for(int length=0;length<LENGTH;length++)
    {
        for(int width=0;width<WIDTH;width++)
        {
            if( map[length][width]==5)
            {
                *player=length;
                *(player+1)=width;
                *(*(map+length)+width)=2;
            }
            else if(map[length][width]==7)
            {
                *player=length;
                *(player+1)=width;
                *(*(map+length)+width)=4;
            }
            else if(map[length][width]==8)
            {
                *player=length;
                *(player+1)=width;
                *(*(map+length)+width)=6;
            }
        }
    }
}

void playerFinal(int map[LENGTH][WIDTH],int player[2])
{
    for(int length=0;length<LENGTH;length++)
    {
        for(int width=0;width<WIDTH;width++)
        {
            if(length==player[0]&&width==player[1])
            {
                if(map[length][width]==4)
                {
                    *(*(map+length)+width)=7;
                }
                else if(map[length][width]==6)
                {
                    *(*(map+length)+width)=8;
                }
                else *(*(map+length)+width)=5;
            }
        }
    }
}

// TODO print map, attention to print 'P' when meet player position
void printMap(int map[LENGTH][WIDTH], int player[2])
{
    system("cls");
    printf("\n");
    for(int length=0;length<LENGTH;length++)
    {
        printf("          ");
        for(int width=0;width<WIDTH;width++)
        {
            if(length==player[0]&&width==player[1])
            {
                if(map[length][width]==4||map[length][width]==6)
                {
                    printf("%c",symbols[7]);
                }
                else printf("%c",symbols[5]);
            }
            else if(map[length][width]==0)
                printf("%c",symbols[0]);
            else if(map[length][width]==1)
                printf("%c",symbols[1]);
            else if(map[length][width]==2)
                printf("%c",symbols[2]);
            else if(map[length][width]==3)
                printf("%c",symbols[3]);
            else if(map[length][width]==4)
                printf("%c",symbols[4]);
            else if(map[length][width]==6)
                printf("%c",symbols[6]);
            else if(map[length][width]==9)
            {
                printf("%c",symbols[3]);
            }
        }
        printf("\n");
    }
}

// TODO check a move is valid? return true for valid, false for invalid
int validMove(int map[LENGTH][WIDTH], int player[2], int direction)
{
    int length=DIR[direction][0]+player[0];
    int width=DIR[direction][1]+player[1];
    if(length<LENGTH&&length>=0&&width>=0&&width<WIDTH&&map[length][width]!=1)
    {
        return TRUE;
    }
    else return FALSE;
}

int validBox(int map[LENGTH][WIDTH], int player[2], int direction)
{
    int length=DIR[direction][0]+player[0];
    int width=DIR[direction][1]+player[1];
    int lengthmore=length+DIR[direction][0];
    int widthmore=width+DIR[direction][1];
    if((map[length][width]!=3&&map[length][width]!=9)||((map[length][width]==3||map[length][width]==9)\
        &&(map[lengthmore][widthmore]!=9&&map[lengthmore][widthmore]!=3\
       &&map[lengthmore][widthmore]!=1&&lengthmore<LENGTH&&widthmore<WIDTH)))
        return TRUE;
    else
        return FALSE;
}

int number(int map[LENGTH][WIDTH],int n)
{
    int sum=0;
    for(int length=0;length<LENGTH;length++)
    {
        for(int width=0;width<WIDTH;width++)
        {
            if (map[length][width]==n)
                sum++;
        }
    }
    return sum;
}
