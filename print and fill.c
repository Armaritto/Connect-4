#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define X 'X'
#define O 'O'

int rows=6;
int col=7;
char a[6][7];
int piece;

typedef struct{
    int score_x;
    int score_o;
}scores;

void Loading(){
    printf("Loading.");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
}

void mainMenu(){
    char the_menu[1000];
    printf("Choose form (1-4)");
    printf("\n1.Start New Game");
    printf("\n2.Load Game");
    printf("\n3.Top Players");
    printf("\n4.Quit\n");

    fgets(the_menu,1000,stdin);
    int j = atoi(the_menu);
    while(j<1||j>col||j==0){
        printf("\nERROR! Enter from (1 to 4)\n");
        fgets(the_menu,1000,stdin);
        j = atoi(the_menu);
    }
    switch(j){
        case 1:
            system("cls");
            Loading();
            system("cls");
            start_new_game();
            break;
        /*case 2:
            system("cls");
            Loading();
            system("cls");
            load_game();
            break;
        case 3:
            system("cls");
            Loading();
            system("cls");
            top_players();
            break;*/
        case 4:
            system("cls");
            Quit();
            break;
    }

}
void red () {
  printf("\033[1;31m");
}

void yellow () {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}   


void Quit(){
    printf("Quitting.");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    exit(0);
}

scores count_4_Row(int m, int n, char arr[m][n]){

   scores score;

   int score_R = 0, score_Y = 0;
   char temp;
   //////////////////////////////////////////////////////////////////////
   void check_right(int row, int col){
     int count_R = 0; int count_Y = 0;
            for(int i = 0; i < 4; i++)
                if(col + i < n)
            {
            temp = arr[row][col + i] ;
            if (temp == X) {count_R++; count_Y = 0;}
            else if(temp == O){count_Y++; count_R = 0;}
            else {count_Y = count_R = 0; break;};
            if (count_R == 4) {score_R++;}; if (count_Y == 4) {score_Y++;};
            }
}

   //////////////////////////////////////////////////////////////////////
   void check_down(int row, int col)
{
     int count_R = 0; int count_Y = 0;
            for(int i = 0; i < 4; i++)
                if(row + i < m)
            {
            temp = arr[row + i][col] ;
            if (temp == X) {count_R++; count_Y = 0;}
            else if(temp == O){count_Y++; count_R = 0;}
            else {count_Y = count_R = 0; break;};
            if (count_R == 4) {score_R++;}; if (count_Y == 4) {score_Y++;};
            }
}

   ///////////////////////////////////////////////////////////////////////
   void check_diagonal_right(int row, int col)
{
     int count_R = 0; int count_Y = 0;
            for(int i = 0; i < 4; i++)
                if(row + i < m && col + i < n)
            {
            temp = arr[row + i][col + i] ;
            if (temp == X) {count_R++; count_Y = 0;}
            else if(temp == O){count_Y++; count_R = 0;}
            else {count_Y = count_R = 0; break;};
            if (count_R == 4) {score_R++;}; if (count_Y == 4) {score_Y++;};
            }
}

   ///////////////////////////////////////////////////////////////////////
    void check_diagonal_left(int row, int col)
{
     int count_R = 0; int count_Y = 0;
            for(int i = 0; i < 4; i++)
                if(row + i < m && col - i >= 0)
            {
            temp = arr[row + i][col - i] ;
            if (temp == X) {count_R++; count_Y = 0;}
            else if(temp == O){count_Y++; count_R = 0;}
            else {count_Y = count_R = 0; break;};
            if (count_R == 4) {score_R++;}; if (count_Y == 4) {score_Y++;};
            }
}

   ///////////////////////////////////////////////////////////////////////

    for (int row = 0; row < m; row++){
        for (int col = 0; col < n; col++)
        {

        check_right(row, col);
        check_down(row, col);
        check_diagonal_right(row, col);
        check_diagonal_left(row, col);

        }
    }
    score.score_x = score_R;
    score.score_o = score_Y;
    return score;
}


