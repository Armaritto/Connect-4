#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int rows=6;
int col=7;
char a[6][7];
int piece;

typedef struct{
    int hours;
    int minutes;
    int seconds;
    } digital_clock;

void printUI(int errors){
    int i,j; /// i~rows , j~columns , k~menu position
    int triScreen = rows/3; /// to print the menu in the 1st third of the board
    int farRight; /// to print the menu on the right
    char character1;
    digital_clock clock1;
    clock1.hours = 0;
    clock1.minutes = 0;
    clock1.seconds = 0;

    while(1) {
    int k=0;
    farRight = (4*col)+1;
    system("cls");
       if(clock1.seconds == 60){
           clock1.minutes += 1;
           clock1.seconds = 0;
       }
       if(clock1.minutes == 60){
           clock1.hours += 1;
           clock1.minutes = 0;
       }
       if(clock1.hours == 24){
           clock1.hours = 0;
           clock1.minutes = 0;
           clock1.seconds = 0;
       }

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
                printf("5 moves         %02d:%02d:%02d",clock1.hours,clock1.minutes,clock1.seconds);
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
            printf("\nERROR! Enter from (1 to %d)",col);
            break;
        case 2:
            printf("\nColumn is filled, choose another column");
            break;
    }
    clock1.seconds++;
    sleep(1);
    }
}

int fillBoard(){

    int i,j,check=0,errors=0;
    int character;
    while(check==0){

        scanf("%d",&character);
        while(character<1||character>col){
            system("cls");
            errors = 1;
            printUI(errors);
            scanf("%d",&character);
        }

        j = character; /// Type casting

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
        if(c%2==0){ /// not complete
            piece = 'X';
            fillBoard();
            system("cls");
            printUI(errors);
        }
        else{ /// not complete
            piece = 'O';
            fillBoard();
            system("cls");
            printUI(errors);
        }
    }
    return 0;
}
