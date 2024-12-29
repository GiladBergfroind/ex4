/******************
Name: Gilad Bergfroind
ID: 331749978
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define MAX_CROSSWORD_SIZE  30
#define MAX_WORD_LENGTH 16
#define MAXIMUM_SLOTS 100
#define HorizontalOrVertical 2

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();
void printMenu()
{
    printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

}
struct slotsPlaces {
    int row;
    int column;
    int length;
    char direction;
    int dictionaryIndex;
};
int main()
{
    printMenu();
    int task = -1;
    do
    {


        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
                case 1:
                task1RobotPaths();
                printMenu();
                break;
            case 2:
                task2HumanPyramid();
                printMenu();
                break;
            case 3:
                task3ParenthesisValidator();
                printMenu();
                break;
            case 4:
                task4QueensBattle();
                printMenu();
                break;
            case 5:
                task5CrosswordGenerator();
                printMenu();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                printMenu();
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}
int robotPaths(int column, int row) {
    if (column == 0 || row == 0) // if the robot is in column 0 or row 0 the robot has only 1 way to (0,0).
        return 1;
    if (column < 0 || row < 0) // break condition.
        return 0;
    return robotPaths(column -1, row) + robotPaths(column, row -1); // call for recursive function.
}

void task1RobotPaths() {
    int column, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &column, &row);
    printf("The total number of paths the robot can take to reach home is: %d\n",
        robotPaths(column, row));
}
// function that sets all the values to 0.
void initarray(int size,float array[size][size]) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            {
                array[i][j] = 0;
            }
    }
}

// function that returns the weight of some people given the position.
float carriedWeightFunc(float weight[5][5], int row,int column)
{
    if (row == 0) // the person is on top of everyone which means that he is carrying only his weight.
        return weight[0][0];
    if (row == column) // the person is in the most left position in his row.
        return carriedWeightFunc(weight, row - 1, column-1)/2 + weight[row][column];
    if (column == 0) // the person is in the most right position in his row.
        return carriedWeightFunc(weight, row - 1, column)/2 + weight[row][column];
    return carriedWeightFunc(weight, row - 1, column)/2 +carriedWeightFunc(weight, row - 1, column-1)/2
    + weight[row][column];
}
// the rest is calls for recursive functions.

void task2HumanPyramid() {
    float weight[5][5], temporary;
    printf("Please enter the weights of the cheerleaders:\n");
    int validation = 0;
    initarray(5,weight);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j <= i; j++){
            if (scanf("%f", &temporary)&& (temporary >= 0))
                // checks if the given values is positive and if not returns the user to the main menu.
                weight[i][j] = temporary;
            else
            {
                printf("Negative weights are not supported.\n");
                validation = 1;
                i = 5;
                break;
            }
        }
    if (validation == 0) {
        printf("The total weight on each cheerleader is:\n");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j <= i; j++)
                printf("%.2f ",carriedWeightFunc(weight,i, j));
            printf("\n");
        }
    }

}
    int pv(char target)
/* pv stands for ParenthesisValidator, the function recives a char and does the following things:
 * if the char is one of this: {,[,(,< the function calls for the function again and sets the target to the right close parenthesis.
 * if the char is one of this: },],),>, \n the function checks if the target is the recived char,
 * if it is the functions returns 1 if not the function returns 0.
 * if the char is everything else the function continue.
*/
{
    char c;
    while ( scanf("%c",&c) == 1 ) {
        switch (c) {
            case '(':
                if (  pv(')') == 0 )
                    return 0;
                break;
             case '<':
                if (  pv('>') == 0 )
                    return 0;
                break;
             case '[':
                if (  pv(']') == 0 )
                    return 0;
                break;
             case '{':
                if (  pv('}') == 0 )
                    return 0;
                break;
             case ')':
             case '>':
             case ']':
             case '}':
             case '\n':
            if ( c == target)
                return 1;
            return 0;

         }
    }
return 0;
}


    void task3ParenthesisValidator() {
    char c;
    printf("Please enter a term for validation:\n");
    scanf("%c",&c);
    if (pv('\n')) // call for recursive function with \n as the target
        printf("The parentheses are balanced correctly.\n");
    else
    printf("The parentheses are not balanced correctly.\n");
    }

//function that checks if there is a queen in some given column.
int isQueenInColumn(int row,int column,int dimension, char solvedBoard[dimension][dimension]) {
    if (row == dimension)
        return 0;
    if (solvedBoard[row][column] == 'X')
        return 1;
    else
        return isQueenInColumn(row+1,column,dimension,solvedBoard);
}

