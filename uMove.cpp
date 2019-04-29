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
      float vel;

      float t = float( timeMS ) * 0.001f;

      float det = t * t - 4.0f * invAccel * abs( position - endPoint );

      if( det > 0 ) // destination is reached in time
      {
         vel = ( -t + sqrtf( det )) / ( -2.0f * invAccel );
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


void uMove::stopNow()
{
   float stopDist = velocity * velocity * invAccel * 0.5f; // distance to declerate to a stop
   if( moveDistance > 0.0f )
   {
      endPosition = position + stopDist;
   }
   else
   {
      endPosition = position - stopDist;
   }
}


bool uMove::moveComplete()
{
   return !moving;
}



float uMove::getPosition()
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

      if( abs(moveDistance) > 0.001f )
      {
         moveDistance = endPosition - position; // recompute if a move is already queued, this should never happen...
      }
   }      
}


void uMove::setMinLimit( float negativeLimit )
{
   minLimit = negativeLimit;
}


void uMove::setMaxLimit( float positiveLimit )
{
   maxLimit = positiveLimit;
}

