#include <uMove.h>

const float maxVel = 120.0f; // mm/s
const float Accel  = 150.0f; // mm/s^2

uMove motion( maxVel, Accel );


void setup() {

   Serial.begin(250000);
   while( !Serial ) {} // wait for serial to connect

   // First Move
   motion.setPosition( -15.0f ); // current position (mm)
   
   motion.addMove( 50.0f );      // end point (mm)
   motion.startMoving();

   do
   {
      Serial.println( motion.getPosition(), 3 ); // output position until end point is reached
      delay(5);
   }
   while( !motion.moveComplete() ); // check if move is complete

   // Second Move
   motion.addMove( 0.0f );      // end point (mm)
   motion.startMoving();

   do
   {
      Serial.println( motion.getPosition(), 3 ); // output position until end point is reached
      delay(5);
   }
   while( !motion.moveComplete() ); // check if move is complete
  
}


void loop() {
  // put your main code here, to run repeatedly:
}