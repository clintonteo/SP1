#include <iostream>

#include "UI.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
// UI THINGY

//Divider
void divider()
{
    for (int i = 0; i < 28; ++i)
    {
        gotoXY(50,i);
        cout << "|";
    }
}



//Timer Notification
void timer(double g_dElapsedTime)
{
    gotoXY(51,0);
    if ((g_dElapsedTime >= 120) && (g_dElapsedTime <= 130))
    {
        cout << "Time is "<< g_dElapsedTime << "! You have a min left!";
    }
    if ((g_dElapsedTime >= 500) && (g_dElapsedTime <= 510))
    {
        cout << "Time is "<< g_dElapsedTime << "! You have a min left!";
    }
    if ((g_dElapsedTime >= 480) && (g_dElapsedTime <= 490))
    {
        cout << "Time is "<< g_dElapsedTime << "! You have a min left!";
    }

    //Timer
    gotoXY(51,1);
    cout << "Timer:";
    gotoXY(51,2);
    cout << g_dElapsedTime;
}
    

//Lives
void lives( player & user )
{
    gotoXY(51,3);

    cout << "Lives: ";
    gotoXY(51,4);
    for (int count = 1; count <= user.lives; ++count)
    {
        cout << (char)1 << "  ";
    }

}


////Damage Taken
//void damagetaken(bool damage, player user)
//{
//    if (damage == 1)
//    {
//        user.lives -= 1;
//    }
//}


//Render Inventory
void renderInventory( player & user )
{
    gotoXY(51,5);
    cout << "Inventory: ";
    
    gotoXY(51,6);

    for (int i = 0; i < user.inventoryitems.size(); ++i)
    {
        if (user.inventory[0] == 't')
        {
            cout << i+1 << ". " << user.inventoryitems[i] << " ";
            gotoXY(51,6+i);
        }
        /*if (user.inventory[1] == 't')
        {
            cout << "2. " << user.inventory1 << " ";
            gotoXY(51,8);
        }
        if (user.inventory[2] == 't')
        {
            cout << "3. " << user.inventory2 << " ";
            gotoXY(51,9);
        }
        if (user.inventory[3] == 't')
        {
            cout << "4. " << user.inventory3 << " ";
            gotoXY(51,10);
        }
        if (user.inventory[4] == 't')
        {
            cout << "5. " << user.inventory4 << " ";
            gotoXY(51,11);
        }
        if (user.inventory[5] == 't')
        {
            cout << "6. " << user.inventory5 << " ";
            gotoXY(51,12);
        }*/
    }
    
}

void point( player & user )
{
    gotoXY(51,15);
    
    cout << "Points: " << user.points;
}

void selector( player & user )
{
    gotoXY(51, 13);
    cout << "Item " << user.select << " selected.";
}
    