//function that checks if there is a queen in the area of some given position.
int isQueenWithinTouch(int row,int column,int dimension, char solvedBoard[dimension][dimension]) {
    if (row == 0 && column == 0)
        return solvedBoard[row+1][column+1] == 'X';
    if (row == 0 && column == dimension-1)
        return (solvedBoard[row+1][column-1] == 'X');
    if (row == dimension-1 && column == dimension-1)
        return solvedBoard[row-1][column-1] == 'X';
    if (row == dimension-1 && column == 0 )
        return (solvedBoard[row-1][column+1] == 'X');
    if (column == 0)
        return (solvedBoard[row+1][column+1] == 'X' || solvedBoard[row-1][column+1] == 'X');
    if (column == dimension-1)
        return (solvedBoard[row-1][column-1] == 'X' || solvedBoard[row+1][column-1] == 'X');
    if (row == 0)
        return (solvedBoard[row+1][column-1] == 'X' || solvedBoard[row+1][column+1] == 'X');
    if (row == dimension-1)
        return (solvedBoard[row-1][column-1] == 'X' || solvedBoard[row-1][column+1] == 'X');
    return (solvedBoard[row-1][column-1] == 'X' || solvedBoard[row+1][column-1] == 'X'
        || solvedBoard[row-1][column+1] == 'X' || solvedBoard[row+1][column+1] == 'X');

}

//function that checks if all of the values in the some given array is equal
//to 1 - if there are qeens in all if the colors.
int isSolutionRight(int size,char array[size],int counter) {
    char value = '1';
    if (counter == size)
        return 1;
    if (array[counter] != value)
        return 0;
    return isSolutionRight(size,array,counter+1);
}

//function that checks if there is a given value in a given array and returns it's palce,
//if the value isn't in the array the function return -1.
int findValue(int size,char array[size],int value,int counter ) {
    if (counter == size) return -1;
    if (array[counter] == value)
    {
        return counter;
    }
    return (findValue(size,array,value,counter+1));
}

//function that checks if a given block is available.
int availableBlocks(int dimension,char board[dimension][dimension],int row, int column,
    char colors[dimension],char solvedBoard[dimension][dimension] ) {
    return (!isQueenInColumn(0, column,dimension,solvedBoard)&&
        (colors[findValue(dimension,colors,board[row][column],0)] !='1')
        &&!isQueenWithinTouch(row,column,dimension,solvedBoard)&&solvedBoard[row][column] != 'X');

}

//the recursive function.
int solution(int dimension,char board[dimension][dimension],int row, int column,
    char colors[dimension],char solvedBoard[dimension][dimension] ,char colorsOriginal[dimension]) {
    if (row == dimension) //there are queens in all of the rows.
        return 1;
    if (column == dimension) //there is a column without a queen.
        return 0;
    if (availableBlocks(dimension,board,row,column,colors,solvedBoard)) {
        solvedBoard[row][column] = 'X'; //marks the queen spot.
        colors[findValue(dimension,colors,board[row][column],0)] ='1'; //marks the color in the colors array.
        if (solution(dimension,board,row+1,0,colors,solvedBoard,colorsOriginal) == 0)
            //call for recursive function in the next row.
        {
            if (isSolutionRight(dimension,colors,0) == 1) //checks if soltion is right
                return 0;
            solvedBoard[row][column] = '0'; //if we got here this means that the last queen is not in the right place,
            //therefor we mark the spot with 0 to know that the queen is not there anymore.
            colors[findValue(dimension,colorsOriginal,board[row][column],0)] =
                colorsOriginal[findValue(dimension,colorsOriginal,board[row][column],0)];
            //sets the value of the removed queen in the colors array back to his original color.
        }
    }
        return solution(dimension,board,row,column+1,colors,solvedBoard,colorsOriginal);
    }

//function that sets all of the values in an array to 0.
int initArrayChar(int dimension,char array[dimension][dimension],int column,int row) {
    if (row == dimension)
    return 0;
    if (column == dimension) {
        row++;
        column = -1;
    }
    array[row][column] = 0;
    return initArrayChar(dimension,array,column+1,row);
}



    void task4QueensBattle()
    {
        int dimension,counter = 0;
        printf("Please enter the board dimensions:\n");
        scanf("%d",&dimension);
        printf("Please enter a %d*%d puzzle board:\n", dimension, dimension);
        char board[dimension][dimension], solvedBoard[dimension][dimension],colors[dimension],
        colorsOriginal[dimension];
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                scanf(" %c",&board[i][j]);
                if (findValue(dimension,colors,board[i][j],0) == -1) { //search for a new color
                    colors[counter] = board[i][j];
                    colorsOriginal[counter] = colors[counter];
                    counter++;
                }
            }
        }
    initArrayChar(dimension,solvedBoard,0,0);
    if ((solution(dimension,board,0,0,colors,solvedBoard,colorsOriginal)==0)
        &&(isSolutionRight(dimension,colors,0)==1)) {
        printf("Solution:\n");
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                { if (solvedBoard[i][j] == 'X')
                    printf("%c ", solvedBoard[i][j]);
                  else
                      printf("* ");
                }
            }
            printf("\n");
        }
    }
    else
        printf("This puzzle cannot be solved. \n");
    }
struct Slot {
    int row;
    int col;
    int length;
    int direction[HorizontalOrVertical];
};

// function that places a word at a specific position
void fillWord(int row, int col, int length, int direction[HorizontalOrVertical], int size, char word[],
               char crosswordBoard[][MAX_CROSSWORD_SIZE], int charIndex) {
    if (charIndex == length) return;
    crosswordBoard[row][col] = word[charIndex];
    fillWord(row + direction[1], col + direction[0], length, direction, size, word, crosswordBoard, charIndex + 1);
}

