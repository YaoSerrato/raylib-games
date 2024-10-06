# Snake game
Snake game developed using Raylib and C++ using Visual Studio Code on Windows.
It works with raylib version 5.0.

## How to build and run the application
1. Double click on the main.code-workspace file. This will open the template in VS Code.
2. From the Explorer Window of VS Code navigate to the src folder and double click on the main.cpp file.
3. Press F5 (or Fn+F5) on the keyboard to compile and run the program.

## Known issues
- There is no current score limit so the score could overflow (after 0xFFFF FFFF points, though).

## Nice-to-have´s
- Init screen where the user can enter its user name.
- Store in a file the points scored per user.
- Add music during init menu.
- Add sound effects on collisions with snake and with the screen border.
- Add option to select the theme of the game. There could be a dark theme, a light theme, a high-contrast theme, etc.
- Add PAUSE, RESUME and QUIT options to the game (QUIT option would return to init menu).
- When losing, display a screen showing the top three scores so far.

## Acknowledgements
This application was developed with **raylib** library for developing games and also by following a tutorial from **Programming With Nick** YouTube channel.

