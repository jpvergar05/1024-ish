Overview
This program is a console-based game inspired by the popular game 2048, implemented in C++. The game is played on a 4x4 grid, where the player slides tiles in four directions (up, down, left, right). The objective is to combine tiles containing powers of 2 to reach the target number (e.g., 256, 512, or 1024, depending on the difficulty level).

Features
Three Difficulty Levels:

Easy: Target is 256; higher probability of generating higher-value tiles.
Medium: Target is 512.
Hard: Target is 1024; lower probability of generating higher-value tiles.
Dynamic Tile Movement:

Tiles slide and merge based on direction input (U, D, L, R).
Numbers combine only if they are equal and haven’t already merged in the current move.
Random Tile Generation:

Each move generates a new tile (2 or 4) at a random empty position.
The probabilities of generating tiles depend on the difficulty level.
Winning and Losing Conditions:

Win: When a tile reaches the target value.
Lose: When no valid moves are available.
User-Friendly Console UI:

The grid is displayed after every move with clear formatting.
Custom Random Seed:

Allows deterministic runs for testing by setting a random seed.
Quit Option:

Players can exit the game anytime by entering Q.
How to Play
Start the Game:

Compile and run the program.
Enter a random seed value to initialize the random number generator.
Select Difficulty Level:

Choose from Easy (E), Medium (M), or Hard (H).
Game Controls:

U: Slide tiles up.
D: Slide tiles down.
L: Slide tiles left.
R: Slide tiles right.
Q: Quit the game.
Gameplay:

Tiles with the same number merge when slid into each other.
The merged tile’s value is doubled.
Continue sliding and merging tiles to reach the target value.
Winning:

The game announces "You win!" when you achieve the target value.
Losing:

If no moves are possible, the game announces "You lose."
