
/** @file Game.h
 *  @brief Function prototypes for the Game.
 *
 *  @author Jose Figueroa (TODO: Change for EXMAN ID)
 *  @TODO:
 *      @bug  - No known bugs.
 *      @TODO - In getCMD.
 *      @TODO - In get_angle_vel.
 *      @TODO - Create an end window with final score.
 *      @TODO - Multiplayer - Init Round
 *      @TODO -
 */

#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include "graphics_lib.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
#define WIN_WIDTH (960)             ///< WINDOW width constant.
#define WIN_LEN   (700)             ///< WINDOW Length constant.
#define GND       (FLOOR + 100.0)   ///< Ground Floor check with WIN_LEN
#define GRAVITY   (9.81)            ///< In game gravity.
#if !defined(PI)
#define PI        (3.14159f)        ///< PI Constant
#endif
#define SC_SIZE   (5)               ///< Number of Score Zones.
#define ATTEMPTS  (3)               ///< Number of attempts per play.

// Body Definitions
#define FLOOR     (500.0)           ///< Player Stick Reference.
#define BODYLEN   (70)              ///< Body longitude
#define BODYLEG   (20)              ///< LEG
#define ARMLEN    (35)              ///< ARM


#define DEG2RAD(x) (x*PI/180)       ///< Macro Function for Converting between Degrees and Radians

/*******************************************************************************
* Type definitions
*******************************************************************************/

/**
 * @name Projectile
 * @brief Represent a Projectile
 */
typedef struct Projectile
{
    /*@{*/
    double TotalVel;    /**< Magnitud of Vel Vector */
    double Angle;       /**< Angle of the Vel Vector */
    double IPos_x;      /**< Initial Position of Proyectile in Y axis */
    double IPos_y;      /**< Initial Position of Proyectile in X axis */
    /*@}*/
}Proy_t;

/**
 * @name Stickman
 * @brief Represent a player's stickman
 */
typedef struct Stickman
{
    /*@{*/
    int score;
    int IPos_x;      /**< Initial Position in X*/
    int IPos_y;      /**< Initial Position in Y*/
    int move_x;      /**< Current Position in x moved from IPos_x*/
    int color;       /**< Stick-man color*/
    Proy_t proy;     /**< Stick-man Projectile (Proy_t)*/
    /*@}*/
}Man_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief Core Game function.
 */
void Game_Init(void);

/** @brief Initialized variables for the player
 *
 *  @param [Man_t Ptr] Initialized the Player variables that would be used in the game.
 */
void InitPlayer(Man_t * Player);

/** @brief Will asked the user for a color using the Terminal
 *
 *  @return Return a char value representing a color value.
 */
char getColor(void);

/** @brief Initialize the round by changing the score position and get the player
 *          to its default position
 *         @TODO: Instead of Player reset all players.
 *
 *  @param [Man_t Ptr] Player struct.
 */
void initRound(Man_t * Player);

/** @brief Modify the x position of player if the left and right arrow keys or return a
 *          '\r' character if ENTER key was pressed.
 *         @TODO: Apply the keyboard functions in graphics lib.
 *
 *  @param [int Ptr] From Player struct we pass only the move_x.
 *
 *  @return Return '\r' if the ENTER key was pressed.
 */
int getCMD(int * move_x);

/** @brief Draw the floor and the score points of the game.
 *          The score can be moved by using the RandomPos global variable.
 */
void DrawFloor_DrawScore(void);

/** @brief Move the player position based on the Man_t parameters of the incoming player.
 *
 *  @param [Man_t Ptr] Player struct.
 */
void movePlayer(Man_t * Player);

/** @brief Get the angle and velocity, from the CMD, for the projectile and save it in the struct.
 *          TODO: Use the mouse functions from the graphics_lib to get the angle.
 *          TODO: Create another way to get the Vel.
 *  @param [Proy_t Ptr] Player struct.
 */
void get_angle_vel(Proy_t * proy);

/** @brief Calculate and draw the projectile trajectory from the final position of the player. The
 *          Trajectory is measure from the players hand until it hit the 'GND'.
 *
 *  @param [Man_t Ptr] Player struct.
 *
 *  @return Final Position of the projectile in the X axis.
 */
double proyectile(Man_t * Player);

/** @brief Calculate and draw the projectile trajectory from the final position of the player.
 *
 *  @param [int Ptr] Player score.
 *  @param [double] End Projectile position in x axis.
 */
void getScore(int * score, double EndProy_pos);

/** @brief Displays the Attempts and score in the game.
 *          TODO: Not modifiers so, no ptr needed.
 *
 *  @param [char Ptr] Current Attempr number.
 *  @param [int Ptr]  Current Score.
 */
void set_Score_Attempts(char nAtt, int score);

#endif
