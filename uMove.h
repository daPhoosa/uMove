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

         void addMove( float position );
         void addMove( float position, float timeSeconds );

         bool moveComplete();

         void startMoving();
         void stopNow();

         float getPostion();
         float getMoveTime();

         void setPosition( float position );


      private:


   };




#endif