#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define Map_S 15
#define Mxplayers 3
#define LOG_SIZE 100
#define LOG_DISPLAY 5
#define LOG_LENGTH 100

//defining a structure for the player 
typedef struct {
    char name[10];
    int row;
    int col;
    int health;
    int score;
    int keys;
    char symbol;
    int isalive;

    //for the player stat
    int moveMade;
    int chestfound;
    int traphit;
    int damageTaken;
    int healthPackUsed;
    int keysCollected;
    int doorsUnlocked;
}player;


//globle varibles . so we can use in any function
char map[Map_S][Map_S];
int Traps[Map_S][Map_S];
player players[3];  //this is a variable named players as the data structre of player and also it can hold 3 elements as well
int activePlayers = 2;   
int roundCounter=0;

char eventLog[LOG_SIZE][LOG_LENGTH];
int logCount = 0;
int logIndex = 0;

//func protyping .because of i declared all of the functions after main() function 
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
void addLog(char *message);
void printRecentLog();
void saveLog();
void showStats();

//the main function
int main(){
    srand((time(NULL)));
    //variables
    int startIn= 0;
    int goback = 0;
    
    //starting body of the game 
do{
    system("clear");  //clear the terminal
    startingPage();  
    printf("Enter your choice:"); //getting starting input for switch statement.
    scanf("%d",&startIn);
    switch(startIn){
        case 1:
            system("clear");
            printf("====== SELECT THE PLAYER MODE =====\n");
            printf("|     1 >  1 PLAYERS               |\n");
            printf("|     2 >  2 PLAYERS               |\n");
            printf("|     3 >  3 PLAYERS               |\n");
            printf("====================================\n");
            printf("Enter 1 to the Single player game \n");
            printf("Enter 2 to the Two player game \n");
            printf("Enter 3 to the Three player game \n");
            printf("====================================\n");

            int choise;
            printf("Plyer mode : ");
            scanf("%d",&choise);
             if (choise == 1){
                activePlayers = 1;
             }else if(choise == 2) {
                activePlayers = 2;
             }else if (choise == 3){
                activePlayers = 3;
             }else{
                printf("\n INvalid choise Defulting to 2 player Mode... \n");
                fflush(stdout);
                 sleep(2);
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

      //used break statement because otherwise after commands of one case is executed its going to fall to the next case automatically
    }
}while(startIn!=4);
/* > put a do while so the game starting page can show unless user input 4
   >and inside the do while loop i put a switch statement so after getting a user choise user can go
     to new game or load game or how to play or quit */
//--------------------------------------------------------


    return 0;
}

void startingPage(){
      printf(" ======================================= \n");
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
      printf(" =======================================\n");

      /*>this is the starting page's ui using printf function
        > and also this is a function without a return type 
          so when i declaring the function use void instead of a data type */

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

   // this is the function that hold how to play instructions 
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

/*  > first in the above i created  2d array named map[][] and Traps[][]
    > used two for loops inside the initializeMap function to initiate the boarder and the empty cells
    > and also at the beginning didn't set any traps 
    > above for loops only for boarder and the empty cells of the map of the game*/
   placewalls();
   placeTreasures();
   placeHealthpacks();
   placeKeys();
   placeDoors();
   placeTraps();

   /*the i called above 6 functions 
   all of above functions are described inside their own local scope*/
}

void printmap(){

    printf("       ===========================================\n");
    printf("       ||       QUEST FOR THE LOST TREASURE     ||\n");
    printf("       ||               ROUND %-3d               ||\n",roundCounter+1);
    printf("       ===========================================\n");
    printf("\n");


    for(int row=0;row < Map_S;row++){
        printf("              ");
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

    printf("____________________________________________________________\n");
    /*inside printmap function; after initializing the map with all of the elements we print it in the terminal
     > not only the map the other details such as round counter and players currunt details are being printed in the terminal */
}


void placewalls(){
    int walls = 0;

    while(walls<30){
        int row = (rand()%13)+1; 
        int col = (rand()%13)+1;
        /*using rand function to genarate a radome number; but it can be any number so using modulus dividing method ,
        i divided that random number by 13 so any number divided by 13 and its remain is must keep between 1 and 13 
        we want that between 1 and 13 because the outer wall is in 0th and 14*/

        if (map[row][col]==' '){ //in this if statement it checks whether its empty tile or not 
              map[row][col] = '#'; // if the tile is empty it places the wall
              walls++; //then it update the walls count
        }

    }

    /*as in the assignment rules in this function place 30 walls inside the map*/
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
  
    /*using the same above mechanism we place treasures inside the map using this function*/
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
 /*again using the same above mechanism we place health packs inside the map*/
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
/*again using the same above mechanism we place keys packs inside the map*/
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
/*again using the same above mechanism we place doors packs inside the map*/
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
/*and also using the same above mechanism we place traps packs inside the map
but unlike other above placing elements we dont call this function inside the printmap so traps remaining hidden*/
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

        players[i].moveMade = 0;
        players[i].chestfound = 0;
        players[i].traphit = 0;
        players[i].damageTaken = 0;
        players[i].healthPackUsed = 0;
        players[i].keysCollected = 0;
        players[i].doorsUnlocked = 0;
        /*inside the for loop we declared a local i varible so we can place each player according to player mode */
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
    /*in here we use rand for the same reason and we place playes like all above elements*/
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
    char logMsg[LOG_LENGTH];
    
    if(Traps[row][col] == 1){

            players[index].health -= 20;
            players[index].traphit++;
            players[index].damageTaken +=20;
            Traps[row][col] = 0;
            snprintf(logMsg,LOG_LENGTH,"%s hit a trap! -20HP",players[index].name);
            addLog(logMsg);
            printf("%s caught on a trap -20HP\n",players[index].name);

            if(players[index].health <= 0){
                players[index].health = 0;
                players[index].isalive = 0;
                snprintf(logMsg,LOG_LENGTH,"%s has been eliminated!",players[index].name);
                addLog(logMsg);
                printf("%s has been eliminated\n",players[index].name);
            }
    }

    if(map[row][col] == 'T'){
        players[index].score += 10;
        players[index].chestfound++;
        map[row][col] = ' ';
        snprintf(logMsg,LOG_LENGTH,"%s found a treasure +10 Score",players[index].name);
        addLog(logMsg);        
        printf("\n Nice JOB! %s found a treasure! +10 Score\n",players[index].name);

    }

    if(map[row][col] == 'H'){
        players[index].health += 20;
        players[index].healthPackUsed++;
         if(players[index].health > 100){
            players[index].health = 100;
         }

         map[row][col]=' ';
         snprintf(logMsg,LOG_LENGTH,"%s used a health pack! +20HP",players[index].name);
         addLog(logMsg);
         printf("\n %s got a Medikit! +20HP\n",players[index].name);

    }

    if(map[row][col]=='K'){
        players[index].keys += 1;
        players[index].keysCollected++;
        map[row][col] = ' ';
        snprintf(logMsg,LOG_LENGTH,"%s picked up a key",players[index].name);
        addLog(logMsg);
        printf("%s picked up a key !",players[index].name);
    }
/*
 >in here we Checks the tile at the player's new position and applies effects then
 > Handles traps (-20HP), treasures (+10 score), health packs (+20HP),
   and keys (+1 inventory). Removes item from map after collection.
 > as the  Parameter we use  index - the player array index
 */
}

void movePlayer(int index){
    char moves[50];//initializing a string that can hold 50 charachters

    printf("\n%s (player %d)enter moves (WASD)|max 4 moves :",players[index].name,index+1);
    scanf("%s",moves); //in here we Reads up to 4 move characters (WASD) from the player.
    
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
        char move = toupper(moves[i]); //using toupper function becase if user enters the lowercase 

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
            players[index].doorsUnlocked++;
            map[newrow][newcol] = ' ';
            char logMsg[LOG_LENGTH];
            snprintf(logMsg,LOG_LENGTH,"%s unlocked a door !",players[index].name);
             addLog(logMsg);
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
        players[index].moveMade++;

        processTile(index);

        map[players[index].row][players[index].col] = players[index].symbol;

    }else{
      printf("Invalid Move blocked !!!\n");

    }
  }
  /*
 > after getting the moves ;Validates each move for bounds and walls, handles door entry
   with key check, updates player position on map, and calls
   processTile() after each successful step.
  in this function as the Parameter we use index again - the player array index
 */

  fflush(stdout);
  sleep(1.3);

}

