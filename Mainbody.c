#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

void startingPage();
void howtoplay();

int main(){
    //variables
    int startIn= 0;
    int goback = 0;
    
    //starting body
do{
    system("cls");
    startingPage(); 
    printf("Enter your choice:"); //getting starting input
    scanf("%d",&startIn);
    switch(startIn){
        case 1:
           // newgame();
            break;
        case 2:
            //loadgame();
            break;
        case 3:
            system("cls");
            howtoplay();
            scanf("%d",&goback);
            if (goback == 1){
                system("cls");
                startingPage();
            }
            break;
        case 4:
         system("cls");
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
      printf("||          4  Exit game               ||\n");
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