
extern unsigned int turn;
extern unsigned int map[13][13];
extern unsigned int walls[2];
extern unsigned int time;
extern unsigned int orientation; 
extern unsigned int wallFlag;
extern unsigned int px[2],py[2];
extern unsigned int currX,currY;

extern int centers[]; // centers of boxes ad walls

void printTime(void);
void printRemainingWalls(void);
void setMove(void);
void gameInit(void);
void nextMove(void);
int checkVictory(void);
