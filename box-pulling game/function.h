#ifndef BOXFINAL_FUNCTION_H
#define BOXFINAL_FUNCTION_H

#define MAXLINE 256

/* map size */
extern int LENGTH;
extern int WIDTH;
extern int BOX;

/* characters need to print, 'W' for Wall, '-' for blank space, 'P' for Player */
extern char symbols[];
enum graph {wall=1,in=2,box=3,aim=4,person=5,get=6,person_in_aim=7,person_in_get=8,box_in_get=9};

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

void initializeMap(int map[LENGTH][WIDTH],FILE *fp);
void playerPosition(int map[LENGTH][WIDTH],int player[2]);
void playerFinal(int map[LENGTH][WIDTH],const int player[2]);
void playerMove(int map[LENGTH][WIDTH],int player[2],int direction);
void printMap(int map[LENGTH][WIDTH],const int player[2]);
void storeMap(int map[LENGTH][WIDTH], int player[2],FILE *fs);
int validMove(const int map[LENGTH][WIDTH],const int player[2], int direction);
int number(int map[LENGTH][WIDTH],int figure);

#endif //BOXFINAL_FUNCTION_H
