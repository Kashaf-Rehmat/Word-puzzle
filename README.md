# Word Search Puzzle Game (C++)

A console-based Word Search Puzzle Game developed in C++. The game challenges players to find hidden words in a 15×15 puzzle board while managing limited attempts based on the selected difficulty level.

## Overview

This project was developed to practice core C++ programming concepts including arrays, functions, file handling, string manipulation, searching algorithms, and game-state management.

Players can start a new game, select a difficulty level, pause and resume progress, and earn points by finding words hidden within the puzzle grid.

## Features

- 15×15 word search puzzle board
- Three difficulty levels:
  - Easy (5 attempts)
  - Medium (3 attempts)
  - Hard (1 attempt)
- Search words in all 8 directions:
  - Left
  - Right
  - Up
  - Down
  - Top-left diagonal
  - Top-right diagonal
  - Bottom-left diagonal
  - Bottom-right diagonal
- Score tracking system
- Duplicate word detection
- Pause and resume functionality
- Save game progress using file handling
- Display previously found words
- Player name support
- Case-insensitive input handling

## Technologies Used

- C++
- Object-free procedural programming approach
- File Handling (`ifstream`, `ofstream`)
- Character Arrays
- String Processing (`cstring`)
- Searching Algorithms

## Project Structure

```text
Word_Search_Puzzle_Game/
│
├── Pasted code.cpp
├── board.txt
├── savegame.dat
└── README.md
```

## How to Run

### Compile

```bash
g++ "Pasted code.cpp" -o WordSearchGame
```

### Run

```bash
./WordSearchGame
```

## Game Controls

| Key | Function |
|-------|----------|
| N | Start New Game |
| R | Resume Saved Game |
| L | Set Difficulty Level |
| E | Exit Program |
| P | Pause Current Game |

## Scoring System

- Correct word: **+10 points**
- Duplicate word: **No additional points**
- Incorrect word: **One attempt is deducted**

## Save & Resume

The game automatically saves:

- Player Name
- Score
- Difficulty Level
- Remaining Attempts
- Found Words

Players can later resume their saved session from the main menu.

## Concepts Demonstrated

This project demonstrates:

- Multi-directional word searching
- File persistence
- Menu-driven application design
- Input validation
- State management
- Dynamic gameplay logic
- Use of arrays and character strings

## Future Improvements

- Random board generation
- Dictionary validation
- Hint system
- High score leaderboard
- Colored console interface
- Timer-based gameplay
- Graphical User Interface (GUI)

## Author

**Kashaf Rehmat**

BS Computer Science Student

## License

This project is developed for educational and learning purposes.
