// TODO LIST: Load game modification - save - 3 times failed xml - global struct variable Line 228
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

/// Global Variables
int rows;
int col;
int c=0;
int shift = 0;
int loaded;
struct
{
    int startTimeSec;
    int moveTimeSec;
    int moveTimeMin;
    int moveTimeHr;
} structTime;

/// Type Defined Structures
typedef struct
{
    int score_x;
    int score_o;
} scores;

typedef struct
{
    char name[256];
    int score;
    char color;
    int nMoves;
} info;

typedef struct
{
    int height;
    int width;
    int highscores;
    int corrupted;
} parameters;

typedef struct
{
    int rows;
    int col;
    info player1;
    info player2;
    int onePlayerCheck;
    int c;
    int shift;
    int progress[1000];
    int moveTime;
} state;

/// Prototypes
parameters parametersInXml();
void printUI(int errors,char a[rows][col],info player1,info player2);
int start_new_game();
int load_game();
int top_players();
int AI(char a[rows][col]);

/// Secondary Functions
void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void reset()
{
    printf("\033[0m");
}

void gotoxy(int xAxis,int yAxis)
{
    COORD c;
    c.X = xAxis;
    c.Y = yAxis;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void openingGame()
{
    system("cls");
    printf("\n\n\n\n");
    int center=42;
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }

    char connect4s[] = "Connect 4s";
    for(int i=0; i<strlen(connect4s); i++)
    {
        if(i%2==0)
        {
            red();
            printf(" %c",connect4s[i]);
            Sleep(200);
        }
        else
        {
            yellow();
            printf(" %c",connect4s[i]);
            Sleep(200);
        }
    }
    reset();
    Sleep(500);
}

void Loading()
{
    system("cls");
    printf("\n\n\n\n");
    int center=42;
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }

    char Loading[] = "Loading";
    for(int i=0; i<strlen(Loading); i++)
    {
        if(i%2==0)
        {
            red();
            printf(" %c",Loading[i]);
        }
        else
        {
            yellow();
            printf(" %c",Loading[i]);
        }
    }
    printf(" ");
    red();
    for(int i=0; i<3; i++)
    {
        Sleep(500);
        printf(".");
    }
    reset();
    Sleep(500);
}

int Quit()
{
    system("cls");
    printf("\n\n\n\n");
    int center=42;
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }

    char quitting[] = "Quitting";
    for(int i=0; i<strlen(quitting); i++)
    {
        if(i%2==0)
        {
            red();
            printf(" %c",quitting[i]);
        }
        else
        {
            yellow();
            printf(" %c",quitting[i]);
        }
    }
    printf(" ");
    red();
    for(int i=0; i<3; i++)
    {
        Sleep(500);
        printf(".");
    }
    reset();
    Sleep(500);
    exit(0);
}

char update_piece(char piece)
{
    if(c%2==0)
    {
        piece = 'X';
    }
    else
    {
        piece = 'O';
    }
    return piece;
}

struct highScoreStructs
{
    int storedScore;
    char name[256];
};

void sortByScore(struct highScoreStructs Ranked[],int n)
{

    int i,j;
    struct highScoreStructs temp;

    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(Ranked[i].storedScore < Ranked[j].storedScore )
            {
                temp = Ranked[i];
                Ranked[i] = Ranked[j];
                Ranked[j] = temp;
            }
        }
    }

}

/// Main Functions
struct highScoreStructs ranked[10];

