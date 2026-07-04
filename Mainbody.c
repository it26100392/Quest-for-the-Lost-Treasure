#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define Map_S 15
#define Mxplayers 3

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
player players[3];
int activePlayers = 2;

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
int isValidMove(int row,int col);
void processTile(int index);
void movePlayer(int index);
void gameloop();
void showscore();
void savegame();
void loadgame();

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
            printf("====== SELECT THE PLAYER MODE =====\n");
            printf("| 1) 2 PLAYERS                     |\n");
            printf("| 2) 3 PLAYERS                     |\n");
            printf("|__________________________________|\n");
            int choise;
            scanf("%d",&choise);
             if (choise == 2){
                activePlayers = 3;
             }else {
                activePlayers = 2;
             }

            system("clear");
            initializeMap();
            placeplayers();
            gameloop();
            break;
        case 2:
            system("clear");
            loadgame();
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
        printf("     ");
        for(int col = 0;col < Map_S ;col++){
           printf("%c ",map[row][col]);
        }
        printf("\n");
    }

    printf("\n");
    for(int i=0;i<activePlayers;i++){
        printf("____________________________________________________________\n");
        printf("\n");
        printf("Player %d :%-10s  | HP: %d  | Score : %d  |Keys: %d \n",
            i+1,
            players[i].name,
            players[i].health,
            players[i].score,
            players[i].keys);
        printf("____________________________________________________________\n");
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

    for(int i=0;i<activePlayers;i++){
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


int isValidMove(int row,int col){
    if(row<0 || row >= Map_S || col<0 || col>= Map_S){
        return 0;
    }

    if (map[row][col] == '#'){
        return 0;
    }
    return 1;
}

void processTile(int index){

    int row = players[index].row;
    int col = players[index].col;
    
    if(Traps[row][col] == 1){

            players[index].health -= 20;
            Traps[row][col] = 0;
            printf("%s caught on a trap -20HP\n",players[index].name);

            if(players[index].health <= 0){
                players[index].health = 0;
                players[index].isalive = 0;
                printf("%s has been eliminated\n",players[index].name);
            }
    }

    if(map[row][col] == 'T'){
        players[index].score += 10;
        map[row][col] = ' ';
        printf("\n Nice JOB! %s found a treasure! +10 Score\n",players[index].name);

    }

    if(map[row][col] == 'H'){
        players[index].health += 20;
         if(players[index].health > 100){
            players[index].health = 100;
         }

         map[row][col]=' ';
         printf("\n %s got a Medikit! +20HP\n",players[index].name);

    }

    if(map[row][col]=='K'){
        players[index].keys += 1;
        map[row][col] = ' ';
        printf("%s picked up a key !",players[index].name);
    }

}

void movePlayer(int index){
    char moves[50];

    printf("\n%s (player %d)enter moves (WASD)|max 4 moves :",players[index].name,index+1);
    scanf("%s",moves);

    if(strlen(moves)>4){
        printf("  --------------------------------------------------\n");
        printf("  | Too many moves! Your turn hass been cancelld !!!|\n");
        printf("   --------------------------------------------------\n");
        
        fflush(stdout);
        sleep(1.3);
        return;
    }
      
        int newrow = players[index].row;
        int newcol = players[index].col;

    for(int i = 0;i < strlen(moves);i++){
        char move = toupper(moves[i]);

        int newrow = players[index].row;
        int newcol = players[index].col;


        if(move == 'W'){
            newrow--;
        }else if(move == 'S'){
            newrow++;
        }else if(move =='A'){
            newcol--;
        }else if(move =='D'){
            newcol++;
        }else{
            printf("You have entered a invalid move '%c' !!! SKIPPED !!!\n",moves[i]);
            continue;
        }
    

    if(map[newrow][newcol] == 'D'){
        if(players[index].keys > 0){
            players[index].keys--;
            map[newrow][newcol] = ' ';
            printf("%s unlocked a door!\n",players[index].name);
        }else{
            printf("%s need a key to open this door!\n",players[index].name);
             continue;
        }
    }

    if(isValidMove(newrow,newcol)){

        map[players[index].row][players[index].col] = ' ';

        players[index].row = newrow;
        players[index].col = newcol;

        processTile(index);

        map[players[index].row][players[index].col] = players[index].symbol;

    }else{
      printf("Invalid Move blocked !!!\n");

    }
  }

  fflush(stdout);
  sleep(1.3);

}

void gameloop(){
   int gamerunning = 1;

   while(gamerunning){

       for(int i=0;i<activePlayers;i++){
        if(!players[i].isalive) continue;
        
        system("clear");
        printmap();

        movePlayer(i);

        int chestLeft = 0;
        for(int r=0;r<15;r++){
            for(int c=0;c<15;c++){
                if(map[r][c] == 'T'){
                    chestLeft++;
                }
                
            }
        }

        if(chestLeft == 0){
            printf("\n ALL TREASURES HAVE BEEN COLLECTED\n");
            printf("---------GAME OVER-------\n");

            showscore();
            gamerunning = 0;
            break;
        }

        int aliveplayers = 0;
        for(int j=0;j<activePlayers;j++){
            if(players[j].isalive){
                aliveplayers++;
            }}

            if(aliveplayers == 0){
                printf("\n All players has been eleminated !\n");
                printf("-------GAME OVER-------\n");

                showscore();
                gamerunning = 0;
                break;
            }
       }

       if(gamerunning){
        int savechoise;
        printf("\n Do you want to save? (1:YES / 0:NO) : ");
        scanf("%d",&savechoise);
        if(savechoise == 1){
            savegame();
        }
       }

   }

}

void showscore(){
     system("clear");
      printf("\n================ HP BONUS ==============\n");
      for(int i=0;i<activePlayers;i++){
       if(players[i].isalive){
        int bonus = players[i].health/2;
        players[i].score += bonus;
        printf("%s received +%d bonus score (HP/2)",players[i].name,bonus);
      }
    }  
     
    for (int i=0;i<activePlayers;i++){
        for(int j=0;j<activePlayers-1-i;j++){
            if(players[j].score < players[j+1].score){
                player temp =players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }

    printf("\n");
    printf("===========================================\n");
    printf("||              LEADERBOARD              ||\n");
    printf("===========================================\n");

    char *ranks[] = {"1st","2nd","3rd"};

    for(int i=0;i<activePlayers;i++){
    printf("||  %s > %-10s   Score: %-8d ||\n",ranks[i],players[i].name,players[i].score);
    }

    printf("===========================================\n");


    if(activePlayers > 1 && players[0].score == players[1].score){
        printf("||~~~~~~~~~~~~~ MATCH IS A TIE ~~~~~~~~~~||\n");
    }else{
        printf("     WINNER IS %-25s  \n",players[0].name);
    }
    
    printf("===========================================\n");

    fflush(stdout);
    printf("\n Press ENTER to go back to main menu ");
    while(getchar() != '\n');
    getchar();
    
}    



void savegame(){
    FILE *file=fopen("savefile.dat","wb");

    if (file == NULL){
        printf("Error saving game!");
        return;
    }

    fwrite(&activePlayers, sizeof(int),1,file);
    fwrite(players, sizeof(player),activePlayers,file);
    fwrite(map, sizeof(map),1,file);
    fwrite(Traps, sizeof(Traps),1,file);
    fclose(file);

    printf("\n");
    printf("===========================================\n");
    printf("           GAME SAVED SUCCESSFULLY         \n");
    printf("===========================================\n");

    fflush(stdout);
    sleep(2);
}

void loadgame(){

    FILE *file = fopen("savefile.dat","rb");

    if(file == NULL){
    printf("\n");
    printf("===========================================\n");
    printf("            NO SAVE FILE FOUND             \n");
    printf("            Starting a new game ...        \n");
    printf("===========================================\n");

    fflush(stdout);
    sleep(2);
    return;

    }


    fread(&activePlayers ,sizeof(int),1,file );

    if(activePlayers<2 || activePlayers>3){
        printf("\n WARNING ! somthings wrong with the save file !!!\n");
        fclose(file);
        fflush(stdout);
        sleep(2);
        return;
    }

    fread(players, sizeof(player),activePlayers,file);
    fread(map, sizeof(map),1,file);
    fread(Traps, sizeof(Traps),1,file);
    fclose(file);

    printf("\n");
    printf("===========================================\n");
    printf("              GAME FILE LOADED             \n");
    printf("===========================================\n");

    fflush(stdout);
    sleep(2);

    gameloop();


}  
