//
//  KilobotInterfaceEmulator.cpp
//  roborobo
//
//  Created by Nicolas Bredeche on 02/08/12.
//

#include <stddef.h>

#include "BasicProject-Kilobot/include/KilobotInterfaceEmulator.h"


void KilobotInterfaceEmulator::updateKilobotWorld()
{
    // computer network relation
    // update message list for all robots
    // call updateKilobot() for all kilobot
}

void KilobotInterfaceEmulator::registerKilobot( KilobotInterfaceEmulator kilobot )
{
    kilobots.push_back(kilobot);
}

// * * *

KilobotInterfaceEmulator::KilobotInterfaceEmulator()
{
    kilobot__enable_tx = 0;
    KilobotInterfaceEmulator::registerKilobot(*this);
}

KilobotInterfaceEmulator::~KilobotInterfaceEmulator()
{
}

void KilobotInterfaceEmulator::updateKilobot()
{
    // set motor
}

//### From Kilobot doc (for information only):
//set_motor(cw_motor,ccw_motor)
//set motor speed PWM values for motors between 0 (off) and 255 (full on)
void KilobotInterfaceEmulator::kilobot_set_motor( int left, int right )
{
    
}

//### From Kilobot doc (for information only):
//message_out(tx0,tx1);
//set message values to be sent over IR every .2 seconds, 2 bytes tx0,tx1
void KilobotInterfaceEmulator::kilobot__message_out(int tx0, int tx1)
{
    
}

//### From Kilobot doc (for information only):
//get_message();
//take oldest message off of rx buffer
//message is only new if message_rx[5]==1 !
//if so, message is in message_rx[0],message_rx[1] //distance to transmitting robot (in mm) is in message_rx[3]
int* KilobotInterfaceEmulator::kilobot__get_message()
{
    return NULL;
}

//### From Kilobot doc (for information only):
//set_color(r,g,b);
//set LED color, values can be from 0(off) to 3(brightest)
void KilobotInterfaceEmulator::kilobot__set_color( int r, int g, int b )
{
    
}

//### From Kilobot doc (for information only):
//get_ambient_light();
//returns the value of ambient light
//note: will return -1 if there is an incoming message (which also uses a/d) //note: turns off interrupts for a short while to sample a/d
int KilobotInterfaceEmulator::kilobot__getAmbiantLight()
{
    return NULL;
}