#ifndef ENUMS_H
#define ENUMS_H

enum BUTTON_STD_TYPE
{
     BST_CONNECT,
     BST_DCONNECT,
     BST_START,
     BST_EXITTOMENU,
     BST_STARTSERVER,
     BST_NONE
};

enum RADIO_BUTTON_TYPE
{
     RBT_PvsP,              // 1
     RBT_PvsCOM,            // 1
     RBT_PvsP_ONLINE,       // 1
     RBT_SERVER,            // 2
     RBT_CLIENT,            // 2
     RBT_NONE
};

enum PROGRAM_ID
{
     PID_MENU_GLOWNE,
     PID_ROZGRYWKA,
     PID_NONE
};

enum GAMETYPE
{
     GT_PP,
     GT_PCOM,
     GT_S,
     GT_C,
     GT_NONE
};

enum GRACZ_PLAYER
{
     GP_X,
     GP_O,
     GP_REMIS,
     GP_NONE
};
     
     
// Szary-okna 236, 233, 216



#endif