void save(int rows, int col, int progress[rows*col],info player1,info player2,int onePlayerCheck)
{
    state savedGames[3];
    FILE *in;
    in = fopen("savedGames.bin", "rb");
    fread(&savedGames, sizeof(savedGames), 1, in);
    fclose(in);
    if (!loaded)
    {
        state temp;
        temp = savedGames[2];
        savedGames[2] = savedGames[1];
        savedGames[1] = savedGames[0];
        savedGames[0] = temp;

    }


    if (loaded == 0 || loaded == 1)
    {

        savedGames[0].rows= rows;
        savedGames[0].col = col;
        savedGames[0].player1 = player1;
        savedGames[0].player2 = player2;
        savedGames[0].onePlayerCheck = onePlayerCheck;
        savedGames[0].c = c;
        savedGames[0].shift = shift;
        savedGames[0].moveTime = structTime.moveTimeSec;
        for (int i = 0; i < c + shift; i++)
        {
            savedGames[0].progress[i] = progress[i];
        }
    }
    else if(loaded == 2)
    {
        savedGames[1].rows= rows;
        savedGames[1].col = col;
        savedGames[1].player1 = player1;
        savedGames[1].player2 = player2;
        savedGames[1].onePlayerCheck = onePlayerCheck;
        savedGames[1].c = c;
        savedGames[1].shift = shift;
        savedGames[1].moveTime = structTime.moveTimeSec;
        for (int i = 0; i < c + shift; i++)
        {
            savedGames[1].progress[i] = progress[i];
        }
    }
    else
    {
        savedGames[2].rows= rows;
        savedGames[2].col = col;
        savedGames[2].player1 = player1;
        savedGames[2].player2 = player2;
        savedGames[2].onePlayerCheck = onePlayerCheck;
        savedGames[2].c = c;
        savedGames[2].shift = shift;
        savedGames[2].moveTime = structTime.moveTimeSec;
        for (int i = 0; i < c + shift; i++)
        {
            savedGames[2].progress[i] = progress[i];
        }
    }


    FILE *out;
    out = fopen("savedGames.bin", "wb");
    fwrite(&savedGames, sizeof(savedGames), 1, out);
    fclose(out);

}