void gameloop(){
   int gamerunning = 1;

   while(gamerunning){

       for(int i=0;i<activePlayers;i++){
        if(!players[i].isalive) continue;
        
        system("clear");//in here we use clear to clean out the previous state of the map
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
            saveLog();
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
                saveLog();
                showscore();
                gamerunning = 0;
                break;
            }
       }

       if(gamerunning){
        roundCounter++;
        int savechoise;
        printf("\n Do you want to save? (1:YES / 0:NO) : ");// Prompt to save after each complete round.
        scanf("%d",&savechoise);//getting the saving choise
        if(savechoise == 1){
            savegame(); 
        }
       }

   }

   /*
 > this is the Main game loop that runs until win or loss condition is met.
 > Each iteration gives every living player a turn, then checks
   if all treasures are collected or all players are eliminated. */
}

void showscore(){
     system("clear");
      printf("\n             ================= HP BONUS ================\n");
      for(int i=0;i<activePlayers;i++){
       if(players[i].isalive){
        int bonus = players[i].health/2;
        players[i].score += bonus;
        printf("                * %s received +%d bonus score (HP/2) \n",players[i].name,bonus);
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
    printf("             ===========================================\n");
    printf("             ||              LEADERBOARD              ||\n");
    printf("             ===========================================\n");

    char *ranks[] = {"1st","2nd","3rd"};

    for(int i=0;i<activePlayers;i++){
    printf("             ||   %s > %-10s   Score: %-8d  ||\n",ranks[i],players[i].name,players[i].score);
    }

    printf("             ===========================================\n");


    if(activePlayers > 1 && players[0].score == players[1].score){
        printf("             ||~~~~~~~~~~~~~ MATCH IS A TIE ~~~~~~~~~~||\n");
    }else{
        printf("             >>>>>         WINNER IS %-13s<<<<<  \n",players[0].name);
    }
    
    printf("             ===========================================\n");

    fflush(stdout);
    showStats();
    printf("\n Press ENTER to go back to main menu ");
    while(getchar() != '\n');
    getchar();
    
}    



void savegame(){
    FILE *file=fopen("savefile.dat","wb");// in here we open file for binary writing

    if (file == NULL){ // check if file opened successfully
        printf("Error saving game!\n");
        return;
    }

    fwrite(&activePlayers, sizeof(int),1,file);
    fwrite(players, sizeof(player),activePlayers,file);
    fwrite(map, sizeof(map),1,file);
    fwrite(Traps, sizeof(Traps),1,file);
    fwrite(&roundCounter, sizeof(int),1,file);
    fclose(file);

    printf("\n");
    printf("===========================================\n");
    printf("           GAME SAVED SUCCESSFULLY         \n");
    printf("===========================================\n");

    fflush(stdout);
    sleep(2);
    /*
 > in this function Saves the current game state to savefile.dat in binary format.
 > Writes active players count, round counter, event log,
   player structs, map array and hidden trap array to the file.
 */
}

void loadgame(){

    FILE *file = fopen("savefile.dat","rb");// because of we wrote already in here we open file for binary reading

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

    if(activePlayers<2 || activePlayers>3){ // validate before restoring
        printf("\n WARNING ! somthings wrong with the save file !!!\n");
        fclose(file);
        fflush(stdout);
        sleep(2);
        return;
    }

    fread(players, sizeof(player),activePlayers,file);
    fread(map, sizeof(map),1,file);
    fread(Traps, sizeof(Traps),1,file);
    fread(&roundCounter, sizeof(int),1,file);
    fclose(file);

    printf("\n");
    printf("===========================================\n");
    printf("              GAME FILE LOADING...          \n");
    printf("===========================================\n");

    fflush(stdout);
    sleep(2);//using sleep function so we can see the loading banner for 2 seconds

    gameloop();

/*
 > in this func we Reads and restores a previously saved game from savefile.dat.
 > and also Validates file existence and player count before restoring.
  then Jumps directly into gameloop() after successful load.
 */
}  


void addLog(char *message){
    snprintf(eventLog[logIndex],LOG_LENGTH,"[R%d] %s",roundCounter,message);

    logIndex = (logIndex+1)%LOG_SIZE;
    logCount++;
    /*
 >in here we  Adds a formatted event message to the circular log array.
 > Overwrites oldest entry when 100 entries are reached.
 > as the  Parameter we use message pointer : the event string to store
 */
}

void printRecentLog(){

    printf("\n");
    printf("  ===========================================\n");
    printf("                   EVENT LOG                 \n");
    printf("  ===========================================\n");
 
    // calculate how many entries to show
    int total = logCount < LOG_DISPLAY ? logCount : LOG_DISPLAY;

    if(total == 0){
        printf(" >>>>>        No events yet...         <<<<<<\n");
    }else{
        // find starting index of last 5 entries
        int start = (logIndex - total + LOG_SIZE) % LOG_SIZE;
       
        for(int i = 0; i < total; i++){
            int idx = (start + i) % LOG_SIZE;
            printf("     ||  %-44s||\n", eventLog[idx]);
        }
    }

   printf("  ===========================================\n");
   /*
  > using this function we Displays the 5 most recent event log entries below the map.
 > Calculates correct starting index accounting for circular wrap.
 */
}

void saveLog(){

    FILE *file = fopen("gamelog.txt", "w");// open as text file for writing

    if(file == NULL){
        printf("Error saving log!\n");
        return;
    }

    fprintf(file, "======= QUEST FOR THE LOST TREASURE =======\n");
    fprintf(file, "Total Rounds: %d\n", roundCounter);
    fprintf(file, "===========================================\n\n");

    // write all log entries in order
    int total = logCount < LOG_SIZE ? logCount : LOG_SIZE;
    int start = logCount < LOG_SIZE ? 0 : logIndex;// find oldest entry start point and assign it to start

    for(int i = 0; i < total; i++){
        int idx = (start + i) % LOG_SIZE;
        fprintf(file, "%s\n", eventLog[idx]);
    }

    fclose(file);
    printf("\n     Game log saved to gamelog.txt!\n");
    /*
 > Writes the entire event log to gamelog.txt when game ends.
 */
}

void showStats(){
     
    printf("\n");
    printf("     ||========================================================||\n");
    printf("     ||                   PLAYER STATISTICS                    ||\n");
    printf("     ||====================||==========||==========||==========||\n");
    printf("     || Statistic          ||");
     
    // this below loop prints each stat row across all players
    for(int i = 0; i < activePlayers; i++){
        printf(" %-8s ||", players[i].name);
    }
    printf("\n");
    printf("     ||====================||==========||==========||==========||\n");

    // moves
    printf("     || Moves Made         ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].moveMade);
    printf("\n");

    // treasures 
    printf("     || Treasures Found    ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].chestfound);
    printf("\n");

    // traps 
    printf("     || Traps Triggered    ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].traphit);
    printf("\n");

    // damage 
    printf("     || Damage Taken       ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].damageTaken);
    printf("\n");

    // health packs 
    printf("     || Health Packs Used  ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].healthPackUsed);
    printf("\n");

    // keys 
    printf("     || Keys Collected     ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].keysCollected);
    printf("\n");

    // doors unlocked
    printf("     || Doors Unlocked     ||");
    for(int i = 0; i < activePlayers; i++) printf(" %-8d ||", players[i].doorsUnlocked);
    printf("\n");

   printf("     ||========================================================||\n");

   /*
 > Displays a per-player statistics table after the leaderboard.
 > Shows moves made, treasures found, traps triggered,
    damage taken, health packs used, keys collected, doors unlocked.
 */
}