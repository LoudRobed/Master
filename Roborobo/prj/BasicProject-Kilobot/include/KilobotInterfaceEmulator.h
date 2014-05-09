//
//  KilobotInterfaceEmulator.h
//  roborobo
//
//  Created by Nicolas Bredeche on 02/08/12.
//

#ifndef roborobo_KilobotInterfaceEmulator_h
#define roborobo_KilobotInterfaceEmulator_h

#include <vector.h>

// A very simplified, minimal, emulation of kilobot main functions

class KilobotInterfaceEmulator {
    
    private:
    
    static std::vector<KilobotInterfaceEmulator*> kilobots;
    
    public:
    
    // * * * General purpose management methods for emulating Kilobot
    
    void static updateKilobotWorld(); // called by Roborobo
    void static registerKilobot(KilobotInterfaceEmulator agent);
    
    // * * * Kilobot level management methods used by Roborobo
    
    KilobotInterfaceEmulator();
    ~KilobotInterfaceEmulator();
    
    void updateKilobot();  // called by Roborobo.

    // * * * KILOBOT-related methods (i.e. comparable to what you would get/use on a real Kilobot)
    
    //### From Kilobot doc (for information only): (note that here, it is initialized in the constructor)
    //enable_tx
    //to turn off the transmitter, set enable_tx = 0 //to turn on the transmitter, set enable_tx = 1 
    //Example:
    //  if(Want_To_Transmit==TRUE)
    //    enable_tx = 1; 
    //  else
    //    enable_tx = 0;
    int kilobot__enable_tx;
    
    //### From Kilobot doc (for information only):
    //set_motor(cw_motor,ccw_motor)
    //set motor speed PWM values for motors between 0 (off) and 255 (full on)
    void kilobot_set_motor( int left, int right );
    
    //### From Kilobot doc (for information only):
    //message_out(tx0,tx1);
    //set message values to be sent over IR every .2 seconds, 2 bytes tx0,tx1
    void kilobot__message_out(int tx0, int tx1);
    
    //### From Kilobot doc (for information only):
    //get_message();
    //take oldest message off of rx buffer
    //message is only new if message_rx[5]==1 !
    //if so, message is in message_rx[0],message_rx[1] //distance to transmitting robot (in mm) is in message_rx[3]
    int* kilobot__get_message();
    
    //### From Kilobot doc (for information only): 
    //set_color(r,g,b);
    //set LED color, values can be from 0(off) to 3(brightest)
    void kilobot__set_color( int r, int g, int b );
    
    //### From Kilobot doc (for information only):
    //get_ambient_light();
    //returns the value of ambient light
    //note: will return -1 if there is an incoming message (which also uses a/d) //note: turns off interrupts for a short while to sample a/d
    int kilobot__getAmbiantLight();
    


};

#endif

