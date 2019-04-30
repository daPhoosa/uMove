/*
 *    uMove library example
 *       by Phillip Schmidt
 *    
 *    This example outputs three moves to the serial output using the three different setMove functions
 * 
 */

#include <uMove.h>

const float maxVel = 120.0f; // mm/s
const float Accel  = 100.0f; // mm/s^2

uMove motion( maxVel, Accel );


void setup() {

   Serial.begin(250000);
   while( !Serial ) {} // wait for serial to connect

   // *** FIRST MOVE ***
   motion.setPosition( -15.0f ); // set current position (mm)
   
   motion.setMove( 50.0f );      // end point (mm) -- move at max speed
   motion.startMoving();

   do
   {
      Serial.println( motion.getPosition(), 3 ); // output position until end point is reached
      delay(9);
   }
   while( !motion.moveComplete() ); // check if move is complete

   // *** SECOND MOVE ***
   motion.setMove( 0.0f, 30.0f );      // end point (mm) -- move at 30mm/s
   motion.startMoving();

   do
   {
      Serial.println( motion.getPosition(), 3 ); // output position until end point is reached
      delay(9);
   }
   while( !motion.moveComplete() ); // check if move is complete

   // *** THIRD MOVE ***
   motion.setMove( 20.0f, 1000UL );      // end point (mm) -- move takes 1 second
   motion.startMoving();

   do
   {
      Serial.println( motion.getPosition(), 3 ); // output position until end point is reached
      delay(9);
   }
   while( !motion.moveComplete() ); // check if move is complete
  
}


void loop() {
  // put your main code here, to run repeatedly:
}
