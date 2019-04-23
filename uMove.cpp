/*
      uMove -- Simple one dimentional motion planner

      Copyright (C) 2016  Phillip J Schmidt
 */


#include "uMove.h"


uMove::uMove( float maxVelocity, float acceleration )
{
   maxVel   = maxVelocity;
   maxAccel = acceleration;

   invAccelHalf = 1.0f / ( 2.0f * maxAccel );
}


uMove::~uMove()
{
}


void uMove::addMove( float endPoint )
{
   addMove( endPoint, maxVel );
}

void uMove::addMove( float endPoint, float feedRate )
{
   float dist = endPoint - position;
   if( dist < 0.0f )
   {
      moveDirection = -1;
      dist = -dist;
   }
   else
   {
      moveDirection = 1;
   }
   

   float distanceToVel = ( feedRate * feedRate ) * invAccelHalf;

   if( distanceToVel + distanceToVel > dist )
   {
      distanceToVel = dist * 0.5f;
   }

   
}