// function that checks if a word can be placed at a specific position
int rightWord(int row, int col, int requiredLength, int wordLength, int direction[HorizontalOrVertical], int size,
                 char word[], char crosswordBoard[][MAX_CROSSWORD_SIZE], int wordIndex,
                 int totalSlots, int usedWords[], int charIndex) {
    if (charIndex == wordLength) return 1;
    if (requiredLength != wordLength || usedWords[wordIndex] != 0 ||
        (crosswordBoard[row][col] != '\0' && crosswordBoard[row][col] != word[charIndex]))
        return 0;
    return rightWord(row + direction[1], col + direction[0], requiredLength, wordLength, direction, size, word,
                        crosswordBoard, wordIndex, totalSlots, usedWords, charIndex + 1);
}

// function that removes a word.
void removeWord(int row, int col, int length, int direction[HorizontalOrVertical], int size,
                char crosswordBoard[][MAX_CROSSWORD_SIZE], int charIndex) {
    if (charIndex == length) return;
    crosswordBoard[row][col] = '\0';
    removeWord(row + direction[1], col + direction[0], length, direction, size, crosswordBoard, charIndex + 1);
}

// function that prints the crossword board
void printCrossword(int size, char crosswordBoard[][MAX_CROSSWORD_SIZE]) {
    for (int i = 0; i < size; i++) {
        printf("|");
        for (int j = 0; j < size; j++) {
            if (crosswordBoard[i][j] == '\0') printf(" # |");
            else printf(" %c |", crosswordBoard[i][j]);
        }
        printf("\n");
    }
}

// function that solves the crossword puzzle
int solveCrossword(int boardSize, int totalWords, int totalSlots, char crosswordBoard[][MAX_CROSSWORD_SIZE],
                   char wordList[][MAX_WORD_LENGTH], int slotIndex, int usedWords[],
                   int currentWordIndex, struct Slot slotInstructions[]) {
    if (slotIndex == totalSlots) return 1;
    if (currentWordIndex == totalWords) return 0;

    if (rightWord(slotInstructions[slotIndex].row, slotInstructions[slotIndex].col,
                     slotInstructions[slotIndex].length,
                     strlen(wordList[currentWordIndex]), slotInstructions[slotIndex].direction, boardSize,
                     wordList[currentWordIndex], crosswordBoard, currentWordIndex, totalSlots, usedWords,
                     0)) {
        usedWords[currentWordIndex] = 1;
        fillWord(slotInstructions[slotIndex].row, slotInstructions[slotIndex].col, slotInstructions[slotIndex].length,
                  slotInstructions[slotIndex].direction, boardSize, wordList[currentWordIndex], crosswordBoard, 0);

        if (solveCrossword(boardSize, totalWords, totalSlots, crosswordBoard, wordList, slotIndex + 1, usedWords, 0,
                           slotInstructions))
            return 1;

        removeWord(slotInstructions[slotIndex].row, slotInstructions[slotIndex].col, slotInstructions[slotIndex].length,
                   slotInstructions[slotIndex].direction, boardSize, crosswordBoard, 0);
        usedWords[currentWordIndex] = 0;
    }

    return solveCrossword(boardSize, totalWords, totalSlots, crosswordBoard, wordList, slotIndex, usedWords,
                          currentWordIndex + 1, slotInstructions);
}

void task5CrosswordGenerator() {
    int boardSize, totalSlots, totalWords;

    printf("Please enter the dimensions of the crossword grid:\n");
    scanf(" %d", &boardSize);

    printf("Please enter the number of slots in the crossword:\n");
    scanf(" %d", &totalSlots);

    char crosswordBoard[MAX_CROSSWORD_SIZE][MAX_CROSSWORD_SIZE] = {'\0'};
    struct Slot slotInstructions[MAXIMUM_SLOTS];

    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < totalSlots; i++) {
        char dir;
        scanf(" %d %d %d %c", &slotInstructions[i].row, &slotInstructions[i].col, &slotInstructions[i].length, &dir);

        int direction[HorizontalOrVertical] = {0, 0};
        if (dir == 'V') direction[1] = 1;
        else if (dir == 'H') direction[0] = 1;

        slotInstructions[i].direction[0] = direction[0];
        slotInstructions[i].direction[1] = direction[1];
    }

    printf("Please enter the number of words in the dictionary:\n");
    while (scanf(" %d", &totalWords) && totalWords < totalSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", totalSlots);
    }

    char wordList[MAXIMUM_SLOTS][MAX_WORD_LENGTH];
    int usedWords[MAXIMUM_SLOTS] = {0};

    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < totalWords; i++) {
        scanf(" %s", wordList[i]);
    }

    if (solveCrossword(boardSize, totalWords, totalSlots, crosswordBoard, wordList, 0, usedWords, 0, slotInstructions)) {
        printCrossword(boardSize, crosswordBoard);
    } else {
        printf("This crossword cannot be solved.\n");
    }
}

