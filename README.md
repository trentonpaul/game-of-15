# Game of 15
Face an AI in the Game of 15 (aka [Numerical Tic Tac Toe](https://mathequalslove.net/numerical-tic-tac-toe/))
## Overview
- This is a Game of 15 automation program written in C++. The AI uses [Minimax](https://en.wikipedia.org/wiki/Minimax) with [Alpha Beta Pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) to calculate the optimal next move for any given board.
- This software is very CPU-bound as it uses BFS and multithreading to run several calculations in parallel.
- This program was written for Windows and hasn't been tested on other platforms.
## How to Play
- Use `./batch./runmain.bat` to compile and run the executable
- The game will prompt you `Enter the board:` at which point you enter your game board in the format `(a,b,c,d,e,f,g,h,i)` and press `Enter`
- Entering `(0,0,0,0,0,0,0,0,0) indicates an empty board and the AI will play first on the ODDS team
- Entering a board with 1 odd number already placed indicates that you will play as ODDS and the AI as EVENS
- From there, the AI will respond with its next move and you will have to enter the next board position.
- This continues until one player wins the game or it ends in a tie.
