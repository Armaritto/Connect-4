// TODO LIST: all menus design - load game modification - save - Read Parameters xml - Top players
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define X 'X'
#define O 'O'

/// Global Variables
int rows=6;
int col=7;
int c=0;
int onePlayerCheck;
int shift = 0;
struct{
        int startTimeSec;
        int moveTimeSec;
        int moveTimeMin;
        int moveTimeHr;
} structTime;


/// Type Defined Structures
typedef struct{
    int score_x;
    int score_o;
}scores;

typedef struct{
    char name[256];
    int score;
    char color;
}info;


/// Prototypes
void printUI(int errors,char a[rows][col],info player1,info player2);
int start_new_game(char a[rows][col]);
int load_game(char a[rows][col]);
int top_players(char a[rows][col]);
int AI(char a[rows][col]);


/// Secondary Functions
void red(){
    printf("\033[1;31m");
}

void yellow(){
    printf("\033[1;33m");
}

void reset(){
    printf("\033[0m");
}

void openingGame(){
    system("cls");
    printf("\n\n\n\n");
    int center=6*col;
    for(int x=0; x<center; x++){
        printf(" ");
    }
    red();
    printf("  C");
    Sleep(200);
    yellow();
    printf(" o");
    Sleep(200);
    red();
    printf(" n");
    Sleep(200);
    yellow();
    printf(" n");
    Sleep(200);
    red();
    printf(" e");
    Sleep(200);
    yellow();
    printf(" c");
    Sleep(200);
    red();
    printf(" t");
    Sleep(200);
    yellow();
    printf("  4");
    Sleep(200);
    red();
    printf(" s  ");
    Sleep(800);
    reset();
}

void Loading(){
    system("cls");
    printf("\n\n\n\n");
    int center=6*col;
    for(int x=0; x<center; x++){
        printf(" ");
    }
    red();
    printf("  L");
    yellow();
    printf(" o");
    red();
    printf(" a");
    yellow();
    printf(" d");
    red();
    printf(" i");
    yellow();
    printf(" n");
    red();
    printf(" g");
    red();
    printf(" .");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    reset();
}

int Quit(){
    system("cls");
    printf("\n\n\n\n");
    int center=6*col;
    for(int x=0; x<center; x++){
        printf(" ");
    }
    red();
    printf("  C");
    yellow();
    printf(" l");
    red();
    printf(" o");
    yellow();
    printf(" s");
    red();
    printf(" i");
    yellow();
    printf(" n");
    red();
    printf(" g");
    red();
    printf(" .");
    Sleep(600);
    printf(".");
    Sleep(600);
    printf(".");
    Sleep(600);
    exit(0);
}

char update_piece(char piece){
    if(c%2==0)
    {
        piece = X;
    }
    else
    {
        piece = O;
    }
    return piece;
}

/// Main Functions

void Undo(char a[rows][col],char piece,int progress[rows*col],info player1,info player2){
    int onePlayer = -onePlayerCheck + 2;
    int errors=0;

    for(int k = 0; k <= onePlayer; k++)
    {
    int last_move_shown = progress[c-1];
    for (int i = 0; i < rows; i++)
      {
        if (a[i][last_move_shown] != ' ')
        {
            a[i][last_move_shown] = ' ';
            c--;
            shift++;
            break;
        }
      }
    piece = update_piece(piece);
    }

    system("cls");
    printUI(errors,a,player1,player2);

}

void Redo(char a[rows][col],char piece,int progress[rows*col],info player1,info player2){
    int onePlayer = -onePlayerCheck +2;
    int errors=0;
    int j;
    if (shift != 0)
    {

    for(int k = 0; k <= onePlayer; k++)
    {
      j = progress[c];
        for(int i=rows; i>=0; i--)
        {
            if(a[i][j] == ' ')
            {
                if(c%2 == 0)
                {
                    a[i][j] = X;
                }
                else
                {
                    a[i][j] = O;
                }
                break;
            }
        }
        c++;
        shift--;
    }
    piece = update_piece(piece);
    }
    system("cls");
    printUI(errors,a,player1,player2);

}

