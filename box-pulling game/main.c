#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void help_page(void);
void getTheOne(char *p,char target[MAXLINE]);

int main()
{
    while(1)
    {
        char begin;
        system("cls");
        printf("\n Welcome to this game! ^-^ \n");
        printf(" Please input h for help,b for beginning,l for leaving.\n");
        getTheOne(&begin,"hbl");
        system("cls");
        if(begin=='l')
            break;
        else if(begin=='h')
        {
            help_page();
            char quit;
            getTheOne(&quit,"q");
        }
        else if(begin=='b')
        {
            char choice;
            char game;
            FILE *fp = NULL;
            while(1)//The second page: when you go out of this circle,you go to the welcome page
            {
                printf("\nPlease input c to continue your last game,b to begin a new game;q to return the welcome page.\n");
                getTheOne(&choice,"cbq");
                system("cls");
                if(choice=='q')
                    break;//return to the welcome page
                else
                {
                    while(1)//The third page
                    {
                        if(choice=='c')
                        {
                            fp=fopen("C:\\Users\\az811\\Desktop\\maps\\storemap.map","r");
                        }
                        else if(choice=='b')
                        {
                            printf("\nChoose the game you want to play.Please input 1-9.\n(If you change your idea and want to leave , input q to return the welcome page.)");
                            getTheOne(&game,"123456789q");
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
                                default:break;
                            }
                        }
                        if((fscanf(fp,"%d %d %d\n",&WIDTH,&LENGTH,&BOX)!=3)&&(game!='q'))
                            printf("No store!");//go to the third page
                        else
                            break;
                    }
                    if(game=='q')
                        break;//go to the welcome page
                }
                /* initialize map */
                int map[LENGTH][WIDTH];
                initializeMap(map,fp);
                fclose(fp);

                /* initialize player position*/
                // TODO separate the player from the map
                int player[2];
                playerPosition(map,player);

                /* control game over or not */
                int end = FALSE;

                while(!end)
                {
                    // TODO print map, attention to print 'P' when meet player position
                    printMap(map,player);
                    int dir = INPLACE;
                    int win = number(map,aim);
                    if(!win)
                    {
                        printf("You got it! Congratulation!\n");
                        break;
                    }
                    printf("Please input command(w UP,s DOWN,a LEFT,d RIGHT,q QUIT,r STORE):\n");

                    /* get input from console,read a line each time */
                    char move;
                    getTheOne(&move,"wsadqr");
                    //TODO change dir according to console input.
                    switch(move){
                        case 'w':dir=UP;break;
                        case 's':dir=DOWN;break;
                        case 'a':dir=LEFT;break;
                        case 'd':dir=RIGHT;break;
                        case 'q':end=TRUE;system("cls");break;
                        case 'r':
                        {
                            /* store the map */
                            FILE *fl;
                            fl=fopen("C:\\Users\\az811\\Desktop\\maps\\storemap.map","w+");
                            storeMap(map,player,fl);
                            fclose(fl);
                            break;
                        }
                        default:break;
                    }

                    /* move player if dir is valid */
                    // TODO check a move is valid? return true for valid, false for invalid
                    if(validMove(map,player,dir)&&validBox(map,player,dir))
                        playerMove(map,player,dir);
                }
            }
        }
    }
    printf("\nGoodbye.\n");
    return 0;
}

void help_page(void)
{
    printf("\nw:wall;   *:target;   - =:empty space;   P p:you;   @:box; \nYou can use wasd to move(w:up  a:left  s:down  d:left).\n");
    printf("\nRemember\n You can\n stand on the target.\n You can't\n go through the wall ,push boxes through the wall, push two boxes together.\n");
    printf("\nWhen you stand on the target, P will turn into p .\nWhen a box is pushed into the target,* will turn into !.\n");
    printf("When all boxes are pushed into targets, you will win.\n");
    printf("\nDuring the game, you can use q to leave the game ,use r to store the map.\n");
    printf("\nGood luck for you.\n");
    printf("\nInput q to return the welcome page.\n");
}

void getTheOne(char *p,char target[MAXLINE])
{
    char input[MAXLINE];
    fgets(input,MAXLINE,stdin);
    while(strchr(target,input[0])==NULL)
    {
        printf("Invalid input.Please input again!\n");
        fgets(input,MAXLINE,stdin);
    }
    *p=input[0];
}
