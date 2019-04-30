/*
 *    uMove library example
 *       by Phillip Schmidt
 *    
 *    This example uses uMove to control a stepper motor's position.
 *    Once each move a complete, a new random 
 * 
 *    The dStepper and PollTimer libraries must also be installed to your local Arduino libraries directory
 * 
 */

#include <uMove.h>
#include <dStepper.h>      // https://github.com/daPhoosa/dStepper
#include <PollTimer.h>     // https://github.com/daPhoosa/PollTimer


const float MAX_VEL = 100.0f; // mm/s
const float ACCEL   = 200.0f; // mm/s^2

uMove motion( MAX_VEL, ACCEL );


const float STEPS_PER_MM  = 80.0f;
const int   MOTOR_DIR     = 1;
const float MOTOR_TICK_HZ = 20000.0f;
const int   STEP_PIN      = 10;
const int   DIR_PIN       = 11;
const int   ENABLE_PIN    = 12;

dStepper motor( STEPS_PER_MM, MOTOR_DIR, MOTOR_TICK_HZ, STEP_PIN, DIR_PIN, ENABLE_PIN );


const int   UPDATE_MOTOR_HZ = 400;
const int   OUTPUT_POS_HZ   = 50;
const int   SET_TARGET_HZ   = 10;

PollTimer motorTick(      MOTOR_TICK_HZ );
PollTimer updateMotor(  UPDATE_MOTOR_HZ );
PollTimer outputPosition( OUTPUT_POS_HZ );
PollTimer setTarget(      SET_TARGET_HZ );


void setup()
{
   Serial.begin( 250000 );
   while( !Serial ) {}  // wait for serial port to open

   motion.setPosition(  0.0f ); // initialize motion planner start position
   motor.setPositionMM( 0.0f ); // initialize motor start position
   motor.enable();

   motorTick.start();
   updateMotor.start();
   outputPosition.start();
   setTarget.start();
}


void loop() 
{
   if( motorTick.check() )
   {
      motor.step();
   }
   else if( updateMotor.check() )
   {
      motor.setSpeedByPostionMM( motion.getPosition(), UPDATE_MOTOR_HZ );
   }
   else if( outputPosition.check() )
   {
      Serial.print( motion.getPosition() ); Serial.print( "\t" );
      Serial.println( motor.getPositionMM() );
   }
   else if( setTarget.check() )
   {
      if( motion.moveComplete() )
      {
         motion.setMove( float(random(-100, 100)), uint32_t(random( 10, MAX_VEL)) );
         motion.startMoving();
      }
   }
}