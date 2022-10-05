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
    pwmController.setChannelPWM(0,  0);  // set to zero all motor
    pwmController.setChannelOff(1);
    pwmController.setChannelPWM(2,  0);  // set to zero all motor
    pwmController.setChannelOff(3);
    pwmController.setChannelPWM(4,  0);  // set to zero all motor
    pwmController.setChannelOff(5);
    pwmController.setChannelPWM(6,  0);  // set to zero all motor
    pwmController.setChannelOff(7);
  }

  /* When is connected */
  else {
    
    /* Update motor value with joystick value */
    if(RemoteXY.joystick_1_x > 0) {
      pwmController.setChannelPWM(1, map(RemoteXY.joystick_1_x, 0, 100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(0);
    }
    else if(RemoteXY.joystick_1_x < 0) {
      pwmController.setChannelPWM(0, map(RemoteXY.joystick_1_x, 0, -100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(1);
    }
    else {
      pwmController.setChannelOff(0);
      pwmController.setChannelOff(1);
    }


    if(RemoteXY.joystick_1_y > 0) {
      pwmController.setChannelPWM(3, map(RemoteXY.joystick_1_y, 0, 100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(2);
    }
    else if(RemoteXY.joystick_1_y < 0) {
      pwmController.setChannelPWM(2, map(RemoteXY.joystick_1_y, 0, -100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(3);
    }
    else {
      pwmController.setChannelOff(2);
      pwmController.setChannelOff(3);
    }


    // manage joystick_2_x
    if(RemoteXY.joystick_2_x > 0) {
      pwmController.setChannelPWM(5, map(RemoteXY.joystick_2_x, 0, 100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(4);
    }
    else if(RemoteXY.joystick_2_x < 0) {
      pwmController.setChannelPWM(4, map(RemoteXY.joystick_2_x, 0, -100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(5);
    }
    else {
      pwmController.setChannelOff(4);
      pwmController.setChannelOff(5);
    }


    // manage joystick_2_y
    if(RemoteXY.joystick_2_y > 0) {
      pwmController.setChannelPWM(7, map(RemoteXY.joystick_2_y, 0, 100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(6);
    }
    else if(RemoteXY.joystick_2_y < 0) {
      pwmController.setChannelPWM(6, map(RemoteXY.joystick_2_y, 0, -100, 0, 4096));  // set to zero all motor
      pwmController.setChannelOff(7);
    }
    else {
      pwmController.setChannelOff(6);
      pwmController.setChannelOff(7);
    }
  }
}