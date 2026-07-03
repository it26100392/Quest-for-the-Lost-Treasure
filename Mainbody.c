#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

#define Map_S 15

//global 2d arrays
char map[Map_S][Map_S];
int Traps[Map_S][Map_S];

//func protyping 
void startingPage();
void howtoplay();
void initializeMap();
void printmap();

int main(){
    //variables
    int startIn= 0;
    int goback = 0;
    
    //starting body
do{
    system("clear");
    startingPage(); 
    printf("Enter your choice:"); //getting starting input
    scanf("%d",&startIn);
    switch(startIn){
        case 1:
            system("clear");
            initializeMap();
            printmap();
            printf("\npressenter to continue ...");
            while(getchar() != '\n');
            getchar();
            break;
        case 2:
            //loadgame();
            break;
        case 3:
            system("clear");
            howtoplay();
            scanf("%d",&goback);
            if (goback == 1){
                system("clear");
                startingPage();
            }
            break;
        case 4:
         system("clear");
         printf("Thanks for playing!");
         exit(0);

        default: 
          printf("enter a number between 1-4");
          break;
    }
}while(startIn!=4);
//--------------------------------------------------------


    return 0;
}

void startingPage(){
      printf("//=====================================\\ \n");
      printf("||  ================================   ||\n");
      printf("||  ||  QUEST FOR THE LOST TREASURE || ||\n");
      printf("||  ================================   ||\n");
      printf("||                                     ||\n");
      printf("||      ~~ WELCOME, ADVENTURER ~~      ||\n");
      printf("||                                     ||\n");
      printf("||          1. Start New Game          ||\n");
      printf("||          2. Load game               ||\n");
      printf("||          3. How to play             ||\n");
      printf("||          4. Exit game               ||\n");
      printf("||                                     ||\n");
      printf("||                                     ||\n");
      printf("\\=====================================//\n");

}

void howtoplay(){

    printf("======================== Movement & Tile Interaction =========================\n");
    printf("| 1) W = up , S = down , A = left , D = right                                 |\n");
    printf("| 2) A move is rejected if the target tile is a wall (#) or is out of bounds  |\n");
    printf("|                                                                             |\n");
    printf("|======================== Win & Loss Conditions ============================= |\n");
    printf("|  1) Game ends (treasures collected): all 12 treasure tiles have been removed|\n|  from the map.                                                              |\n");                                                        
    printf("|  2) Game ends (all eliminated): every player's HP has reached 0             |\n");
    printf("|  3) At end-of-game, surviving players receive a HP bonus equal to half their|\n|  remaining HP,then a ranked leaderboard is displayed                        |\n");
    printf("|                                                                             |\n");
    printf("| *Enter 1 to go back *                                                       |\n");
    printf("|=============================================================================|\n");
}

void initializeMap(){

    for(int row=0;row < Map_S;row++){
        for(int col = 0;col < Map_S ;col++){
            map[row][col]= ' ';
            Traps[row][col] = 0;
        }
    }

    for(int row=0;row<Map_S;row++){
        for(int col = 0;col<Map_S;col++){
            if(row==0 || row == Map_S-1 || col==0 || col == Map_S-1){
                map[row][col] = '#';
            }
        }
    }


}

void printmap(){
    for(int row=0;row < Map_S;row++){
        for(int col = 0;col < Map_S ;col++){
           printf("%c ",map[row][col]);
        }
        printf("\n");
    }

}