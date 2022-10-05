/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL
#include <Arduino.h>
#include <RemoteXY.h>
#include "PCA9685.h"

PCA9685 pwmController;  
       
// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 28 bytes
  { 255,4,0,0,0,21,0,16,31,0,5,32,0,17,30,30,2,26,31,5,
  32,70,18,30,30,2,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  int8_t joystick_2_x; // from -100 to 100  
  int8_t joystick_2_y; // from -100 to 100  

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


/* Init section */
void setup() 
{
  RemoteXY_Init ();

  Wire.begin();
  
  pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line

  pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer

  pwmController.setPWMFrequency(100); // Set PWM freq to 100Hz (default is 200Hz, supports 24Hz to 1526Hz)
  
}



/* Main polling loop */
void loop() 
{ 
  /* Polling manager for RemoteXY */
  RemoteXY_Handler ();
  
  if(RemoteXY.connect_flag == false){
    pwmController.setChannelPWM(0,  128 << 4);  // set to zero all motor
    pwmController.setChannelPWM(1,  128 << 4);  // set to zero all motor
    pwmController.setChannelPWM(2,  128 << 4);  // set to zero all motor
    pwmController.setChannelPWM(3,  128 << 4);  // set to zero all motor
  }

  /* When is connected */
  else {
    
    /* Update motor value with joystick value */
    uint8_t joystick_1_x = map(RemoteXY.joystick_1_x,-100,100,128,255);
    pwmController.setChannelPWM(0,  joystick_1_x << 4);

    uint8_t joystick_1_y = map(RemoteXY.joystick_1_y,-100,100,128,255);
    pwmController.setChannelPWM(1,  joystick_1_y << 4);

    uint8_t joystick_2_x = map(RemoteXY.joystick_2_x,-100,100,128,255);
    pwmController.setChannelPWM(2,  joystick_2_x << 4);

    uint8_t joystick_2_y = map(RemoteXY.joystick_2_x,-100,100,128,255);
    pwmController.setChannelPWM(3,  joystick_2_y << 4);

  }
}