void Undo(char a[rows][col],char piece,int progress[rows*col],info player1,info player2,int onePlayerCheck)
{
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

void Redo(char a[rows][col],char piece,int progress[rows*col],info player1,info player2,int onePlayerCheck)
{
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
                        a[i][j] = 'X';
                    }
                    else
                    {
                        a[i][j] = 'O';
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

void mainMenu()
{
    loaded=0;
    int center=42;
    char the_menu[1000];
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("\e[1;94m");
    printf("   Connect 4s\n\n\n");
    reset();
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
    while(j<1||j>4||j==0)
    {
        system("cls");
        mainMenu();
    }
    switch(j)
    {
    case 1:
        system("cls");
        Loading();
        system("cls");
        start_new_game();
        break;
    case 2:
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
        break;
    case 4:
        system("cls");
        Quit();
        break;
    }

}

void startNewGameMenu()
{
    int center=42;
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("\e[1;94m");
    printf("   Connect 4s\n\n\n");
    reset();
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

int corruptedMenu()
{
    system("cls");
    int center = 42;
    printf("\n\n\n\n\a");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    red();
    printf("      Parameters File is Corrupted!\n");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    yellow();
    printf("1.To skip and go with default parameters\n");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("         2.To Enter file's path\n");
    reset();
    int checkers;
    char checker[256];
    fgets(checker,256,stdin);
    checkers = atoi(checker);
    if(checkers == 1)
    {
        system("cls");
        return -1;
    }
    else if(checkers == 2)
    {
        system("cls");
        return -5;
    }
}

int error404()
{
    system("cls");
    int center = 42;
    printf("\n\n\n\n\a");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    red();
    printf("        Error 404 File Not Found!\n");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    yellow();
    printf("1.To skip and go with default parameters\n");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("         2.To Enter file's path\n");
    reset();
    int checkers;
    char checker[256];
    fgets(checker,256,stdin);
    checkers = atoi(checker);
    if(checkers == 1)
    {
        system("cls");
        return -1;
    }
    else if(checkers == 2)
    {
        system("cls");
        return -5;
    }
}

scores count_4_Row(int m, int n, char arr[m][n])
{
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
                if (temp == 'X')
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == 'O')
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
                if (temp == 'X')
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == 'O')
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
                if (temp == 'X')
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == 'O')
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
                if (temp == 'X')
                {
                    count_R++;
                    count_Y = 0;
                }
                else if(temp == 'O')
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

void printBoard(char a[rows][col])
{
    char character;
    printf("\n\n");
    printf("\n+");
    for(int j=0; j<col; j++)
    {
        printf("---+");
    }
    for(int i=0; i<rows; i++)
    {
        printf("\n|");
        for(int j=0; j<col; j++)
        {
            character = a[i][j];
            if(character== 'X')
            {
                red();
                printf(" %c ",character);
                reset();
                printf("|");
            }
            else if(character== 'O')
            {
                yellow();
                printf(" %c ",character);
                reset();
                printf("|");
            }
            else
            {
                printf(" %c ",character);
                printf("|");
            }
        }
        printf("\n+");
        for(int j=0; j<col; j++)
        {
            printf("---+");
        }
    }
}

void printUI(int errors,char a[rows][col],info player1,info player2)
{

    int endGame = rows*col;
    player1.color='X';
    player2.color='O';
    player1.nMoves=0;
    player2.nMoves=0;

    if(c%2==0)
    {
        player1.nMoves = c/2;
        player2.nMoves = c/2;
    }
    else
    {
        player1.nMoves = (c/2)+1;
        player2.nMoves = c/2;
    }

    scores playerscore = count_4_Row(rows, col, a);
    player1.score = playerscore.score_x;
    player2.score = playerscore.score_o;

    printBoard(a);
    int space= (col*4)+20;
    int center= ((col*4)+50)/2;
    gotoxy(center,0);
    printf("\e[1;94m");
    printf("Connect 4s");
    reset();
    gotoxy(space,7);

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

    gotoxy(space,9);
    printf("Time: %02d:%02d:%02d",structTime.moveTimeHr,structTime.moveTimeMin,structTime.moveTimeSec);
    gotoxy(space,11);
    printf("   Scores            %d Total moves",c);
    gotoxy(space,13);
    red();
    printf("%-17s",player1.name);
    printf(":%d     %d moves",player1.score,player1.nMoves);
    reset();
    yellow();
    gotoxy(space,14);
    printf("%-17s",player2.name);
    printf(":%d     %d moves",player2.score,player2.nMoves);
    reset();
    gotoxy(0,rows*2+3);
    printf("\n  ");
    for(int i=1; i<=col; i++) /// i is column counter viewer
    {
        printf("%02d  ",i);
    }
    printf("\e[1;94m");
    printf("\n\nChoose from (1 to %d)",col);

    printf("      'U' for Undo / 'R' for Redo / 'S' for Save / 'M' for Main Menu / 'Q' for Quit ");
    reset();
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

int fillBoard(char a[rows][col],char piece,int progress[rows*col],info player1,info player2,int onePlayerCheck)
{
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
                if(c!=0)
                {
                    Undo(a,piece,progress,player1,player2,onePlayerCheck);
                }
                else
                {
                    system("cls");
                    printUI(errors,a,player1,player2);
                }
                fgets(character,1000,stdin);
                j = atoi(character);

            }
            else if(character[0] == 'r'||character[0] == 'R')
            {
                Redo(a,piece,progress,player1,player2,onePlayerCheck);
                fgets(character,1000,stdin);
                j = atoi(character);
            }
            else if(character[0] == 'm'||character[0] == 'M')
            {
                system("cls");
                mainMenu();
            }
            else if(character[0] == 's'||character[0] == 'S')
            {
                saveCheck = 1;
                save(rows,col,progress,player1,player2,onePlayerCheck);
                fgets(character,1000,stdin);
                j = atoi(character);
            }
            else if(character[0] == 'q'||character[0] == 'Q')
            {
                if(saveCheck==0)
                {
                    int center= ((col*4)+50)/2;
                    system("cls");
                    red();
                    gotoxy(center,4);
                    printf("   Unsaved game");
                    gotoxy(center,5);
                    printf("Do you want to save");
                    yellow();
                    gotoxy(center,7);
                    printf("      1.Save");
                    gotoxy(center,8);
                    printf("   2.Don't Save");
                    int save_choice;
                    scanf("%d",&save_choice);
                    if(save_choice==1)
                    {
                        save(rows,col,progress,player1,player2,onePlayerCheck);
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

int start_new_game()
{
    parameters gameparameters;
    info player1;
    info player2;
    int defaultValueReference;
    char gameFileParametersName[] = "Game Parameters.xml";
    gameparameters = parametersInXml(gameFileParametersName);
    while(gameparameters.corrupted==1 || gameparameters.corrupted==2)
    {
        if(gameparameters.corrupted==1)
        {
            defaultValueReference = corruptedMenu();
        }
        else if(gameparameters.corrupted==2)
        {
            defaultValueReference = error404();
        }
        if(defaultValueReference == -1)
        {
            char defaultFileParametersName[] = "Default Parameters.xml";
            gameparameters = parametersInXml(defaultFileParametersName);
        }
        else if(defaultValueReference == -5)
        {
            char gameFileParametersName2[256];
            system("cls");
            yellow();
            printf("Enter file's path\n");
            gets(gameFileParametersName2);

            for(int i=0; i<strlen(gameFileParametersName2); i++)
            {
                if(gameFileParametersName2[i]=='\\')
                {
                    gameFileParametersName2[i] = '/';
                }
            }


            strcpy(gameFileParametersName,gameFileParametersName2);
        }
        gameparameters = parametersInXml(gameFileParametersName);
        system("cls");
    }


    struct highScoreStructs highstruct1;

    rows = gameparameters.height;
    col = gameparameters.width;
    int maxScores = gameparameters.highscores;

    char a[rows][col];
    int progress[rows*col];
    int errors=0;
    char piece;
    char ppp[1000];
    startNewGameMenu();
    fgets(ppp,1000,stdin);
    int read = atoi(ppp);
    if(read == 3)  ///back
    {
        system("cls");
        mainMenu();
    }
    int onePlayerCheck = read;
    system("cls");
    if(onePlayerCheck==2)
    {

        printf("\n\n\n\n");
        int center=42;
        for(int x=0; x<center; x++)
        {
            printf(" ");
        }
        red();
        printf("Enter Player 1 Name: ");
        fgets(player1.name,256,stdin);
        yellow();
        for(int x=0; x<center; x++)
        {
            printf(" ");
        }
        printf("Enter Player 2 Name: ");
        fgets(player2.name,256,stdin);
        reset();
        player1.name[strlen(player1.name)-1]='\0';
        player2.name[strlen(player2.name)-1]='\0';
    }
    else
    {

        printf("\n\n\n\n");
        int center=42;
        for(int x=0; x<center; x++)
        {
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
    for(int c=0; c<rows; c++)
    {
        for(int b=0; b<col; b++)
        {
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
            piece = 'X';
            fillBoard(a,piece,progress,player1,player2,onePlayerCheck);
            system("cls");
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec);
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            structTime.moveTimeSec %= 60;
            printUI(errors,a,player1,player2);
        }
        else
        {
            piece = 'O';
            fillBoard(a,piece,progress,player1,player2,onePlayerCheck);
            system("cls");
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec);
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            structTime.moveTimeSec %= 60;
            printUI(errors,a,player1,player2);
        }
    }

    scores playerscore = count_4_Row(rows, col, a);
    struct highScoreStructs TopRankedArrayofStructs[maxScores];
    printf("\n");


    if(playerscore.score_x>playerscore.score_o)
    {
        red();
        printf("%s is winner",player1.name);
        reset();
        strcpy(highstruct1.name,player1.name);
        highstruct1.storedScore = playerscore.score_x;
    }
    else if(playerscore.score_x<playerscore.score_o)
    {
        yellow();
        printf("%s is winner",player2.name);
        reset();
        strcpy(highstruct1.name,player2.name);
        highstruct1.storedScore = playerscore.score_o;

    }
    else
    {
        printf("Draw\n\n");
        strcpy(highstruct1.name,player1.name);
        highstruct1.storedScore = playerscore.score_x;
    }
   // if(!((playerscore.score_x<playerscore.score_o) || (onePlayerCheck==1)))
   // {
        FILE *highscoresFile2 = fopen("HighScores.bin", "rb");
        fread(&TopRankedArrayofStructs, sizeof(TopRankedArrayofStructs), 1, highscoresFile2);
        fclose(highscoresFile2);

        sortByScore(TopRankedArrayofStructs,maxScores);

        int found=0;
        int i;
        for(i=0; i<maxScores; i++)
        {
            if(strcasecmp(TopRankedArrayofStructs[i].name,highstruct1.name)==0)
            {
                found = 1;
                break;
            }
        }
        if(found != 1)
        {
            if(TopRankedArrayofStructs[maxScores-1].storedScore < highstruct1.storedScore)
            {
                TopRankedArrayofStructs[maxScores-1] = highstruct1;
                sortByScore(TopRankedArrayofStructs,maxScores);
            }
        }
        else
        {
            if(TopRankedArrayofStructs[i].storedScore < highstruct1.storedScore)
            {
                TopRankedArrayofStructs[i] = highstruct1;
                sortByScore(TopRankedArrayofStructs,maxScores);
            }
        }
        for(i=0; i<maxScores; i++)
        {
            if(strcasecmp(TopRankedArrayofStructs[i].name,highstruct1.name)==0)
            {
                found = 1;
                break;
            }
        }
        if(i!=maxScores+1)
        {
            if(playerscore.score_x<playerscore.score_o)
            {
                yellow();
                printf("\nYour Rank is %d\n",i+1);
                reset();
            }
            else
            {
                red();
                printf("\nYour Rank is %d\n",i+1);
                reset();
            }

      //}
        FILE *highscoresFile = fopen("HighScores.bin", "wb");
        fwrite(&TopRankedArrayofStructs,sizeof(TopRankedArrayofStructs),1,highscoresFile);
        fclose(highscoresFile);

    }

    printf("\nPress Enter to return to main menu");
    getchar();
    system("cls");
    mainMenu();
    return 0;
}

int load_game()
{
    parameters gameparameters;

    int defaultValueReference;
    char gameFileParametersName[] = "Game Parameters.xml";
    gameparameters = parametersInXml(gameFileParametersName);
    while(gameparameters.corrupted==1 || gameparameters.corrupted==2)
    {
        if(gameparameters.corrupted==1)
        {
            defaultValueReference = corruptedMenu();
        }
        else if(gameparameters.corrupted==2)
        {
            defaultValueReference = error404();
        }
        if(defaultValueReference == -1)
        {
            char defaultFileParametersName[] = "Default Parameters.xml";
            gameparameters = parametersInXml(defaultFileParametersName);
        }
        else if(defaultValueReference == -5)
        {
            char gameFileParametersName2[256];
            system("cls");
            yellow();
            printf("Enter file's path\n");
            gets(gameFileParametersName2);

            for(int i=0; i<strlen(gameFileParametersName2); i++)
            {
                if(gameFileParametersName2[i]=='\\')
                {
                    gameFileParametersName2[i] = '/';
                }
            }


            strcpy(gameFileParametersName,gameFileParametersName2);
        }
        gameparameters = parametersInXml(gameFileParametersName);
        system("cls");
    }
    int maxScores = gameparameters.highscores;

    state savedGames[3];
    state currentState;
    FILE* in;
    in = fopen("savedGames.bin", "rb");
    fread(&savedGames, sizeof(savedGames), 1, in);
    fclose(in);

    info player1;
    info player2;
    int onePlayerCheck;
    int progress[rows*col];
    char piece;
    int center=42;
    int errors=0;
    int currentGame;
    system("cls");
    printf("\n\n\n\n");
    yellow();
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    printf("=================================\n");
    for(int x=0; x<center-1; x++)
    {
        printf(" ");
    }
    printf("|");
    red();
    printf("     Choose a game from (1-3)    ");
    yellow();
    printf("|\n");
    for(int x=0; x<center; x++)
    {
        printf(" ");
    }
    yellow();
    printf("=================================\n");
    char input[256];
    int j;
    do
    {
        fgets(input, 256, stdin);
        j = atoi(input);

        switch (j)
        {
        case 1:
            currentState = savedGames[0];
            break;
        case 2:
            currentState = savedGames[1];
            break;
        case 3:
            currentState = savedGames[2];
            break;
        default:
            j = 0;
            printf("Enter a number from 1-3: ");
        }
    }
    while(!j);
    Loading();
    loaded = j;
    rows = currentState.rows;
    col = currentState.col;
    struct highScoreStructs highstruct1;
    char a[rows][col];
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<col; j++)
        {
            a[i][j]= ' ';
        }
    }
    c = currentState.c;
    shift = currentState.shift;
    for(int i = 0; i < c + shift; i++)
    {

        progress[i] = currentState.progress[i];

    }
    player1 = currentState.player1;
    player2 = currentState.player2;
    onePlayerCheck = currentState.onePlayerCheck;
    /// geting the pieces back
    for (int k = 0; k < c
            ; k++)
    {
        int j = progress[k];
        for(int i=rows; i>=0; i--)
        {
            if(a[i][j] == ' ')
            {
                if(k%2 == 0)
                {
                    a[i][j] = 'X';
                }
                else
                {
                    a[i][j] = 'O';
                }
                break;
            }
        }
    }
    printUI(errors,a,player1,player2);
    system("cls");
    printUI(errors,a,player1,player2);
    structTime.startTimeSec = time(NULL);
    int endGame=rows*col;

    while(c<endGame)
    {
        if(c%2==0)
        {
            piece = 'X';
            fillBoard(a,piece,progress,player1,player2,onePlayerCheck);
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec) + currentState.moveTime;
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            structTime.moveTimeSec %= 60;
            system("cls");
            printUI(errors,a,player1,player2);
        }
        else
        {
            piece = 'O';
            fillBoard(a,piece,progress,player1,player2,onePlayerCheck);
            structTime.moveTimeSec = (time(NULL) - structTime.startTimeSec) + currentState.moveTime;
            structTime.moveTimeMin = (structTime.moveTimeSec/60)%60;
            structTime.moveTimeHr = (structTime.moveTimeMin/60);
            structTime.moveTimeSec %= 60;
            system("cls");
            printUI(errors,a,player1,player2);
        }
    }

    scores playerscore = count_4_Row(rows, col, a);
    struct highScoreStructs TopRankedArrayofStructs[maxScores];
    printf("\n");


    if(playerscore.score_x>playerscore.score_o)
    {
        red();
        printf("%s is winner",player1.name);
        reset();
        strcpy(highstruct1.name,player1.name);
        highstruct1.storedScore = playerscore.score_x;
    }
    else if(playerscore.score_x<playerscore.score_o)
    {
        yellow();
        printf("%s is winner",player2.name);
        reset();
        strcpy(highstruct1.name,player2.name);
        highstruct1.storedScore = playerscore.score_o;

    }
    else
    {
        printf("Draw\n\n");
        strcpy(highstruct1.name,player1.name);
        highstruct1.storedScore = playerscore.score_x;
    }
    //if(!((playerscore.score_x<playerscore.score_o) || (onePlayerCheck==1)))
    //{
        FILE *highscoresFile2 = fopen("HighScores.bin", "rb");
        fread(&TopRankedArrayofStructs, sizeof(TopRankedArrayofStructs), 1, highscoresFile2);
        fclose(highscoresFile2);

        sortByScore(TopRankedArrayofStructs,maxScores);

        int found=0;
        int i;
        for(i=0; i<maxScores; i++)
        {
            if(strcasecmp(TopRankedArrayofStructs[i].name,highstruct1.name)==0)
            {
                found = 1;
                break;
            }
        }
        if(found != 1)
        {
            if(TopRankedArrayofStructs[maxScores-1].storedScore < highstruct1.storedScore)
            {
                TopRankedArrayofStructs[maxScores-1] = highstruct1;
                sortByScore(TopRankedArrayofStructs,maxScores);
            }
        }
        else
        {
            if(TopRankedArrayofStructs[i].storedScore < highstruct1.storedScore)
            {
                TopRankedArrayofStructs[i] = highstruct1;
                sortByScore(TopRankedArrayofStructs,maxScores);
            }
        }
        for(i=0; i<maxScores; i++)
        {
            if(strcasecmp(TopRankedArrayofStructs[i].name,highstruct1.name)==0)
            {
                found = 1;
                break;
            }
        }
        if(i!=maxScores+1)
        {
            if(playerscore.score_x<playerscore.score_o)
            {
                yellow();
                printf("\nYour Rank is %d\n",i+1);
                reset();
            }
            else
            {
                red();
                printf("\nYour Rank is %d\n",i+1);
                reset();
            }

        }
        FILE *highscoresFile = fopen("HighScores.bin", "wb");
        fwrite(&TopRankedArrayofStructs,sizeof(TopRankedArrayofStructs),1,highscoresFile);
        fclose(highscoresFile);

    //}

    printf("\nPress Enter to return to main menu");
    getchar();
    system("cls");
    mainMenu();
    return 0;
}

int AI(char a[rows][col])
{
    time_t t;
    srand((unsigned) time(&t));
    int size = col;
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

parameters parametersInXml(char filename[256])
{
    parameters parameters1;

    FILE *file = fopen(filename,"r");
    int i;
    int j;
    int count=0;
    int corruptionChecker=0; ///zero:normal - one:file is corrupted - two:file not found
    if (file != NULL)
    {
        while(count <=4)
        {
            if(count==0)  ///Configuration Opening Corruption Check
            {
                i=0;
                j=0;
                char ConfigOpen[256];
                fgets(ConfigOpen,sizeof(ConfigOpen),file);
                while((ConfigOpen[i]==' ')||(ConfigOpen[i]=='\t'))
                {
                    i++;
                }
                char ConfigOpenCode[256-i];
                char ConfigOpenTag[] = "<Configurations>";
                while(ConfigOpen[j]!='\0')
                {
                    ConfigOpenCode[j]=ConfigOpen[i+j];
                    j++;
                }
                j++;
                for(j=0; j<strlen(ConfigOpenTag); j++)
                {
                    if(ConfigOpenCode[j] != ConfigOpenTag[j])
                    {
                        corruptionChecker=1;
                        break;
                    }
                }
                count++;
            }
            else if(count==1)  /// height parameter take and Corruption Check
            {
                i=0;
                j=0;
                char heightLine[256];
                fgets(heightLine,sizeof(heightLine),file);
                while((heightLine[i]==' ')||(heightLine[i]=='\t'))
                {
                    i++;
                }
                char heightCode[256-i];
                while(heightLine[j]!='\0')
                {
                    heightCode[j]=heightLine[i+j];
                    j++;
                }
                j++;
                char height[256];
                for(int x=0; x<10; x++)
                {
                    height[x] = 'a';
                }
                char heightOpenTag[] = "<Height>";
                char heightCloseTag[] = "</Height>";

                for(j=0; j<strlen(heightOpenTag); j++)
                {
                    if(heightCode[j] != heightOpenTag[j])
                    {
                        corruptionChecker=1;
                        break;
                    }
                }
                if(!corruptionChecker)
                {
                    int a=0;
                    while(isdigit(heightCode[j]))
                    {
                        height[a] = heightCode[j];
                        a++;
                        j++;
                    }
                    parameters1.height = atoi(height);
                    for(i=0; i<strlen(heightOpenTag); i++)
                    {
                        if(heightCode[i+j] != heightCloseTag[i])
                        {
                            corruptionChecker=1;
                            break;
                        }
                    }
                }
                count++;
            }
            else if(count==2)  /// width parameter take and Corruption Check
            {
                i=0;
                j=0;
                char widthLine[256];
                fgets(widthLine,sizeof(widthLine),file);
                while((widthLine[i]==' ')||(widthLine[i]=='\t'))
                {
                    i++;
                }
                char widthCode[256-i];
                while(widthLine[j]!='\0')
                {
                    widthCode[j]=widthLine[i+j];
                    j++;
                }
                j++;
                char width[256];
                for(int x=0; x<10; x++)
                {
                    width[x] = 'a';
                }
                char widthOpenTag[] = "<Width>";
                char widthCloseTag[] = "</Width>";

                for(j=0; j<strlen(widthOpenTag); j++)
                {
                    if(widthCode[j] != widthOpenTag[j])
                    {
                        corruptionChecker=1;
                        break;
                    }
                }
                if(!corruptionChecker)
                {
                    int a=0;
                    while(isdigit(widthCode[j]))
                    {
                        width[a] = widthCode[j];
                        a++;
                        j++;
                    }
                    parameters1.width = atoi(width);
                    for(i=0; i<strlen(widthOpenTag); i++)
                    {
                        if(widthCode[i+j] != widthCloseTag[i])
                        {
                            corruptionChecker=1;
                            break;
                        }
                    }
                }
                count++;
            }
            else if(count==3)  /// HighScores parameter take and Corruption Check
            {
                i=0;
                j=0;
                char highscoreLine[256];
                fgets(highscoreLine,sizeof(highscoreLine),file);
                while((highscoreLine[i]==' ')||(highscoreLine[i]=='\t'))
                {
                    i++;
                }
                char highscoreCode[256-i];
                while(highscoreLine[j]!='\0')
                {
                    highscoreCode[j]=highscoreLine[i+j];
                    j++;
                }
                j++;
                char highscore[256];
                for(int x=0; x<10; x++)
                {
                    highscore[x] = 'a';
                }
                char highscoreOpenTag[] = "<Highscores>";
                char highscoreCloseTag[] = "</Highscores>";

                for(j=0; j<strlen(highscoreOpenTag); j++)
                {
                    if(highscoreCode[j] != highscoreOpenTag[j])
                    {
                        corruptionChecker=1;
                        break;
                    }
                }
                if(!corruptionChecker)
                {
                    int a=0;
                    while(isdigit(highscoreCode[j]))
                    {
                        highscore[a] = highscoreCode[j];
                        a++;
                        j++;
                    }
                    parameters1.highscores = atoi(highscore);
                    for(i=0; i<strlen(highscoreOpenTag); i++)
                    {
                        if(highscoreCode[i+j] != highscoreCloseTag[i])
                        {
                            corruptionChecker=1;
                            break;
                        }
                    }
                }
                count++;
            }
            else if(count==4)  ///Configuration Closing Corruption Check
            {
                i=0;
                j=0;
                char ConfigClose[256];
                fgets(ConfigClose,sizeof(ConfigClose),file);
                while((ConfigClose[i]==' ')||(ConfigClose[i]=='\t'))
                {
                    i++;
                }
                char ConfigCloseCode[256-i];
                char ConfigCloseTag[] = "</Configurations>";
                while(ConfigClose[j]!='\0')
                {
                    ConfigCloseCode[j]=ConfigClose[i+j];
                    j++;
                }
                j++;
                for(j=0; j<strlen(ConfigCloseTag); j++)
                {
                    if(ConfigCloseCode[j] != ConfigCloseTag[j])
                    {
                        corruptionChecker=1;
                        break;
                    }
                }
                count++;
            }
            if(corruptionChecker==1)
            {
                break;
            }
        }
    }
    else
    {
        corruptionChecker=2;
    }
    fclose(file);

    if(corruptionChecker==0)
    {
        parameters1.corrupted=0;
    }
    else if(corruptionChecker==1)
    {
        parameters1.corrupted=1;
        parameters1.height=0;
        parameters1.highscores=0;
        parameters1.width=0;
    }
    else if(corruptionChecker==2)
    {
        parameters1.corrupted=2;
        parameters1.height=0;
        parameters1.highscores=0;
        parameters1.width=0;
    }
    fclose(file);
    return parameters1;
}

int top_players()
{
    int center = ((col*4)+50)/2;
    int maxScores;
    parameters gameparameters;
    int defaultValueReference;
    char gameFileParametersName[] = "Game Parameters.xml";
    gameparameters = parametersInXml(gameFileParametersName);
    while(gameparameters.corrupted==1 || gameparameters.corrupted==2)
    {
        if(gameparameters.corrupted==1)
        {
            defaultValueReference = corruptedMenu();
        }
        else if(gameparameters.corrupted==2)
        {
            defaultValueReference = error404();
        }
        if(defaultValueReference == -1)
        {
            char defaultFileParametersName[] = "Default Parameters.xml";
            gameparameters = parametersInXml(defaultFileParametersName);
        }
        else if(defaultValueReference == -5)
        {
            char gameFileParametersName2[256];
            system("cls");
            yellow();
            printf("Enter file's path\n");
            gets(gameFileParametersName2);

            for(int i=0; i<strlen(gameFileParametersName2); i++)
            {
                if(gameFileParametersName2[i]=='\\')
                {
                    gameFileParametersName2[i] = '/';
                }
            }


            strcpy(gameFileParametersName,gameFileParametersName2);
        }
        gameparameters = parametersInXml(gameFileParametersName);
        system("cls");
    }

    maxScores = gameparameters.highscores;

    struct highScoreStructs TopRanked[maxScores];

    FILE* highFile = fopen("HighScores.bin", "rb");

    fread(&TopRanked, sizeof(TopRanked), 1, highFile);
    fclose(highFile);

    sortByScore(TopRanked,maxScores);

    printf("\e[1;94m");
    gotoxy(center+4,0);
    printf("Top Players");

    for(int i=0; i<maxScores; i++)
    {
        gotoxy(center,i+2);
        yellow();
        printf("%s",TopRanked[i].name);
        red();
        gotoxy(center+17,i+2);
        printf("%d",TopRanked[i].storedScore);
    }


    getchar();
    system("cls");
    mainMenu();
}
/// main
int main(void)
{

    openingGame();
    system("cls");
    mainMenu();
}

