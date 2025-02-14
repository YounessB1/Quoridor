/*
this file handles the global variable map with handles the game
0 represent an empty position
1 resprent th erpesence of a wall
2 represent th epresence of a player 
*/
void mapInit(void); // initisliza map with all zeros
int mapIndex(int pos); // gets and index given the centre of a box
void mapWall(int posx, int posy, int orientation); // maps the wall on the map
void mapPlayer(int posx, int posy); // maps th eplayer on the map 
