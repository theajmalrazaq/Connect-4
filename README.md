# Connect Four Game

Welcome to the Connect Four game implementation in C++!

## Introduction

Connect Four is a two-player connection game in which the players  take turns by slecting column occupying the lowest available space within the column. The object of the game is to connect four of one's own symbol vertically, horizontally, or diagonally before your opponent.

## How to Play

1. Run the program.
2. Choose an option from the main menu:
    - Play: Start a new game.
    - Exit: Quit the game.
    - Credits: View credits.
    - Instructions: Learn how to play.
    - Record: View game records.

3. If you choose to play:
1. Players take turns dropping by selecting one of seven columns into a 6x7 Board.
2. The goal is to connect four 'X' or 'O'  in a Board.
3. Connections can be horizontal, vertical, or diagonal.
4. The first to achieve this wins, or it's a draw if the Board is full.

## Features

- Two-player turn-based gameplay.
- Toss to determine the starting player.
- Keep track of scores for Player 1 and Player 2.
- Record and view game results.
- Simple console-based user interface.

## Game Files

- **main.cpp**: The main C++ source code.
- **Scores.txt**: File to store game records.

## Usage

Compile and run the `ConnectFour.cpp` file using a C++ compiler.

```bash
g++ main.cpp -o main
./main
```

## Additional Information

- This game was created as a collaborative project by Usman Dilbar and Ajmal Razaq.
- For more information, check the game credits and instructions within the program.

## Credits

Game made by:
- Usman Dilbar
- Ajmal Razaq

Feel free to customize and expand this README to include more details about the game, how to compile/run it, or any additional features you'd like to highlight.
