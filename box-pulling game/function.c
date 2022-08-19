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

void initializeMap(int map[LENGTH][WIDTH],FILE *fp)
{
    for(int i=0;i<LENGTH;i++)
    {
        for(int i2=0;i2<WIDTH;i2++)
        {
            if((i2+1)%WIDTH==0)
                fscanf(fp,"%1d\n",&map[i][i2]);
            else
                fscanf(fp,"%1d",&map[i][i2]);
        }
    }
}

/* separate the player from the map */
void playerPosition(int map[LENGTH][WIDTH],int player[2])
{
    for(int length=0;length<LENGTH;length++)
        for(int width=0;width<WIDTH;width++)
        {
            switch(map[length][width])
            {
                case person:map[length][width]=in;break;
                case person_in_aim:map[length][width]=aim;break;
                case person_in_get:map[length][width]=get;break;
                default:continue;
            }
            player[0]=length;
            player[1]=width;
        }
}

/* merge the player location into the map */
void playerFinal(int map[LENGTH][WIDTH],const int player[2])
{
    for(int length=0;length<LENGTH;length++)
        for(int width=0;width<WIDTH;width++)
        {
            if(length==player[0]&&width==player[1])
            {
                if(map[length][width]==aim)
                    *(*(map+length)+width)=person_in_aim;
                else if(map[length][width]==get)
                    *(*(map+length)+width)=person_in_get;
                else *(*(map+length)+width)=person;
            }
        }
}

void playerMove(int map[LENGTH][WIDTH],int player[2],const int direction)
{
    int leng=DIR[direction][0]+player[0];
    int wid=DIR[direction][1]+player[1];
    int lengmore=leng+DIR[direction][0];
    int widmore=wid+DIR[direction][1];
    if(map[leng][wid]==box)
    {
        if(map[lengmore][widmore]!=aim)
        {
            if(map[lengmore][widmore]==get)
            {
                map[lengmore][widmore]=box_in_get;
            }
            else map[lengmore][widmore]=box;
            map[leng][wid]=in;
        }
        else
        {
            map[lengmore][widmore]=get;
            map[leng][wid]=in;
        }
    }
    if(map[leng][wid]==box_in_get)
    {
        map[leng][wid]=get;
        if(map[lengmore][widmore]==aim)
        {
            map[lengmore][widmore]=get;
        }
        else if(map[lengmore][widmore]==get)
        {
            map[lengmore][widmore]=box_in_get;
        }
        else map[lengmore][widmore]=box;
    }
    player[0] += DIR[direction][0];
    player[1] += DIR[direction][1];
}

void printMap(int map[LENGTH][WIDTH], const int player[2])
{
    system("cls");
    printf("\n");
    for(int length=0;length<LENGTH;length++)
    {
        printf("          ");
        for(int width=0;width<WIDTH;width++)
        {
            int index=map[length][width];
            if(length==player[0]&&width==player[1])
            {
                if(map[length][width]==aim||map[length][width]==get)
                    printf("%c",symbols[person_in_aim]);
                else
                    printf("%c",symbols[person]);
            }
            else if(map[length][width]==box_in_get||map[length][width]==box)
                printf("%c",symbols[box]);
            else
                printf("%c",symbols[index]);
        }
        printf("\n");
    }
    printf("\n");
}

void storeMap(int map[LENGTH][WIDTH], int player[2],FILE *fs)
{
    playerFinal(map,player);
    BOX=number(map,box)+number(map,box_in_get);
    fprintf(fs,"%1d %1d %1d\n",WIDTH,LENGTH,BOX);
    for(int m=0;m<LENGTH;m++)
    {
        for(int m2=0;m2<WIDTH;m2++)
        {
            fprintf(fs,"%d",map[m][m2]);
        }
        fprintf(fs,"\n");
    }
    playerPosition(map,player);//used in pairs with function playerFinal()
}

int validMove(const int map[LENGTH][WIDTH],const int player[2], int direction)
{
    int length=DIR[direction][0]+player[0];
    int width=DIR[direction][1]+player[1];
    if(length<LENGTH&&length>=0&&width>=0&&width<WIDTH&&map[length][width]!=wall)
        return TRUE;
    else
        return FALSE;
}

int validBox(const int map[LENGTH][WIDTH],const int player[2], int direction)
{
    int length=DIR[direction][0]+player[0];
    int width=DIR[direction][1]+player[1];
    int lengthmore=length+DIR[direction][0];
    int widthmore=width+DIR[direction][1];
    if((map[length][width]!=box&&map[length][width]!=box_in_get)||((map[length][width]==box||map[length][width]==box_in_get)\
        &&(map[lengthmore][widthmore]!=box_in_get&&map[lengthmore][widthmore]!=box\
       &&map[lengthmore][widthmore]!=wall&&lengthmore<LENGTH&&widthmore<WIDTH)))
        return TRUE;
    else
        return FALSE;
}

int number(int map[LENGTH][WIDTH],int figure)
{
    int sum=0;
    for(int length=0;length<LENGTH;length++)
    {
        for(int width=0;width<WIDTH;width++)
        {
            if (map[length][width]==figure)
                sum++;
        }
    }
    return sum;
}
