#include "chk_function.h"



void chk_AntiLog_LButtonUp()
{
    // Nothing
}

void chk_LightHack_LButtonUp()
{
    // Nothing
}

void chk_UseEnemyList_LButtonUp()
{
    if( chkbox_UseEnemyList->is_ticked() == true )
    {   // Disable ...
        listB_EnemyList->set_znacznik(0);
        listB_EnemyList->set_enabled(false);
    }
    else
    {   // Enable ...
        listB_EnemyList->set_znacznik(0);
        listB_EnemyList->set_enabled(true);
    }
}

void chk_UseWaypointList_LButtonUp()
{
    if( chkbox_UseWaypointList->is_ticked() == true )
    {   // Disable ...
        listB_CaveBotCheckPoints->set_enabled(false);
        chkbox_RecWaypoints->set_ticked(false, false);
        chkbox_RecWaypoints->set_enabled(false);
    }
    else
    {   // Enable ...
        listB_CaveBotCheckPoints->set_enabled(true);
        chkbox_RecWaypoints->set_enabled(true);
    }
}

void chk_RecWaypoints_LButtonUp()
{
    if( chkbox_RecWaypoints->is_ticked() == true )
    {
        cavebot.m_wPointBot->dodaj_wayPoint( player.posx, player.posy, player.posz, 0 );
    }
}

void chk_UseEscapepointList_LButtonUp()
{
    
    
}

void chk_RecEscapepoints_LButtonUp()
{
    if( chkbox_RecEscapepoints->is_ticked() == true )
    {
        if( comBox_EscapeWayBox->get_value_index() == 0 )
        {
            chkbox_RecEscapepoints->set_ticked(false,false);
        }
        else
        {
            cavebot.m_ePointBot->record_EscapeWay( player );
        }
    }
    
}
