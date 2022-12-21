#include <stdio.h>
#include <stdlib.h>
#define X 'x'
#define O 'e'

















int count_4_Row(int m, int n, char arr[m][n])
{
   int score_R = 0, score_Y = 0;
   char temp;
   //////////////////////////////////////////////////////////////////////
   int check_right(int row, int col)
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
   int check_down(int row, int col)
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
   int check_diagonal_right(int row, int col)
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
    int check_diagonal_left(int row, int col)
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

    printf(" scoreR = %d      scoreY = %d", score_R, score_Y);
}



int main()
{
    int m = 5;
    int n = 8;
    //char arr[n][m];

     char arr[5][8] = {
        {'o','e','e','e','e','e','x','x'},
        {'o','o','o','o','x','e','x','x'},
        {'e','o','e','o','o','x','e','x'},
        {'o','o','e','o','x','o','o','e'},
        {'x','x','x','x','x','x','x','x'}
          };
count_4_Row(m, n, arr);

    return 0;
}