void mainMenu(char a[rows][col]){
    int center=6*col;
    char the_menu[1000];
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("   Connect 4s\n\n\n");
    center-=7;
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("=================================\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("       Choose from (1-4)       ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("|");
    red();
    printf("1.Start New Game               ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("2.Load Game                    ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("3.Top Player                   ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("4.Quit                         ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("=================================\n");
    reset();

    fgets(the_menu,1000,stdin);
    int j = atoi(the_menu);
    while(j<1||j>col||j==0)
    {
        system("cls");
        mainMenu(a);
    }
    switch(j)
    {
    case 1:
        system("cls");
        Loading();
        system("cls");
        start_new_game(a);
        break;
    case 2:
        system("cls");
        Loading();
        system("cls");
        load_game(a);
        break;
    /*case 3:
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

void startNewGameMenu(){
    int center=6*col;
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("   Connect 4s\n\n\n");
    center-=7;
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("=================================\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("       Choose from (1-3)       ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("|");
    red();
    printf("1.Play vs Computer             ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("2.Play vs Human                ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("3.Back                         ");
    yellow();
    printf("|\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    yellow();
    printf("=================================\n");
    reset();
}

scores count_4_Row(int m, int n, char arr[m][n]){

    scores score;

    int score_R = 0, score_Y = 0;
    char temp;
    void check_right(int row, int col)
    {
        int count_R = 0;
        int count_Y = 0;
        for(int i = 0; i < 4; i++)
            if(col + i < n)
            {
                temp = arr[row][col + i] ;
                if (temp == X)
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == O)
                {
                    count_Y++;
                    count_R = 0;
                }
                else
                {
                    count_Y = count_R = 0;
                    break;
                }
                if (count_R == 4)
                {
                    score_R++;
                }
                if (count_Y == 4)
                {
                    score_Y++;
                }
            }
    }

    void check_down(int row, int col)
    {
        int count_R = 0;
        int count_Y = 0;
        for(int i = 0; i < 4; i++)
            if(row + i < m)
            {
                temp = arr[row + i][col] ;
                if (temp == X)
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == O)
                {
                    count_Y++;
                    count_R = 0;
                }
                else
                {
                    count_Y = count_R = 0;
                    break;
                };
                if (count_R == 4)
                {
                    score_R++;
                };
                if (count_Y == 4)
                {
                    score_Y++;
                };
            }
    }

    void check_diagonal_right(int row, int col)
    {
        int count_R = 0;
        int count_Y = 0;
        for(int i = 0; i < 4; i++)
            if(row + i < m && col + i < n)
            {
                temp = arr[row + i][col + i] ;
                if (temp == X)
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == O)
                {
                    count_Y++;
                    count_R = 0;
                }
                else
                {
                    count_Y = count_R = 0;
                    break;
                };
                if (count_R == 4)
                {
                    score_R++;
                };
                if (count_Y == 4)
                {
                    score_Y++;
                };
            }
    }

    void check_diagonal_left(int row, int col)
    {
        int count_R = 0;
        int count_Y = 0;
        for(int i = 0; i < 4; i++)
            if(row + i < m && col - i >= 0)
            {
                temp = arr[row + i][col - i] ;
                if (temp == X)
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == O)
                {
                    count_Y++;
                    count_R = 0;
                }
                else
                {
                    count_Y = count_R = 0;
                    break;
                };
                if (count_R == 4)
                {
                    score_R++;
                };
                if (count_Y == 4)
                {
                    score_Y++;
                };
            }
    }
    for (int row = 0; row < m; row++)
    {
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

void printUI(int errors,char a[rows][col],info player1,info player2){
    int endGame = rows*col;
    int center = 6*col;
    int i,j,k=0; /// i~rows , j~columns , k~menu position
    int triScreen = rows/3; /// to print the menu in the 1st third of the board
    int farRight = (4*col)+1; /// to print the menu on the right
    char character1;
    int moves_X=0;
    int moves_O=0;


    if(c%2==0)
    {
        moves_X = c/2;
        moves_O = c/2;
    }
    else
    {
        moves_X = (c/2)+1;
        moves_O = c/2;
    }

    scores playerscore = count_4_Row(rows, col, a);

    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("Connect 4s\n\n");
    printf("\n+");
    for(j=0; j<col; j++)
    {
        printf("---+");
    }
    for(i=0; i<rows; i++)
    {
        printf("\n|");
        for(j=0; j<col; j++)
        {
            character1 = a[i][j];
            if(character1== X)
            {
                red();
                printf(" %c ",character1);
                reset();
                printf("|");
            }
            else if(character1== O)
            {
                yellow();
                printf(" %c ",character1);
                reset();
                printf("|");
            }
            else
            {
                printf(" %c ",character1);
                printf("|");
            }

        }
        if(k>=triScreen&&k<(triScreen+7))
        {
            for(int x=0; x<farRight; x++)
            {
                printf(" ");
            }
            if(k==triScreen)
            {
                if(c==endGame)
                {
                    printf("End Game!");
                }
                else
                {
                    if(c%2==0)
                    {
                        red();
                        printf("%s's Turn",player1.name);
                        reset();
                    }
                    else
                    {
                        yellow();
                        printf("%s's Turn",player2.name);
                        reset();
                    }
                }

            }
            else if(k==triScreen+1)
            {
                printf(" ");
            }
            else if(k==triScreen+2)
            {
                printf("%02d:%02d:%02d",structTime.moveTimeHr,structTime.moveTimeMin,structTime.moveTimeSec);
            }
            else if(k==triScreen+3)
            {
                printf(" ");
            }
            else if(k==triScreen+4)
            {
                printf("   Scores            %d Total moves",c);
            }
            else if(k==triScreen+5)
            {
                red();
                printf("%-17s",player1.name);
                printf(":%d     %d moves",playerscore.score_x,moves_X);
                reset();
            }
            else
            {
                yellow();
                printf("%-17s",player2.name);
                printf(":%d     %d moves",playerscore.score_o,moves_O);
                reset();
            }
        }
        k++;
        printf("\n+");
        for(j=0; j<col; j++)
        {
            printf("---+");
        }
        if(k>=triScreen&&k<(triScreen+7))
        {
            for(int x=0; x<farRight; x++)
            {
                printf(" ");
            }
            if(k==triScreen)
            {
                if(c%2==0)
                {
                    if(c==endGame)
                    {
                        printf("End Game!");
                    }
                    else
                    {
                        if(c%2==0)
                        {
                            red();
                            printf("Player 1's Turn");
                            reset();
                        }
                        else
                        {
                            yellow();
                            printf("Player 2's Turn");
                            reset();
                        }
                    }
                }
            }
            else if(k==triScreen+1)
            {
                printf(" ");
            }
            else if(k==triScreen+2)
            {
                printf("%02d:%02d:%02d",structTime.moveTimeHr,structTime.moveTimeMin,structTime.moveTimeSec);
            }
            else if(k==triScreen+3)
            {
                printf(" ");
            }
            else if(k==triScreen+4)
            {
                printf("   Scores           %d Total moves",c);
            }
            else if(k==triScreen+5)
            {
                red();
                printf("%-17s",player1.name);
                printf(":%d     %d moves",playerscore.score_x,moves_X);
                reset();
            }
            else
            {
                yellow();
                printf("%-17s",player2.name);
                printf(":%d     %d moves",playerscore.score_o,moves_O);
                reset();
            }
        }
        k++;
    }
    printf("\n  ");

    for(i=1; i<=col; i++) /// i is column counter viewer
    {
        printf("%02d  ",i);
    }
    farRight +=21;
    printf("\n\nChoose from (1 to %d)",col);

    printf("      'U' for Undo / 'R' for Redo / 'S' for Save / 'Q' for Quit");

    switch(errors)
    {
    case 0:
        printf("\n");
        break;
    case 1:
        printf("\nERROR! Enter from (1 to %d)\n",col);
        break;
    case 2:
        printf("\nColumn is filled, choose another column\n");
        break;
    }
}

int fillBoard(char a[rows][col],char piece,int progress[rows*col],info player1,info player2){
    int i,j,check=0,errors=0;
    char character[1000];
    while(check==0)
    {
        int saveCheck=0;

        if(onePlayerCheck==1 && c%2==1)
        {
            j = AI(a);
        }
        else
        {
            fgets(character,1000,stdin);
            j = atoi(character);
        }
        while(j<1||j>col||j==0)
        {
            if(character[0] == 'u'||character[0] == 'U')
            {
                if(c!=0){
                    Undo(a,piece,progress,player1,player2);
                }
                else{
                    system("cls");
                    printUI(errors,a,player1,player2);
                }
                    fgets(character,1000,stdin);
                    j = atoi(character);

            }
            else if(character[0] == 'r'||character[0] == 'R')
            {
                Redo(a,piece,progress,player1,player2);
                fgets(character,1000,stdin);
                j = atoi(character);
            }
            /*else if(character == 's'||character == 'S'){
                saveCheck = 1;
                Save();
            }*/
            else if(character[0] == 'q'||character[0] == 'Q')
            {
                if(saveCheck==0)
                {
                    system("cls");
                    printf("Unsaved game\nDo you want to save\n1.Save\n2.Don't Save\n");
                    int save_choice;
                    scanf("%d",&save_choice);
                    if(save_choice==1)
                    {
                        //save();
                    }
                }
                Quit();
            }
            else
            {
                system("cls");
                errors = 1;
                printUI(errors,a,player1,player2);
                fgets(character,1000,stdin);
                j = atoi(character);
            }
        }
        for(i=rows; i>=0; i--)
        {
            if(a[i][j-1] == ' ')
            {
                piece = update_piece(piece);
                a[i][j-1] = piece;
                check=1;
                progress[c] = j-1;
                shift = 0;
                c++;
                break;
            }
        }
        if(check==0)
        {
            system("cls");
            errors = 2;
            printUI(errors,a,player1,player2);
        }
    }
    return 0;
}

int start_new_game(char a[rows][col]){
    info player1;
    info player2;
    int progress[rows*col];
    int errors=0;
    char piece;
    char ppp[1000];

    startNewGameMenu();
    fgets(ppp,1000,stdin);
    int read = atoi(ppp);
    if(read == 3){ ///back
        system("cls");
        mainMenu(a);
    }
    onePlayerCheck = read;
    system("cls");
    if(onePlayerCheck==2){

        printf("\n\n\n\n");
        int center=6*col;
        for(int x=0; x<center; x++){
            printf(" ");
        }
        red();
        printf("Enter Player 1 Name: ");
        fgets(player1.name,256,stdin);
        yellow();
        for(int x=0; x<center; x++){
            printf(" ");
        }
        printf("Enter Player 2 Name: ");
        fgets(player2.name,256,stdin);
        reset();
        player1.name[strlen(player1.name)-1]='\0';
        player2.name[strlen(player2.name)-1]='\0';
    }
    else{

        printf("\n\n\n\n");
        int center=6*col;
        for(int x=0; x<center; x++){
            printf(" ");
        }
        red();
        printf("Enter Your Name: ");
        fgets(player1.name,256,stdin);
        reset();
        player1.name[strlen(player1.name)-1]='\0';
        strcpy(player2.name,"Computer");
    }
    Loading();
    system("cls");
    for(int c=0; c<rows; c++){
        for(int b=0; b<col; b++){
            a[c][b] = ' ';
        }
    }
    c=0;
    structTime.startTimeSec = time(NULL);
    printUI(errors,a,player1,player2);
    int endGame = rows*col;
    while(c<endGame)
    {
        if(c%2==0)
        {
            piece = X;
            fillBoard(a,piece,progress,player1,player2);
            system("cls");
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec)%60;
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            printUI(errors,a,player1,player2);
        }
        else
        {
            piece = O;
            fillBoard(a,piece,progress,player1,player2);
            system("cls");
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec)%60;
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            printUI(errors,a,player1,player2);
        }
    }

    scores playerscore = count_4_Row(rows, col, a);
    if(playerscore.score_x>playerscore.score_o)
    {
        red();
        printf("%s is winner\n\n",player1.name);
        reset();
    }
    else if(playerscore.score_x<playerscore.score_o)
    {
        yellow();
        printf("%s is winner\n\n",player2.name);
        reset();
    }
    else
    {
        printf("Draw\n\n");
    }
    printf("Press Enter to return to main menu");
    getchar();
    system("cls");
    mainMenu(a);
    return 0;
}

