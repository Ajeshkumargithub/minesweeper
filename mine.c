#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10
#define mine -1

void printBoard(int board[][SIZE]);
void print_Board(int board[][SIZE]);
int isValid(int x, int y);
void setMines(int (*board)[SIZE], int MINES);
int minesInArray(int (*board)[SIZE], int row, int col, int size);
int minesInSquare(int (*board)[SIZE], int row, int col, int side_length);
int isSafe(int (*board)[SIZE], int row, int col);
void revealConnected(int (*board)[SIZE], int row, int col);
int revealCross(int (*board)[SIZE], int row, int col);

bool debug_board;

int main()
{
    debug_board = true;
    printf("Welcome to Minesweeper!!!\nHow many mines? ");

    int MINES, n, gameOver = 0, helpCount = 0;
    int board[SIZE][SIZE] = {0};

    scanf("%d", &MINES);
    setMines(board, MINES);
    printBoard(board);

    printf("Game Started\n");
    while (gameOver == 0)
    {
        char input_str[5];
        printf("enter command:");
        getchar();
        fgets(input_str, SIZE, stdin);

        int type = input_str[0] - '0';
        int row = input_str[2] - '0';
        int col = input_str[4] - '0';
        int size = input_str[6] - '0';

        switch (type)
        {
        case 1:
            if (helpCount >= 3)
            {
                printf("Help already used..\n");
                break;
            }
            helpCount++;
            n = minesInArray(board, row, col, size);
            if (n == -1)
            {
                printf("Coordinates not on map.\n");
            }
            else
            {
                printf("There are %d mine(s) in row %d, from column %d to %d.\n", n, row, col, col + size - 1);
            }
            break;
        case 2:
            if (helpCount >= 3)
            {
                printf("Help already used..\n");
                break;
            }
            helpCount++;
            n = minesInSquare(board, row, col, size);
            if (n == -1)
            {
                printf("Coordinates not on map.\n");
            }
            else
            {
                printf("There are %d mine(s) in the square centred at row %d, column %d, of size %d.\n", n, row, col, size);
            }
            break;
        case 3:
            n = revealCross(board, row, col);
            if (n == -1)
            {
                printf("Coordinates not on map.\n");
            }
            if (n == 0)
            {
                gameOver = 1;
            }
            break;
        case 4:
            debug_board = !debug_board;
            break;
        default:
            printf("wrong command\n");
        }
        printf("\n");
        if (debug_board == true)
        {
            printBoard(board);
        }
        else
        {
            print_Board(board);
        }

        if (gameOver == 1)
        {
            printf("Game Over!!");
            break;
        }
    }

    return 0;
}

void printBoard(int board[][SIZE])
{
    int i, j;
    printf("\n    00 01 02 03 04 05 06 07 08 09\n---------------------------------\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%02d  ", i);
        for (j = 0; j < SIZE; j++)
        {
            printf("%02d ", board[i][j]);
        }
        printf("\n---------------------------------\n");
    }
}

void print_Board(int board[][SIZE])
{
    int i, j;
    printf("\n    00 01 02 03 04 05 06 07 08 09\n---------------------------------\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%02d  ", i);
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 1)
            {
                printf("%02d ", minesInSquare(board, i, j, 3));
            }
            else if (board[i][j] == -2)
            {
                printf("() ");
            }
            else
            {
                printf("## ");
            }
        }
        printf("\n---------------------------------\n");
    }
}
int isValid(int x, int y)
{
    if (x >= 0 && x < SIZE && y < SIZE && y >= 0)
    {
        return 1;
    }
    return 0;
}

void setMines(int (*board)[SIZE], int MINES)
{
    int i, x, y;
    printf("Enter pairs: \n");
    for (i = 0; i < MINES; i++)
    {
        scanf("%d %d", &x, &y);
        if (isValid(x, y))
        {
            board[x][y] = mine;
        }
    }
}

int minesInArray(int (*board)[SIZE], int row, int col, int size)
{
    int count = 0, i;
    int end_col = col + size - 1;
    if (isValid(row, col) && (end_col) < SIZE)
    {
        for (i = col; i <= (end_col); i++)
        {
            if (board[row][i] == mine)
            {
                count++;
            }
        }
        return count;
    }
    else
    {
        return -1;
    }
}

int minesInSquare(int (*board)[SIZE], int row, int col, int side_length)
{
    if (isValid(row, col))
    {
        int i, j, count = 0;
        int st_row = row - (side_length / 2);
        int en_row = row + (side_length / 2);
        int st_col = col - (side_length / 2);
        int en_col = col + (side_length / 2);
        for (i = st_row; i <= en_row; i++)
        {
            for (j = st_col; j <= en_col; j++)
            {
                if (isValid(i, j))
                {
                    if (board[i][j] == mine)
                    {
                        count++;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        return count;
    }
    else
    {
        return -1;
    }
}

int isSafe(int (*board)[SIZE], int row, int col)
{
    if (isValid(row, col))
    {
        if ((board[row][col] == mine))
        {
            return 0;
        }
    }
    return 1;
}

void revealConnected(int (*board)[SIZE], int row, int col)
{
    if (isValid(row - 1, col))
    {
        if (minesInSquare(board, row - 1, col, 3) == 0)
        {
            board[row - 1][col] = 01;
        }
    }
    if (isValid(row + 1, col))
    {
        if (minesInSquare(board, row + 1, col, 3) == 0)
        {
            board[row + 1][col] = 01;
        }
    }
    if (isValid(row, col - 1))
    {
        if (minesInSquare(board, row, col - 1, 3) == 0)
        {
            board[row][col - 1] = 01;
        }
    }
    if (isValid(row, col + 1))
    {
        if (minesInSquare(board, row, col + 1, 3) == 0)
        {
            board[row][col + 1] = 01;
        }
    }
}

int revealCross(int (*board)[SIZE], int row, int col)
{
    if (isValid(row, col))
    {
        if (board[row][col] == mine)
        {
            board[row][col] = -2;
            return 0;
        }
        else
        {
            board[row][col] = 01;
            int up = isSafe(board, row - 1, col);
            int down = isSafe(board, row + 1, col);
            int left = isSafe(board, row, col - 1);
            int right = isSafe(board, row, col + 1);
            if (up && down && left && right)
            {
                revealConnected(board, row, col);
            }
        }
        return 1;
    }
    else
    {
        return -1;
    }
}
