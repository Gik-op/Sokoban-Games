#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    while(1){
    char begin;
    Leavethis:printf("\n Welcome to this game! ^-^ \n");
    printf(" Please input h for help,b for begining,l for leaving.\n");
    vscanf0(&begin,'h','b','l');
    system("cls");
    switch(begin)
    {
        case 'b':
    {
    /* initialize map */
    char choice;
    FILE*fp=NULL;
    Ilovegoto:printf("\nPlease input c to continue your last game,b to begin a new game;q to return the welcome page.\n");
    vscanf0(&choice,'c','b','q');
    system("cls");
    if(choice=='q')
    {
        break;
    }
    else if(choice=='c')
    {
         fp=fopen("C:\\Users\\az811\\Desktop\\maps\\storemap.map","r");
    }
    else
    {
        char game;
        choosegame:printf("\nChoose the game you want to play.Please input 1-9.\n(If you change your idea and want to leave , input q to return the welcome page.)");
        vscanf1(&game);
        switch(game)
        {
            case '1':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\1.map","r");break;
            case '2':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\2.map","r");break;
            case '3':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\3.map","r");break;
            case '4':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\4.map","r");break;
            case '5':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\5.map","r");break;
            case '6':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\6.map","r");break;
            case '7':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\7.map","r");break;
            case '8':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\8.map","r");break;
            case '9':fp=fopen("C:\\Users\\az811\\Desktop\\maps\\9.map","r");break;
            case 'q':system("cls");goto Leavethis;
        }
    }
    if(fscanf(fp,"%d %d %d\n",&WIDTH,&LENGTH,&BOX)!=3)
    {
        printf("No store!");
        goto choosegame;
    }
    int map[LENGTH][WIDTH];
    for(int i=0;i<LENGTH;i++)
    {
        for(int i2=0;i2<WIDTH;i2++)
        {
            if((i2+1)%WIDTH==0)
            {
                fscanf(fp,"%1d\n",&map[i][i2]);
            }
            else
                fscanf(fp,"%1d",&map[i][i2]);
        }

    }
    fclose(fp);
    /* initialize player position*/
    int player[2];
    playerPosition(map,player);

    /* control game over or not */
    int end = FALSE;

    while(!end){
        printMap(map,player);
        printf("\n");
        int dir = INPLACE;
        int win = number(map,4);
        if(!win)
        {
            printf("You got it! Congratulaton!\n");
            goto Ilovegoto;
        }
        printf("Please input command(w UP,s DOWN,a LEFT,d RIGHT,q QUIT,r STORE):\n");
        while(1){
            /* get input from console,read a line each time */
            char move;
            validScanf_char(&move);
            // TODO: change dir according to console input.
            switch(move){
                case 'w':dir=UP;break;
                case 's':dir=DOWN;break;
                case 'a':dir=LEFT;break;
                case 'd':dir=RIGHT;break;
                case 'q':end=TRUE;system("cls");break;
                case 'r':
                         {
                          /* initialize player */
                          playerFinal(map,player);

                          FILE*fl;
                          BOX=number(map,3)+number(map,9);
                          fl=fopen("C:\\Users\\az811\\Desktop\\maps\\storemap.map","w+");
                          fprintf(fl,"%1d %1d %1d\n",WIDTH,LENGTH,BOX);
                          for(int m=0;m<LENGTH;m++)
                          {
                              for(int m2=0;m2<WIDTH;m2++)
                              {
                                  fprintf(fl,"%d",map[m][m2]);
                              }
                              fprintf(fl,"\n");
                          }
                          fclose(fl);playerPosition(map,player);break;
                          }
                 default:break;
            }
            break;
        }
        /* move player if dir is valid */
        if(validMove(map,player,dir)&&validBox(map,player,dir)){
            int leng=DIR[dir][0]+player[0];
            int wid=DIR[dir][1]+player[1];
            int lengmore=leng+DIR[dir][0];
            int widmore=wid+DIR[dir][1];
            if(map[leng][wid]==3)
            {
                if(map[lengmore][widmore]!=4)
                {
                    if(map[lengmore][widmore]==6)
                    {
                        map[lengmore][widmore]=9;
                    }
                    else map[lengmore][widmore]=3;
                    map[leng][wid]=2;
                }//以9为标签去标记走在！上的箱子
                else
                {
                    map[lengmore][widmore]=6;
                    map[leng][wid]=2;
                }
            }
            if(map[leng][wid]==9)
            {
                map[leng][wid]=6;
                if(map[lengmore][widmore]==4)
                {
                    map[lengmore][widmore]=6;
                }
                else if(map[lengmore][widmore]==6)
                {
                    map[lengmore][widmore]=9;
                }
                else map[lengmore][widmore]=3;
            }
            player[0] += DIR[dir][0];
            player[1] += DIR[dir][1];
        }
    }
    break;
            }
            case 'l':goto leavethisgame;
            case 'h':
                printf("\nw:wall;   *:target;   - =:empty space;   P p:you;   @:box; \nYou can use wasd to move(w:up  a:left  s:down  d:left).\n");
                printf("\nRemember\n You can\n stand on the target.\n You can't\n go through the wall ,push boxes through the wall, push two boxes together.\n");
                printf("\nWhen you stand on the target, P will turn into p .\nWhen a box is pushed into the target,* will turn into !.\n");
                printf("When all boxes are pushed into targets, you will win.\n");
                printf("\nDuring the game, you can use q to leave the game ,use r to store the map.\n");
                printf("\nGood luck for you.\n");
                printf("\nInput q to return the welcome page.\n");
                returnn();system("cls");
                break;
    }//switch的大括号
    }//此为最大循环的后括号
    leavethisgame:printf("\nGoodbye.\n");
    return 0;
}
