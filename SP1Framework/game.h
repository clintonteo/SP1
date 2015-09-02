#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "UI.h"


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SELECT,
	K_USE,
    K_SPACE,
	K_RESET,
    K_ENTER,
	K_BACK,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_MENU,
	S_OPTIONS,
	S_HELP,
	S_HIGHSCORE,
    S_TUTORIAL,
    S_SPLASHSCREEN,
    S_GAME1,
	S_SPLASHSCREEN2,
	S_GAME2,
	S_SPLASHSCREEN3,
	S_GAME3,
	S_SPLASHSCREEN4,
	S_GAME4,
    S_NAME,
    S_GAMEOVER,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory
void reset();

void splashScreenWait();    // waits for time to pass in splash screen
void splashStage2Wait();    // waits for time to pass in splash screen
void splashStage3Wait();
void splashStage4Wait();
void splashGameoverWait();

void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderSplashStage2();  // renders the splash screen
void renderSplashStage3();
void renderSplashStage4();

void renderEnterName();
void renderGameover();
void renderGame();// renders the game stuff

void renderStage1();
void renderStage2();
void renderStage3();
void renderStage4();
void renderTutorial();

void renderMap();           // renders the map to the buffer first
void renderCharacter(player&user);     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void mainMenu(Console&Console, player&user);
void exit();
void options(Console&Console, player&user);
void help(Console &Console, player&user);
void highscoreMenu(Console&g_Console, player&user);

void EnterName();

#endif // _GAME_H