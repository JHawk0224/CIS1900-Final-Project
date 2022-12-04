# CIS1900-Final-Project
Jordan Hochman's Final Projcet for CIS 1900 (C++)

Project Proposal (Edited):
I would like to make Snake in C++, and to make it more complex, I will add extra features. This includes being able to save/load the game state from a file, and having powerups (special apples) that do certain things (like make snake invincible for a short time, place multiple apples, speed it up, and etc.)

For this project, I plan to use a vector of vectors to make the 2D array for the game board. I also plan to have a class heirarchy for the apples, as the powerups will just be different types of apples. There will be a base apple, and then other apples that have special properties and create special effects. They will also have different looks on the game board. Additionally, there will be a Snake class so that multiple snakes can be added to the board with different characteristics (like color maybe). The game will be text-based and be operated in a similar manner to the midterm project, minesweeper (I also might use ANSI text to color the terminal output).

To expand on this, the interface will let you use commands such as new <x> <y> to create a new snake game and quit to exit. Additionally, I will use a TUI interface to render the game in the terminal (probably TermOx), but for the first checkpoint, the games' logic ticks will be controlled manually through the command tick.

I am going to be in a group by myself for this final project, so I will be doing all of the work and thus there is no need to split up the work. I will split up my time accordingly to whichever parts take the longest, and I am not expecting to have to focus more time on a specific part.
By the first checkpoint, I will have the basic game done, with a class for the snake, the class for the game, and the main file completed. This is a priority since it is needed to continue working on the more complicated stuff. Then I will work on rendering the game properly with a TUI library and getting the controls to work. Then I will work on adding powerups, and finally, saving/loading the game to/from a file.

I am also open to implementing other features or suggestions you have to improve my project or use more concepts we learned in class.
