#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <unistd.h>

#define Map_S 15

typedef struct {
    char name[10];
    int row;
    int col;
    int health;
    int score;
    int keys;
    char symbol;
    int isalive;
}player;


//global 2d arrays
char map[Map_S][Map_S];
int Traps[Map_S][Map_S];
player players[2];

//func protyping 
void startingPage();
void howtoplay();
void initializeMap();
void printmap();
void placewalls();
void placeTreasures();
void placeHealthpacks();
void placeKeys();
void placeDoors();
void placeTraps();
void placeplayers();

int main(){
    srand((time(NULL)));
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
            placeplayers();
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
   placewalls();
   placeTreasures();
   placeHealthpacks();
   placeKeys();
   placeDoors();
   placeTraps();

}

void printmap(){
    for(int row=0;row < Map_S;row++){
        for(int col = 0;col < Map_S ;col++){
           printf("%c ",map[row][col]);
        }
        printf("\n");
    }

    printf("\n");
    for(int i=0;i<2;i++){
        printf("Player %s | HP: %d | Score : %d |Keys: %d \n",
            players[i].name,
            players[i].health,
            players[i].score,
            players[i].keys);
    }

}

void placewalls(){
    int walls = 0;

    while(walls<30){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' '){
              map[row][col] = '#';
              walls++;
        }

    }

}

void placeTreasures(){
    int treasures = 0;

    while(treasures < 12){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' '){
              map[row][col] = 'T';
              treasures++;
        }

    }

}

void placeHealthpacks(){
    int health = 0;

    while(health < 5){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' '){
              map[row][col] = 'H';
              health++;
        }

    }

}

void placeKeys(){
    int keys = 0;

    while(keys < 3){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' '){
              map[row][col] = 'K';
              keys++;
        }

    }

}

void placeDoors(){
    int doors = 0;

    while(doors < 3){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' '){
              map[row][col] = 'D';
              doors++;
        }

    }

}

void placeTraps(){

    int traps = 0;

    while(traps < 10){
        int row = (rand()%13)+1;
        int col = (rand()%13)+1;

        if (map[row][col]==' ' && Traps[row][col] == 0){
              Traps[row][col] = 1;
              traps++;
        }

    }

}

void placeplayers(){
    for(int i=0;i<2;i++){
        printf("Enter the %d player name :",i+1);
        scanf("%s",players[i].name);
       
        players[i].health = 100;
        players[i].score = 0;
        players[i].keys = 0;
        players[i].symbol = '1'+i;
        players[i].isalive = 1;

        int placed = 0;
        while(!placed){
            int row = rand()%13+1;
            int col = rand()%13+1;
            if(map[row][col] == ' '){
                players[i].row = row;
                players[i].col = col;
                map[row][col] = players[i].symbol;
                placed = 1;
            }

        }
    }
}