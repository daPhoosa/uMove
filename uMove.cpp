/*
      uMove -- Simple one dimentional motion planner

      Copyright (C) 2016  Phillip J Schmidt
 */


#include "uMove.h"


uMove::uMove( float maxVelocity, float acceleration )
{
   maxVel   = maxVelocity;
   maxAccel = acceleration;

   invAccel = 1.0f / maxAccel;
   invAccelHalf = invAccel * 0.5f;
   distToMaxVel = maxVel * maxVel * invAccelHalf;

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
   if( !moving )
   {
      float dist = abs( position - endPoint );

      float t = float( timeMS ) * 0.001f;

      float a = -invAccel;
      float b = t;
      float c = -dist;

      float det = b*b - 4.0f * a * c;
      float vel;

      
      if( det > 0 ) // destination is reached in time
      {
         vel = ( -b + sqrtf( det )) / (2.0f * a );
      }
      else  // insufficient time
      {
         vel = maxVel; // best effort
      }

      addMove( endPoint, vel );      
   }
}


void uMove::addMove( float endPoint, float feedRate )
{
   if( !moving && feedRate > 0.001f )
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

