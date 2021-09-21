// Compulsory 1, Programming 1, Marcus Henriksen
// In this program you can play tic tac toe versus another player or versus an "AI" that is based on random numbers.
// The placement of X and Os is based on a WASD movement system, using a player X and Y variable, which will always
// correspond to said X and Y position in the 2D array that is used to store the position of markers X and O.
// The print function runs parallell to the 2D array and player X and Y position using a nested for loop and
// iterators going from 0-2. The player X and Y does not go under 0 or above 2. The game is encased in a menu
// system that lets you seamlessly move between gamemodes and exit or play again when you want. There has also
// been implemented tamper-proofing code to prevent mistakes and intentional cheating/crashing of the game.

#include <iostream>
#include <Windows.h>    // Sleep()
#include <conio.h>      // _getch()
#include <time.h>       // time


void printTable();      // Function that prints the table and markers
void checkChar();       // Checks user input (WASD, Enter) and changes player XY position based on input
void confirm();         // Places X and O in the 2D array based on the position of the player 
void checkScore();      // Checks if either player has won by comparing similar values
void win(char player);  // Stops the game, determines which player won and prints it. Gives option to reset the game
void resetGame(int i);  // Resets all variables, clears the 2D array and resumes the main while-loop
void aiTurn();          // Decides where the AI should place the marker


time_t currentTime;
int playerX = 0;
int playerY = 0;
int currentPlayer = 1;  // Player 1 = X, Player 2 = O
bool gameRunning = true;
bool gameWon = false;
bool aiMode = false;

char arr[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
};


int main()
{
    srand((unsigned)time(&currentTime)); // Seed the rand function with the current time
    system("color F"); // White

    int ans{};
    while (true) {
        system("cls");
        std::cout << "Welcome to Tic Tac Toe, please select a gamemode." << std::endl;
        std::cout << "1. Player vs Player" << std::endl;
        std::cout << "2. Player vs AI" << std::endl;
        std::cout << "3. Exit" << std::endl;

        while (true) {
            std::cin >> ans;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            
            if (ans == 1) { // PvP
                aiMode = false;
                break;
            }
            else if (ans == 2) { // PvE
                aiMode = true;
                break;
            }
            else if (ans == 3) {
                exit(0);
            }
            else {
                std::cout << "Please enter a valid number." << std::endl;
            }
        }
        
        gameRunning = true;
        while (gameRunning) { //Keeps the game running until the player chooses to stop after a win
            system("cls");
            printTable();
            if (aiMode == true && currentPlayer == 1 || aiMode == false) {
                checkChar();
            }
            else if (aiMode == true && currentPlayer == 2) {
                std::cout << "Thinking..." << std::endl;
                Sleep(1000);
                aiTurn();
            }
            else {
                std::cout << "Error in main function!";
                exit(0);
            }
        }
    }
    return 0;
}


