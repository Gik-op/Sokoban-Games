#ifndef BOXFINAL_FUNCTION_H
#define BOXFINAL_FUNCTION_H

#define MAXLINE 256

/* map size */
extern int LENGTH;
extern int WIDTH;
extern int BOX;

/* characters need to print, 'W' for Wall, '-' for blank space, 'P' for Player */
extern char symbols[];

/* four moving vectors */
extern int DIR[5][2];

/* boolean value */
#define TRUE 1
#define FALSE 0

/* four directions, equal to 'w','s','a','d', and INPLACE means not moving  */
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define INPLACE 4

void playerPosition(int map[LENGTH][WIDTH],int player[2]);
void playerFinal(int map[LENGTH][WIDTH],int player[2]);
void printMap(int map[LENGTH][WIDTH], int player[2]);
int validMove(int map[LENGTH][WIDTH], int player[2], int direction);
int validBox(int map[LENGTH][WIDTH], int player[2], int direction);
int number(int map[LENGTH][WIDTH],int n);

#endif //BOXFINAL_FUNCTION_H
