/*
      uMove -- Simple one dimentional motion planner
      
      Copyright (C) 2016  Phillip J Schmidt
 */


#ifndef uMove_h
   #define uMove_h

   #include "Arduino.h"


   class uMove
   {
      public:
         uMove( float maxVelocity, float acceleration );
         ~uMove();

         void addMove( float endPoint );
         void addMove( float endPoint, float feedRate );
         void addMove( float endPoint, uint32_t timeMS );

         bool moveComplete();

         void startMoving();
         void stopNow();

         float getPostion();
         float getMoveTime();

         void setPosition( float position );
         void setLimits( float negativeLimit, float positiveLimit );


      private:

         float maxVel, maxAccel;
         float position, velocity;

         int moveDirection;

         uint32_t accelTime, velTime, decelTime, moveTime;


   };




#endif