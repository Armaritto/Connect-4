#include <stdio.h>
#include <stdlib.h>
#define X 'X'
#define O 'O'

int rows=20;
int col=20;
char a[20][20];
int piece;

typedef struct{
    int score_x;
    int score_o;
}scores;

scores count_4_Row(int m, int n, char arr[m][n]){

   scores score;

   int score_R = 0, score_Y = 0;
   char temp;
   //////////////////////////////////////////////////////////////////////
   void check_right(int row, int col)
{
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
            printf(" %c |",character1);
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
                printf("Player1 : %d",playerscore.score_x);
            }
            else{
                printf("Player2 : %d",playerscore.score_o);
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
                printf("Player1 : 40");
            }
            else{
                printf("Player2 : 15");
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

    printf("       Ctrl-Z for Undo / Ctrl-Y for Redo / Ctrl-S for Save / Esc for Quit\n");

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
            system("cls");
            errors = 1;
            printUI(errors);
            fgets(character,1000,stdin);
            j = atoi(character);
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

int main(){
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

