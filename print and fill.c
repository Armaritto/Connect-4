#include <stdio.h>
#include <stdlib.h>

int rows=5;
int col=7;
char a[5][7];



void printUI(){
    int i,j,k=0; /// i~rows , j~columns , k~menu position
    int triScreen = rows/3; /// to print the menu in the 1st third of the board
    int farRight = (4*col)+1; /// to print the menu on the right
    char character1;

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
}

int fillBoard(){ ///prameter is needed

    int i,j,check=0;
    int character;
    while(check==0){
        scanf("%d",&character);
        j = character;

            for(i=rows;i>=0;i--){
                if(a[i][j-1] == ' '){
                    a[i][j-1] = 'O';
                    check = 1;
                    break;
                }
            }
        if(check==0){
            printf("Column %02d is filled, choose another column");

        }
    }

    return 0;
}

int main(){

    for(int c=0;c<rows;c++){
        for(int b=0;b<col;b++){
            a[c][b] = ' ';
        }
    }
    printUI();
    fillBoard();
    system("cls");
    printUI();
    return 0;
}
