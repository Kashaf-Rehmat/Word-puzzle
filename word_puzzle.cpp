
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

const int BOARD_SIZE   = 15;
const int MAX_FOUND    = 100;   
const int MAX_NAME_LEN = 50;
const int MAX_WORD_LEN = 20;

char   board[BOARD_SIZE][BOARD_SIZE + 1]; 
char   playerName[MAX_NAME_LEN];
int    score;
int    attemptsLeft;
int    difficultyLevel;     
char   foundWords[MAX_FOUND][MAX_WORD_LEN]; 
int    foundCount;
bool   gameActive;               

void  loadBoard(const char *filename);
void  showBoard();
void  showMenu();
char  getMenuChoice();
void  askPlayerName();
void  setDifficulty();
void  newGame();
void  resumeGame();
bool  searchWord(const char *word);
bool  alreadyFound(const char *word);
void  addToFound(const char *word);
void  toUpperStr(char *word);
void  playRound();
void  showStatus();
void  saveGame();
void  loadSavedGame();
bool  savedGameExists();

void loadBoard(const char *filename)
{
    ifstream fin(filename);
    if (!fin)
    {
        cout << "\nCannot open " << filename << "\n";
        cout << "  Make sure board.txt is in the same folder.\n";
        return;
    }
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        fin >> board[row];   
    }
    fin.close();
}

void showBoard()
{
    cout << "\n------------------------------------\n";
    cout << "            WORD PUZZLE BOARD         \n";
    cout << "  ------------------------------------\n";

    cout << "      ";
    for (int c = 0; c < BOARD_SIZE; c++)
        cout << c + 1 << (c + 1 < 10 ? "  " : " ");
    cout << "\n    ┌";
    for (int c = 0; c < BOARD_SIZE; c++)
        cout << "───";
    cout << "┐\n";

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        if (r + 1 < 10) cout << " ";
        cout << r + 1 << " │ ";
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            cout << board[r][c] << "  ";
        }
        cout << "│\n";
    }

    cout << "    └";
    for (int c = 0; c < BOARD_SIZE; c++)
        cout << "───";
    cout << "┘\n";
    cout << "  ╚══════════════════════════════════╝\n";
}

//  Show main menu 
void showMenu()
{
    cout << "\n";
    cout << "  ------------------------------------\n";
    cout << "  |         WORD PUZZLE GAME         |\n";
    cout << "  |----------------------------------|\n";
    cout << "  |   N  -  New Game                 |\n";
    cout << "  |   R  -  Resume Game              |\n";
    cout << "  |   L  -  Set Difficulty Level     |\n";
    cout << "  |   E  -  Exit                     |\n";
    cout << "  ------------------------------------\n";
}

// Get valid menu choice
char getMenuChoice()
{
    char choice;
    cout << "\n  Enter your choice : ";
    cin >> choice;
    return toupper(choice);
}

// Ask player name 
void askPlayerName()
{
    cout << "\n  Enter your name : ";
    cin >> playerName;
}

//  Set difficulty (updates attemptsLeft)
void setDifficulty()
{
    cout << "\n  ── Difficulty Levels ──────────────\n";
    cout << "  1. Easy   (5 attempts)\n";
    cout << "  2. Medium (3 attempts)\n";
    cout << "  3. Hard   (1 attempt )\n";
    cout << "  Choose (1/2/3) : ";

    int pick;
    cin >> pick;

    if (pick == 1)      { difficultyLevel = 1; attemptsLeft = 5; cout << "  Difficulty set to EASY.\n";   }
    else if (pick == 2) { difficultyLevel = 2; attemptsLeft = 3; cout << "  Difficulty set to MEDIUM.\n"; }
    else if (pick == 3) { difficultyLevel = 3; attemptsLeft = 1; cout << "  Difficulty set to HARD.\n";  }
    else                { cout << "  Invalid choice. Keeping previous setting.\n"; }
}

// Convert string to uppercase (in-place) 
void toUpperStr(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
        word[i] = toupper(word[i]);
}

// Check if word was already found 
bool alreadyFound(const char *word)
{
    for (int i = 0; i < foundCount; i++)
    {
        if (strcmp(foundWords[i], word) == 0)
            return true;
    }
    return false;
}

// Add word to found list
void addToFound(const char *word)
{
    if (foundCount < MAX_FOUND)
    {
        strncpy(foundWords[foundCount], word, MAX_WORD_LEN - 1);
        foundWords[foundCount][MAX_WORD_LEN - 1] = '\0';
        foundCount++;
    }
}

//  Search word on board (all 8 directions)
bool searchWord(const char *word)
{
    int wordLen = strlen(word);

    // 8 directions: right, left, down, up, 4 diagonals
    int dirRow[8] = {  0,  0,  1, -1,  1, -1,  1, -1 };
    int dirCol[8] = {  1, -1,  0,  0,  1, -1, -1,  1 };

    for (int startRow = 0; startRow < BOARD_SIZE; startRow++)
    {
        for (int startCol = 0; startCol < BOARD_SIZE; startCol++)
        {
            // try each direction from this cell
            for (int d = 0; d < 8; d++)
            {
                int row = startRow;
                int col = startCol;
                int matched = 0;

                while (matched < wordLen)
                {
                    // boundary check
                    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
                        break;

                    if (board[row][col] != word[matched])
                        break;

                    matched++;
                    row += dirRow[d];
                    col += dirCol[d];
                }

                if (matched == wordLen)
                    return true;   // found!
            }
        }
    }
    return false;
}

