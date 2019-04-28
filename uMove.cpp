/*
      uMove -- Simple one dimentional motion planner

      Copyright (C) 2016  Phillip J Schmidt
 */


#include "uMove.h"


uMove::uMove( float maxVelocity, float acceleration )
{
   maxVel   = maxVelocity;
   maxAccel = acceleration;

   //invAccelHalf = 1.0f / ( 2.0f * maxAccel );

   position = 0.0f;
   velocity = 0.0f;
   moveDistance = 0.0f;

   minLimit = -99999.9f;
   maxLimit =  99999.9f;

   moving = false;
}


uMove::~uMove()
{
}


void uMove::addMove( float endPoint )
{
   addMove( endPoint, maxVel );
}


void uMove::addMove( float endPoint, uint32_t timeMS )
{

}


void uMove::addMove( float endPoint, float feedRate )
{
   if( !moving )
   {
      endPoint     = constrain( endPoint, minLimit, maxLimit );
      moveDistance = endPoint - position;
      moveVel      = min( feedRate, maxVel);
      endPosition  = endPoint;
   }
      
}


void uMove::startMoving()
{
   if( !moving && abs(moveDistance) > 0.001f )
   {
      lastPosTime = micros();
      moving = true;
   }      
}


bool uMove::moveComplete()
{
   return !moving;
}



float uMove::getPostion()
{
   if( moving )
   {
      uint32_t timeNow = micros();
      float deltaTime = (timeNow - lastPosTime) * 0.000001f; // convert microseconds to seconds
      lastPosTime = timeNow;

      if( moveDistance > 0.0f )  // positive move
      {
         float decelVel = min( sqrtf( 2.0f * (endPosition - position) * maxAccel ), moveVel );
         velocity = min( velocity + maxAccel * deltaTime, decelVel );
         position += velocity * deltaTime;
         if( position > endPosition ) 
         {
            position = endPosition;
            velocity = 0.0f;
            moveDistance = 0.0f;
            moving = false;
         }
      }
      else  // negative move
      {
         float decelVel = min( sqrtf( 2.0f * (position - endPosition) * maxAccel ), moveVel );
         velocity = min( velocity + maxAccel * deltaTime, decelVel );
         position -= velocity * deltaTime;
         if( position < endPosition )
         {
            position = endPosition;
            velocity = 0.0f;
            moveDistance = 0.0f;
            moving = false;
         }
      }
   }
   return position;
}


float uMove::getVelocity()
{
   return velocity;
}


void uMove::setPosition( float x )
{
   if( !moving  )
   {
      position = x;
   }      
}

