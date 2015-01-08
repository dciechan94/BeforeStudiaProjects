#include "btn_function.h"


void btn_LOADPROFILE_LButtonUp()
{
    
    
}

void btn_SAVEPROFILE_LButtonUp()
{
    
    
}

void btn_EXITPROFILE_LButtonUp()
{
    program_quit_flag = true;
}

void btn_INFO_LButtonUp()
{
    menu_tab = MT_MENU1;
}

void btn_ATTACK_LButtonUp()
{
    menu_tab = MT_MENU2;
}

void btn_CAVEBOT_LButtonUp()
{
    menu_tab = MT_MENU3;
}

void btn_ESCAPE_LButtonUp()
{
    menu_tab = MT_MENU4;
}

void btn_AddToEnemy_LButtonUp()
{
    
    
}

void btn_DeleteFromEnemy_LButtonUp()
{
    
    
}

void btn_DelWaypointList_LButtonUp()
{
    /*if( chkbox_UseWaypointList->is_ticked() == false )
    {
        chkbox_RecWaypoints->set_ticked(false);
        listB_CaveBotCheckPoints->usun( listB_CaveBotCheckPoints->get_znacznik() );
        cavebot.usun_wayPoint( listB_CaveBotCheckPoints->get_znacznik() );
    }*/
}

void btn_DelAllWaypointList_LButtonUp()
{
    /*if( chkbox_UseWaypointList->is_ticked() == false )
    {
        chkbox_RecWaypoints->set_ticked(false);
        listB_CaveBotCheckPoints->usun_all();
        cavebot.usun_wayPointy();
    }*/
}

void btn_RopeToWaypointList_LButtonUp()
{
    /*if( chkbox_UseWaypointList->is_ticked() == false )
    {
        if( chkbox_RecWaypoints->is_ticked() == true )
        {
            cavebot.dodaj_wayPoint( player.posx, player.posy, player.posz, 0 );
            cavebot.dodaj_wayPoint( player.posx, player.posy, player.posz, 5 );
        }
    }*/
}

void btn_StepLeftWaypointList_LButtonUp()
{
    
    
}

void btn_StepRightWaypointList_LButtonUp()
{
    
    
}

void btn_StepUpWaypointList_LButtonUp()
{
    
    
}

void btn_StepDownWaypointList_LButtonUp()
{
    
    
}
void btn_SewerGrateWaypointList_LButtonUp()
{
    
    
}
void btn_SaveWaypointList_LButtonUp()
{
    
    
}
void btn_LoadWaypointList_LButtonUp()
{
    
    
}
void btn_HealOnEscapeWay_LButtonUp()
{
    
    
}
void btn_NewEscapeWay_LButtonUp()
{
    
    
}
void btn_DelEscapeWay_LButtonUp()
{
    
    
}
