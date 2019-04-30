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

         void setMove( float endPoint );
         void setMove( float endPoint, float feedRate );
         void setMove( float endPoint, uint32_t timeMS );

         bool moveComplete();

         void startMoving();
         void stopNow();

         float getPosition();
         float getVelocity();

         void setPosition( float x );

         void setMinLimit( float negativeLimit );
         void setMaxLimit( float positiveLimit );


      private:

         float maxVel, maxAccel, invAccel;
         float endPosition, moveVel, moveDistance;
         float position, velocity;

         float minLimit, maxLimit;

         uint32_t lastPosTime;

         bool moving;


   };




#endif