int load_game(char a[rows][col]){ ///did not add struct
    info player1;
    info player2;
    int progress[rows*col];
    char piece;
    int errors=0;
    int currentGame;
    system("cls");
    printf("Choose a game(1-3)\n");
    scanf("%d",&currentGame);
    if(currentGame==2)
    {
        c=29; ///read c and array
        int b[6][7]=
        {
            {'O',' ',' ',' ',' ',' ',' '},
            {'O',' ',' ',' ',' ',' ','X'},
            {'O','X',' ','X',' ','X','X'},
            {'O','X','X','X','X','X','X'},
            {'O','O','O','O','O','X','X'},
            {'O','X','O','X','X','X','X'}
        };
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<col; j++)
            {
                a[i][j]=b[i][j];
            }
        }
    }
    else if(currentGame==3)
    {
        c=29;
        int b[6][7]=
        {
            {'X',' ',' ',' ',' ',' ',' '},
            {'X',' ',' ',' ',' ',' ','X'},
            {'X','X',' ','X',' ','X','X'},
            {'X','X','X','X','X','X','X'},
            {'X','O','O','O','O','X','X'},
            {'X','X','O','X','X','X','X'}
        };
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<col; j++)
            {
                a[i][j]=b[i][j];
            }
        }
    }
    else
    {
        c=18;
        int b[6][7]=
        {
            {' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' '},
            {' ','X',' ','X',' ','X',' '},
            {' ','X','X','X','X','X',' '},
            {' ','O','O','O','O','X',' '},
            {' ','X','O','X','X','X',' '}
        };
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<col; j++)
            {
                a[i][j]=b[i][j];
            }
        }
    }


    printUI(errors,a,player1,player2);
    ///c = moves;
    int endGame=rows*col;
    while(c<endGame)
    {
        if(c%2==0)
        {
            piece = X;
            fillBoard(a,piece,progress,player1,player2);
            system("cls");
            printUI(errors,a,player1,player2);
        }
        else
        {
            piece = O;
            fillBoard(a,piece,progress,player1,player2);
            system("cls");
            printUI(errors,a,player1,player2);
        }
    }

    scores playerscore = count_4_Row(rows, col, a);
    if(playerscore.score_x>playerscore.score_o)
    {
        red();
        printf("Player 1 is winner\n\n");
        reset();
    }
    else if(playerscore.score_x<playerscore.score_o)
    {
        yellow();
        printf("Player 2 is winner\n\n");
        reset();
    }
    else
    {
        printf("Draw\n\n");
    }
    printf("Press Enter to return to main menu");
    getchar();
    system("cls");
    mainMenu(a);
    return 0;
}

int AI(char a[rows][col]){
    time_t t;
    srand((unsigned) time(&t));
    int size = 7;
    int available[size];
    for(int i=0; i<size; i++)
    {
        available[i]=i+1;
    }
    int empty=0;
    while(empty<size)
    {
        if(a[0][available[empty]-1]!= ' ')
        {
            available[empty] = available[size-1];
            size--;
            empty=0;
        }
        else
        {
            empty++;
        }
    }

    Sleep(500);
    int rv = (rand() % size);

    return available[rv];
}


/// main
int main(void){
    char a[rows][col];
    openingGame();
    system("cls");
    mainMenu(a);
}