//  Show current game status 
void showStatus()
{
    cout << "\n ---Game Status---\n";
    cout << "  Player   : " << playerName     << "\n";
    cout << "  Score    : " << score          << "\n";
    cout << "  Attempts : " << attemptsLeft   << " remaining\n";

    const char *diffName = (difficultyLevel == 1) ? "Easy" :
                           (difficultyLevel == 2) ? "Medium" : "Hard";
    cout << "  Level    : " << diffName       << "\n";

    if (foundCount > 0)
    {
        cout << "  Words found so far : ";
        for (int i = 0; i < foundCount; i++)
        {
            cout << foundWords[i];
            if (i < foundCount - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "  --------------------------------\n";
}

//  Save game to file 
void saveGame()
{
    ofstream fout("savegame.dat");
    if (!fout) { cout << "  [Warning] Could not save game.\n"; return; }

    fout << playerName    << "\n";
    fout << score         << "\n";
    fout << attemptsLeft  << "\n";
    fout << difficultyLevel << "\n";
    fout << foundCount    << "\n";
    for (int i = 0; i < foundCount; i++)
        fout << foundWords[i] << "\n";

    fout.close();
    cout << "  Game saved!\n";
}

//  Load saved game from file 
void loadSavedGame()
{
    ifstream fin("savegame.dat");
    if (!fin) { cout << "  No saved game found.\n"; return; }

    fin >> playerName >> score >> attemptsLeft >> difficultyLevel >> foundCount;
    for (int i = 0; i < foundCount; i++)
        fin >> foundWords[i];

    fin.close();
    gameActive = true;
    cout << "  Saved game loaded for player: " << playerName << "\n";
}

//  Check if save file exists 
bool savedGameExists()
{
    ifstream fin("savegame.dat");
    return fin.good();
}

//  Start a fresh new game 
void newGame()
{
    // reset state
    score      = 0;
    foundCount = 0;
    gameActive = true;

    // set default difficulty if not set
    if (difficultyLevel == 0)
    {
        difficultyLevel = 1;
        attemptsLeft    = 5;
    }

    askPlayerName();
    showBoard();
    playRound();
}

//  Resume a paused game 
void resumeGame()
{
    if (!savedGameExists())
    {
        cout << "\n  No saved game found. Start a new game first.\n";
        return;
    }
    loadSavedGame();
    showBoard();
    playRound();
}

//  Core gameplay loop 
void playRound()
{
    char guess[MAX_WORD_LEN];

    cout << "\n  ---- HOW TO PLAY ----\n";
    cout << "  Type a word you see on the board.\n";
    cout << "  Type  P  to pause and go to menu.\n";
    cout << "  Type  E  to exit the game.\n";
    cout << "  ------------------------------\n\n";

    while (gameActive)
    {
        showStatus();
        cout << "\n  Your guess : ";
        cin >> guess;
        toUpperStr(guess);

        //  Pause 
        if (strcmp(guess, "P") == 0)
        {
            saveGame();
            cout << "\n  Game paused. Returning to menu...\n";
            gameActive = false;   // keeps global state, menu handles resume
            return;
        }

        //  Exit 
        if (strcmp(guess, "E") == 0)
        {
            saveGame();
            cout << "\n  Thanks for playing, " << playerName << "! Final score: " << score << "\n";
            gameActive = false;
            exit(0);
        }

        //  Already found? 
        if (alreadyFound(guess))
        {
            cout << "\n  You already found \"" << guess << "\"! Score stays at " << score << ".\n";
            continue;   // no attempt consumed
        }

        //  Search the board 
        if (searchWord(guess))
        {
            score += 10;
            addToFound(guess);
            cout << "\n  CORRECT! \"" << guess << "\" found! +10 points → Score: " << score << "\n";
        }
        else
        {
            attemptsLeft--;
            cout << "\n   Wrong! \"" << guess << "\" not found on the board.\n";
            cout << "  Attempts left: " << attemptsLeft << "\n";

            if (attemptsLeft <= 0)
            {
                cout << "\n  -----------------------------------\n";
                cout << "    GAME OVER!  You ran out of attempts.\n";
                cout << "    Final Score : " << score << "\n";
                cout << "    Player      : " << playerName << "\n";
                cout << "  --------------------------------------\n";

                // delete save file so no stale save remains
                remove("savegame.dat");
                gameActive = false;
                return;
            }
        }
    }
}

//  MAIN 
int main()
{
    // init global state
    score           = 0;
    foundCount      = 0;
    attemptsLeft    = 5;
    difficultyLevel = 1;  
    gameActive      = false;
    playerName[0]   = '\0';

    loadBoard("board.txt");

    char choice;
    bool running = true;

    while (running)
    {
        showMenu();
        choice = getMenuChoice();

        switch (choice)
        {
        case 'N':
            newGame();
            break;

        case 'R':
            resumeGame();
            break;

        case 'L':
            setDifficulty();
            break;

        case 'E':
            cout << "\n  Goodbye! Thanks for playing.\n\n";
            running = false;
            break;

        default:
            cout << "\n  Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
