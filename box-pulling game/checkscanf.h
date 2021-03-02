#include <stdio.h>
#include <stdlib.h>

void validScanf_char(char*p)
{
    while(1)
    {
        char line[MAXLINE];
        fgets(line,MAXLINE,stdin);
        switch(line[0])
        {
            case 'w':*p=line[0];break;
            case 'a':*p=line[0];break;
            case 's':*p=line[0];break;
            case 'd':*p=line[0];break;
            case 'q':*p=line[0];break;
            case 'r':*p=line[0];break;
            default:printf("Wrong input! ");continue;
        }
        break;
    }
}
void vscanf0(char*get ,char a, char b,char c)
{
    char choice;
     while(1)
    {
        choice=getchar();
        if(choice==a||choice==b||choice==c)
        {
            while(getchar()!='\n')
                continue;
            break;
        }
        while(getchar()!='\n')
            continue;
        printf("Input again!\n");
    }
    *get=choice;
}
void vscanf1(char*get)
{
    char choice;
     while(1)
    {
        choice=getchar();
        if(choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5'||choice=='6'||choice=='7'||choice=='8'||choice=='9'||choice=='q')
        {
            while(getchar()!='\n')
                continue;
            break;
        }
        while(getchar()!='\n')
            continue;
        printf("Input again!\n");
    }
    *get=choice;
}
void returnn(void)
{
    char choice;
     while(1)
    {
        choice=getchar();
        if(choice=='q')
        {
            while(getchar()!='\n')
                continue;
            break;
        }
        while(getchar()!='\n')
            continue;
        printf("Input again!\n");
    }
}