void printTable() {
    std::cout << "Tic Tac Toe Lets Go! ";

    if (aiMode) { std::cout << "Player versus AI." << std::endl; }
    else { std::cout << "Player versus player." << std::endl; }

    std::cout << "Use the WASD keys to move around, press Enter to confirm." << std::endl << std::endl;

    if (aiMode) { 
        if (currentPlayer == 1) { std::cout << "Your turn!" << std::endl; }
        else { std::cout << "AI's turn!" << std::endl; }
    }
    else { std::cout << "Player " << currentPlayer << "'s turn!" << std::endl; }

    std::string row = " ------- ------- -------";

    for (int y = 0; y < 3; y++) { // Using iterators "x" and "y" to compare to player x and y position
        std::cout << row << std::endl;
        std::cout << "|";
        for (int x = 0; x < 3; x++) {
            if (arr[y][x] == 'X') { // Check if there is an X, if so, place it
                if (playerY == y && playerX == x) { std::cout << "   X*  |"; } // QOL code, makes it easier to see where the cursor is
                else { std::cout << "   X   |"; }
            }
            else if (arr[y][x] == 'O') { // Check if there is an O, if so, place it
                if (playerY == y && playerX == x) { std::cout << "   O*  |"; }
                else { std::cout << "   O   |"; }
            }
            else if (playerY == y && playerX == x) {
                std::cout << "   *   |";
            }
            else { // Print empty cell if there is nothing in the according 2D array cell
                std::cout << "       |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << row << std::endl;
    //Enable this if you want to see how the player position in the 2D array works
    //std::cout << "PlayerY: " << playerY << " PlayerX: " << playerX; 
}


void checkChar() {
    char ch{};
    ch = _getch(); // Get user input (WASD, Enter)

    // In this switch statement I change the player X and Y position based on the input.
    // I need to have an if sentence in each case to avoid going out of scope of the array.
    // For example if the player position is on the top left, and the user presses "A" or "W".
    switch (ch) {
    case 'w':
    case 'W':
        if (playerY == 0) { break; }
        else { playerY--; }
        break;
    case 'a':
    case 'A':
        if (playerX == 0) { break; }
        else { playerX--; }
        break;
    case 's':
    case 'S':
        if (playerY == 2) { break; }
        else { playerY++; }
        break;
    case 'd':
    case 'D':
        if (playerX == 2) { break; }
        else { playerX++; }
        break;
    case 13: // Enter
        confirm();
        break;
    default:
        std::cout << "Wrong key!";
        Sleep(350); // Without this function call the screen will instanly be cleared, thus not showing the cout
        break;
    }
}


void confirm() {
    if (arr[playerY][playerX] == 'X' || arr[playerY][playerX] == 'O') {
        return; // No overwriting allowed!
    }
    else { // Here I insert the value into the 2D array
        if (currentPlayer == 1) {
            arr[playerY][playerX] = 'X'; // X for player 1
        }
        else {
            arr[playerY][playerX] = 'O'; // O for player 2
        }
    }

    if (currentPlayer == 1) { //Switch players
        currentPlayer = 2;
    }
    else {
        currentPlayer = 1;
    }
    checkScore(); // Now that the value is inserted, I check if a player has won
}


void checkScore() { // Forgive me, it was the only way
    if (arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2] && arr[0][0] != ' ') { // If there is 3 equal values in a row, and the values are not empty, run the win function
            win(arr[0][0]);
    }
    else if (arr[1][0] == arr[1][1] && arr[1][1] == arr[1][2] && arr[1][0] != ' ') {
            win(arr[1][0]);
    }
    else if (arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2] && arr[2][0] != ' ') {
            win(arr[2][0]);
    }
    else if (arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0] && arr[0][0] != ' ') {
            win(arr[0][0]);
    }
    else if (arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1] && arr[0][1] != ' ') {
            win(arr[0][1]);
    }
    else if (arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2] && arr[0][2] != ' ') {
            win(arr[0][2]);
    }
    else if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != ' ') {
            win(arr[0][0]);
    }
    else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][2] != ' ') {
            win(arr[0][2]);
    }
    else { // Here I check if there has been a draw, by checking if the 2D array is completely filled
        int count{};
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                if (arr[i][k] != ' ') {
                    count++;
                }
            }
        }
        if (count == 9) {
            win('D'); // Sending a random character that the if statement does not have a case for,
        }             // in order to go into the "else" statement
    }
}


void win(char player) {
    gameWon = true;
    system("cls");
    printTable();

    // Here i use the "player" argument to check which player won, in hindsight I could also have used the "currentPlayer" variable
    std::cout << std::endl;
    if (player == 'X') {
        if (aiMode) { std::cout << "You win!" << std::endl << std::endl; } // Cool quirk
        else { std::cout << "Player 1 wins!" << std::endl << std::endl; }
    }
    else if (player == 'O') {
        if (aiMode) { std::cout << "AI wins!" << std::endl << std::endl; }
        else { std::cout << "Player 2 wins!" << std::endl << std::endl; }
    }
    else {
        std::cout << "Draw!" << std::endl << std::endl;
    }

    for (int j = 1; j < 7; j++) { // Lightshow! 
        if (j % 2 == 0) {
            system("color E");
        }
        else {
            system("color A");
        }
        Sleep(200);
    }

    system("color F"); // Reset color

    char ans{};
    std::cout << "Play again? (y/n): ";
    std::cin >> ans;
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    if (ans == 'y' || ans == 'Y') {
        resetGame(0);
    }
    else {
        resetGame(1);
    }
}


void resetGame(int i) {
    system("cls");
    gameWon = false;

    for (int i = 0; i < 3; i++) { // Clear 2D array completely
        for (int k = 0; k < 3; k++) {
            arr[i][k] = ' ';
        }
    }

    playerX = 0;
    playerY = 0;
    currentPlayer = 1;

    if (i == 1) {
        gameRunning = false;
        aiMode = false;
    }
}


void aiTurn() { 
    int r1{ 0 }, r2{ 0 };
    do  // Here I use do-while because I want the iterator to be randomized before checking, else it will always place in 0, 0 
    {
        r1 = rand() % 3;
        r2 = rand() % 3;
    } while (arr[r1][r2] != ' '); // As long as the random chosen cell is not empty, run again

    arr[r1][r2] = 'O';
    checkScore();
    currentPlayer = 1;
}