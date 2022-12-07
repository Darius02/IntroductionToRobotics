# Tetris Game

The purpose of the Tetris game is to destroy the rows of blocks before any of it reaches the top. There are four-connected blocks of different types that will fall down and the player has to choose wherever they lay down in order to create rows that fill the box horizontally, resulting in destroying that specific filled row.

## Hardware used:

- 8x8 LED Matrix
- LCD Display
- Joystick for navigating through the game menu
- Potentiometer to control the brightness

## Game Description:

- Score: Every time a row of blocks is destroyed, the score increases by 8 (number of blocks on a row) multiplied by the level the player has reached.
- Difficulty : The game has 3 difficulties: easy, medium and hard. It can be changed in Setup. From the easy difficulty to hard difficulty, it will increase the speed. In this way, the hard level will be 3 times faster than the first one and the medium level will be 2 times faster than the first one.
- Lives: The player has only 3 lives. They have the chance to play the game without resetting the score until it loses all the lives. When all chances are lost, the player is asked if he wants to play again or go back to the main menu.
- Highscore: The highscore will be kept in the EEPROM memory. The highscore can be reset.
- While navigating through the menu, the logo of the game will be displayed.

Picture of the setup:

![IMG_0164](https://user-images.githubusercontent.com/75308520/206288721-2aadf210-910b-45cf-bbb0-d40e47772470.jpg)

[Video of the game menu (unfinished)](https://www.youtube.com/watch?v=Na0qpk1AdgE)