void printUI(int errors){
    int i,j,k=0; /// i~rows , j~columns , k~menu position
    int triScreen = rows/3; /// to print the menu in the 1st third of the board
    int farRight = (4*col)+1; /// to print the menu on the right
    char character1;

    scores playerscore = count_4_Row(rows, col, a);

    printf("\n\n+");
    for(j=0;j<col;j++){
        printf("---+");
    }
    for(i=0;i<rows;i++){
        printf("\n|");
        for(j=0;j<col;j++){
            character1 = a[i][j];
            if(character1=='X'){
                red();
                printf(" %c ",character1);
                reset();
                printf("|");
            }
            else if(character1=='O'){
                yellow();
                printf(" %c ",character1);
                reset();
                printf("|");
            }
            else{
                printf(" %c ",character1);
                printf("|");
            }

        }
        if(k>=triScreen&&k<(triScreen+7)){
            for(int x=0;x<farRight;x++){
                printf(" ");
            }
            if(k==triScreen){
                printf("   Player name Turn");
            }
            else if(k==triScreen+1){
                printf(" ");
            }
            else if(k==triScreen+2){
                printf("5 moves         00:00:00");
            }
            else if(k==triScreen+3){
                printf(" ");
            }
            else if(k==triScreen+4){
                printf("   Scores");
            }
            else if(k==triScreen+5){
                red();
                printf("Player1 : %d",playerscore.score_x);
                reset();
            }
            else{
                yellow();
                printf("Player2 : %d",playerscore.score_o);
                reset();
            }
        }
        k++;
        printf("\n+");
        for(j=0;j<col;j++){
            printf("---+");
        }
        if(k>=triScreen&&k<(triScreen+7)){
            for(int x=0;x<farRight;x++){
                printf(" ");
            }
            if(k==triScreen){
                printf("Player name Turn");
            }
            else if(k==triScreen+1){
                printf(" ");
            }
            else if(k==triScreen+2){
                printf("5 moves                00:00:00");
            }
            else if(k==triScreen+3){
                printf(" ");
            }
            else if(k==triScreen+4){
                printf("   Scores");
            }
            else if(k==triScreen+5){
                red();
                printf("Player1 : %d",playerscore.score_x);
                reset();
            }
            else{
                yellow();
                printf("Player2 : %d",playerscore.score_o);
                reset();
            }
        }
        k++;
    }
    printf("\n  ");

    for(i=1;i<=col;i++){ /// i is column counter viewer
        printf("%02d  ",i);
    }
    farRight +=21;
    printf("\n\nChoose from (1 to %d)",col);

    printf("      'U' for Undo / 'R' for Redo / 'S' for Save / 'Q' for Quit\n");

    switch(errors){
        case 1:
            printf("\nERROR! Enter from (1 to %d)\n",col);
            break;
        case 2:
            printf("\nColumn is filled, choose another column\n");
            break;
    }
}

int fillBoard(){

    int i,j,check=0,errors=0;
    char character[1000];
    while(check==0){

        fgets(character,1000,stdin);
        j = atoi(character);

        while(j<1||j>col||j==0){
           /* if(character == 'u'||character == 'U'){
                Undo();
            }
            else if(character == 'r'||character == 'R'){
                Redo();
            }
            else if(character == 's'||character == 'S'){
                Save();
            }
            else*/ if(character[0] == 'q'||character[0] == 'Q'){
                Quit();
            }
            else{
                system("cls");
                errors = 1;
                printUI(errors);
                fgets(character,1000,stdin);
                j = atoi(character);
            }
        }
            for(i=rows;i>=0;i--){
                if(a[i][j-1] == ' '){
                    a[i][j-1] = piece;
                    check = 1;
                    break;
                }
            }
        if(check==0){
            system("cls");
            errors = 2;
            printUI(errors);
        }
    }
    return 0;
}

int start_new_game(){
    int errors=0;
    for(int c=0;c<rows;c++){
        for(int b=0;b<col;b++){
            a[c][b] = ' ';
        }
    }
    printUI(errors);
    int endGame = rows*col;
    for(int c=0;c<endGame;c++){
        if(c%2==0){
            piece = X;
            fillBoard();
            system("cls");
            printUI(errors);
        }
        else{
            piece = O;
            fillBoard();
            system("cls");
            printUI(errors);
        }
    }


    return 0;
}


int main(){
    mainMenu();
    return 0;
}

