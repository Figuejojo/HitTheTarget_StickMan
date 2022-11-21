
/** @file Game.c
 *  @brief Function definitions for the Game.
 *
 *  @author Jose Figueroa (TODO: Change for EXMAN ID)
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "Game.h"

/*******************************************************************************
* Static Variables
*******************************************************************************/
static int Target[SC_SIZE]   = {10,20,30,20,10};       // ScoreValues
static int TLock[SC_SIZE][2] = {{600,620},             // 20 pixels
                                {620,650}, {600,570},  // 30 pixels
                                {650,690}, {570,530}}; // 40 pixels
static int RandomPos  = 100;
static int DEF_POS_X   = 50;

/*******************************************************************************
* Functions
*******************************************************************************/
void Game_Init(void)
{
    Man_t  Player_1;

    InitPlayer(&Player_1);

    initwindow(WIN_WIDTH, WIN_LEN);

    for(char nATT = 0; nATT < ATTEMPTS; nATT++)
    {
        printf("\nAttempt %d",nATT+1);

        initRound(&Player_1);

        printf("\nClick the terminal and use the <- and -> to move");
        printf("\nWhen in position, hit ENTER");
        getch();

        do
        {

            cleardevice();

            DrawFloor_DrawScore();

            movePlayer(&Player_1);

            update_display();


        }while('\r' != getCMD(&Player_1));

        double FPPos = proyectile(&Player_1);

        getScore(&Player_1.score, FPPos);

        printf("\nCurrent Score %d",Player_1.score);
        printf("\nHIT ANY KEY TO CONTINUE");
    }

}

void getScore(int * score, double EndProy_pos)
{
    if(EndProy_pos >= TLock[0][0] && EndProy_pos <= TLock[0][1])
    {
        *score += Target[2];
    }
    else if ((EndProy_pos > TLock[1][0] && EndProy_pos <= TLock[1][1])
             ||(EndProy_pos < TLock[2][0] && EndProy_pos >= TLock[2][1]))
    {
        *score += Target[1];
    }
    else if ((EndProy_pos > TLock[3][0] && EndProy_pos <= TLock[3][1])
             ||(EndProy_pos < TLock[4][0] && EndProy_pos >= TLock[4][1]))
    {
        *score += Target[0];
    }
}

double proyectile(Man_t * Player)
{
    get_angle_vel(&Player->proy);

    moveto(Player->IPos_x + BODYLEG + Player->move_x, Player->IPos_y + BODYLEN);
    Player->proy.IPos_x = Player->IPos_x + BODYLEG + Player->move_x;

    double YVEL = Player->proy.TotalVel * sin(DEG2RAD(Player->proy.Angle));
    double XVEL = Player->proy.TotalVel * cos(DEG2RAD(Player->proy.Angle));

    double Proy_Pos_x  = Player->proy.IPos_x;
    double Pos_y = 0, time = 0;

    do
    {
        time =  (Proy_Pos_x - Player->proy.IPos_x) / XVEL;
        Pos_y = (Player->proy.IPos_y - (YVEL*time) + (GRAVITY*time*time)/2);
        lineto((int)Proy_Pos_x, (int)Pos_y, 1);
        Proy_Pos_x++;
        update_display();
    }while(Pos_y <= GND);

    return Proy_Pos_x;

}

void get_angle_vel(Proy_t * Proy)
{
    do
    {
        fflush(stdin);
        printf("\nWrite the Velocity: ");
    }while(scanf("%lf",&Proy->TotalVel) == 0);

    do
    {
        fflush(stdin);
        printf("\nWrite the Angle: ");
    }while(scanf("%lf",&Proy->Angle) == 0);
}

void DrawFloor_DrawScore()
{
	setcolor(WHITE);
    line(0  ,GND    ,WIN_WIDTH   ,GND    ,3);  //Floor

    int rPos = RandomPos;

    //50 Points
    line(TLock[0][0] + rPos ,GND + 15   ,TLock[0][0] + rPos ,GND - 15   ,1);
    line(TLock[0][1] + rPos ,GND + 15   ,TLock[0][1] + rPos ,GND - 15   ,1);
    //25 Points
    line(TLock[1][1] + rPos ,GND + 10   ,TLock[1][1] + rPos ,GND - 10   ,2);
    line(TLock[2][1] + rPos ,GND + 10   ,TLock[2][1] + rPos ,GND - 10   ,2);
    //10 Points
    line(TLock[3][1] + rPos ,GND + 5    ,TLock[3][1] + rPos ,GND - 5    ,3);
    line(TLock[4][1] + rPos ,GND + 5    ,TLock[4][1] + rPos ,GND - 5    ,3);

}

void movePlayer(Man_t * Player)
{
    setcolor(Player->color);
    filled_circle(Player->IPos_x + Player->move_x,  Player->IPos_y, 15, Player->color);

    line(Player->IPos_x + Player->move_x  ,Player->IPos_y + 9        ,Player->IPos_x + Player->move_x            ,Player->IPos_y + BODYLEN ,2);     //Body
	line(Player->IPos_x + Player->move_x  ,Player->IPos_y + BODYLEN  ,Player->IPos_x + BODYLEG + Player->move_x  ,Player->IPos_y + 100     ,2);  //Leg Right
	line(Player->IPos_x + Player->move_x  ,Player->IPos_y + BODYLEN  ,Player->IPos_x - BODYLEG + Player->move_x  ,Player->IPos_y + 100     ,2);  //Leg Left
    line(Player->IPos_x + Player->move_x  ,Player->IPos_y + ARMLEN   ,Player->IPos_x - BODYLEG + Player->move_x  ,Player->IPos_y + BODYLEN ,2);  //Arm Left
	line(Player->IPos_x + Player->move_x  ,Player->IPos_y + ARMLEN   ,Player->IPos_x + BODYLEG + Player->move_x  ,Player->IPos_y + BODYLEN ,2);  //Arm Right
}

int getCMD(Man_t * Player)
{
    int cmd = getch();
    cmd = (cmd == 0) ? (getch()):(cmd);

    switch(cmd)
    {
        case 77: //Right
            //TODO: Change this for the score left extreme.
            if(Player->move_x < WIN_WIDTH - BODYLEN)
            {
                Player->move_x++;
            }
            break;
        case 75: //Left
            if(Player->move_x > 0 - (DEF_POS_X - BODYLEG))
            {
                Player->move_x--;
            }
            break;
        default:
            break;
    }
    return cmd;
}

void initRound(Man_t * Player)
{
    Player->move_x = 0; // Return player to default position.
    RandomPos = 0;      // TODO: Change for a random position.
}

void InitPlayer(Man_t * Player)
{
    Player->score = 0;
    Player->color = getColor();
    Player->IPos_x = DEF_POS_X;    //The position is fixed right now but can be changed based on ?Difficulty??/Random?
    Player->IPos_y = FLOOR;
    Player->move_x = 0;
    Player->proy.IPos_y = Player->IPos_y + BODYLEN;
}

//TODO: Iterate until a color is chosen
//TODO: For multiplayer there we must know if the color has already being picked.
char getColor(void)
{
    printf("Chose your character color (use the first letter)\n\tred\n\tblue\n\tgreen \nSelect: ");
    char color = getch();
    //Validation of the getch.
    color = (color==0) ? color : getchar();

    //Assign the color value
    switch(color)
    {
        // Increase or decrese using the ENUM values.
        case 'r':
            color = 4; //RED;
            break;
        case 'b':
            color = 1;  //BLUE;
            break;
        case 'g':
            color = 2; //GREEN;
            break;
        default:
            color =  3; //CYAN;
            break;
    }

    return color;
}
