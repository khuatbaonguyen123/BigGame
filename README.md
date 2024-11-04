# TETRIS SDL2
> Course Project: Advanced Programming Techniques (INT2215 1) Group 6
> Khuất Bảo Nguyên - Student ID: 22026508

## Installation
> - Download the .rar file, extract the files, and click on main.exe to play.

## Game Concept/Description
### 1. Introduction

- Tetris is a tile-matching game where players aim to arrange blocks to fill a row and clear it.
- The game is not about winning or losing but rather scoring points. When the game is over, the player's score is displayed.

### 2. How to Play

- The objective is to move falling blocks within a 20-row by 10-column rectangle (displayed on screen). Blocks cannot move to occupied spaces. Players must arrange the blocks to fill horizontal lines to score points; the filled line will then disappear.
- The game ends if the blocks stack too high on the screen.
- The game is over when a block can no longer fall.
- All Tetriminos can complete one or two lines. J and L pieces can clear up to three lines. Only the I Tetrimino can clear four lines simultaneously, known as a "Tetris". A maximum of 4 rows can be cleared at a time.

### 3. Controls
- Rotate block: Up arrow key ↑.
- Move right: Right arrow key →.
- Move left: Left arrow key ←.
- Accelerate block fall: Down arrow key ↓.
- Hold a block for later use: Space key.
- ***Hard Drop*** - immediately drop the block: Enter key.

***Illustrative Images***

![Tetris_Menu](Tetris_Menu.jpg)

![Tetris_Play](Tetris_Play.jpg)

## Reason for Choosing the Game

As a former English major in high school with no programming background, I chose Tetris because it is a classic game with many available tutorials for guidance during development.

## Main Features

### 1. Game Logic
- Clear blocks after filling a row.
- Rotate blocks.
- Show the next block.
- Hold a block.
- Multiple levels (determined by block fall speed).
- Calculate and save the highest score.

### 2. Sound and Visual Effects

- Sound:
> Background music, sound effects for block movement, rotation, line clearing, block dropping, and game over.
- Visuals:
> Delays when clearing lines, transitions between states, creating effects.
> 
> Notably, I believe the game visuals were designed carefully, with attention to detail to create an engaging experience for players.

### 3. Additional Features

- Detailed menu: includes Play button, Settings (toggle music, sound effects, adjust game level), and quit button.
- Ability to pause the game: resume, restart, adjust sound/music, or return to the main menu.
- Display score after a game ends, save and display the highest score during gameplay.

## Techniques Used
- Image rendering, sound playback, mouse/keyboard management, time handling (SDL).
- Utilized classes, pointers, randomization, arrays, files, etc.
- Divided objects into separate files for easier operation and management.
- Rotation algorithm...
- Implemented a rotation algorithm for the Tetriminos.
- Managed the game grid to detect and handle filled rows.
- Used file handling for saving and loading high scores.
- Created modular code by dividing functionalities into multiple files for clarity and maintainability.

## Lessons Learned and Challenges
- Implementing the logic for rotating and handling the positioning of Tetriminos was challenging but rewarding.
- Managing game state transitions and ensuring that the game responded smoothly to user input required careful attention.
- Understanding how to integrate sound and visual effects using SDL2 enhanced my understanding of multimedia handling in programming.
- Balancing gameplay elements such as level progression and block drop speed added complexity to the design.

## Future Improvements
- Adding more advanced game mechanics, such as power-ups or special Tetrimino effects.
- Implementing a multiplayer mode for competitive play.
- Enhancing the user interface with more customizable options and themes.
- Creating a more complex scoring system with bonuses for consecutive line clears.

## Conclusion
Developing this Tetris game using SDL2 was an educational experience that combined multiple aspects of game programming, from logic and object-oriented design to sound and visual integration. This project allowed me to deepen my understanding of programming concepts and learn how to build a complete, interactive application.

Thank you for reading, and I hope you enjoy playing my version of Tetris!
